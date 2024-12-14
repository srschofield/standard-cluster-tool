#include <stdio.h>
#include "Parser.h"

const int Parser::XYZFormat = 0;
const int Parser::GaussianFormat = 1;

Parser::Parser(void) {
    
    _talloc=100;
    _tcount=0;
    _tlist = new int[_talloc];

    _maxdepth = 0;
    _maxrow=0;
    _maxdimer=0;
    
    _bucklingtype=0;  // flat dimers by default.
    _order_ascending = true;
    _order_hfirst = true;
    _output_format = Parser::XYZFormat;
    
    _template = NULL;
}

Parser::~Parser() {
    
    delete[] _tlist;
    if(_template!=NULL) delete _template;

}

bool Parser::_strcmp(const char *a,const char *b) {
 
    while(true) {
        if(*a != *b) return false;
        if(*a == '\0') return true;
        a+=1;
        b+=1;
    }    
}

// reads a single digit number from the string, except 
// when the string starts of with an open curly bracked 
// which indicates a
// multidigit number until a closing bracket is found. 

int Parser::_readSingleDigitNumber(char *str, int &idx) {
    
    if(str[idx]=='0') {
        idx+=1;
        return 0; 
    } 
    else if(str[idx]=='1') {
        idx+=1;
        return 1;
    }
    else if(str[idx]=='2') {
        idx+=1;
        return 2;
    }
    else if(str[idx]=='3') {
        idx+=1;
        return 3;
    }
    else if(str[idx]=='4') {
        idx+=1;
        return 4;
    }
    else if(str[idx]=='5') {
        idx+=1;
        return 5;
    }
    else if(str[idx]=='6') {
        idx+=1;
        return 6;
    }
    else if(str[idx]=='7') {
        idx+=1;
        return 7;
    }
    else if(str[idx]=='8') {
        idx+=1;
        return 8;
    }
    else if(str[idx]=='9') {
        idx+=1;
        return 9;
    }
    else {
        return -1;
    }
}

// Reads single-digit or (via curly brackets) a multidigit positive number. 
// A negative number is returned in case of an error condition.

int Parser::_readNumber(char *str, int &idx) {

    int num = _readSingleDigitNumber(str,idx);

    if(num>=0) {      
        return num;
    }
    else if(str[idx]=='{') {
        idx+=1;
        num=0;
        int digit;
        while((digit=_readSingleDigitNumber(str,idx))>=0) {
            num*=10;
            num+=digit;
        }
        if(str[idx]=='\'') {
            num+=100;
            idx+=1;
        }
        if(str[idx]=='}') {
            idx+=1;
            return num;
        }
        else {
            return -1;        
        }            
    }
    else {
        return -1;
    }
}

// Returns 1 on successful read; 0 on failure.

int Parser::_readClusterDescriptor(char *descr) {

    int idx=0; 
    int step=0;
    int idim = 0;
    int irow = 0;
    
    while(1) {
        if(descr[idx]=='\0') {    // normal end of cluster descriptor.
            return 1;
        }
        else if(descr[idx]=='|') {  // indicator for new row.
            step+=1;    
            idx+=1;
            irow+=1;
            idim=0;
            if(irow>_maxrow) _maxrow=irow;
            _addToken(-1);
        }
        else {              // expect to read a number.
            step += 1;
            idim+=1;
            if(idim>_maxdimer) _maxdimer=idim;
            if(irow==0) {
                irow=1;
                if(irow>_maxrow) _maxrow=irow;
            } 
            int num = _readNumber(descr,idx);
            if(num>_maxdepth) _maxdepth=num;
            if(descr[idx]=='\'') {
               idx+=1;
               num += 100;
            }            
            _addToken(num);
            if(num<0) {
                return 0;
            }
        }
    }    
}

int Parser::readArguments(int argc, char *argv[]) {
        
    if(argc==1) {
        fprintf(stderr,"Usage:   sct <template> [<options> ...] <cluster-descriptor>\n\n");
        fprintf(stderr,"Templates:  Si           Si(001) surface template generated using\n");
        fprintf(stderr,"                         VASP GGA_DFT (Warschkow et al. Surf.Sci. 2007).\n");
	fprintf(stderr,"            Si2024       Si(001) surface template generated using\n");
        fprintf(stderr,"                         CASTEP v19, PBE, USP, (8x4x1) MP, 800 eV, 20 layers (Schofield 2024).\n");
	fprintf(stderr,"            Ge2024       Ge(001) surface template generated using\n");
        fprintf(stderr,"                         CASTEP v19, PBE, USP, (8x4x1) MP, 800 eV, 20 layers (Schofield 2024).\n");
        fprintf(stderr,"            DSi          Si(001) surface template generated using\n");
        fprintf(stderr,"                         DMol3 PBE/DZP. (Tracey et al, JCP 2012).\n");
        fprintf(stderr,"Options:    -p2x1        Selects a p(2x1) flat-dimer pattern.\n");
        fprintf(stderr,"                         This is the default dimer-buckling pattern.\n");
        fprintf(stderr,"            -c4x2        Selects a c(4x2) buckled dimer pattern.\n");
        fprintf(stderr,"            -c4x2inv     Selects a c(4x2) buckled dimer pattern\n");
        fprintf(stderr,"                         with opposite orientation to the -c4x2 option.\n");
        fprintf(stderr,"            -p2x2        Selects a p(2x2) buckled dimer pattern.\n");
        fprintf(stderr,"            -p2x2inv     Selects a p(2x2) buckled dimer pattern\n");
        fprintf(stderr,"                         with opposite orientation to the -c2x2 option.\n");
        fprintf(stderr,"            -xyz         Prints cluster in XYZ file format.\n");
        fprintf(stderr,"                         This is the default output format.\n");
        fprintf(stderr,"            -gaussian    Prints cluster as a Gaussian input\n");
        fprintf(stderr,"                         structure with opt=ModRedunant\n");
        fprintf(stderr,"                         constraint flags.\n");
        fprintf(stderr,"            -ascending   Prints structure ordered by atomic layer\n");
        fprintf(stderr,"                         starting with the deepest layer. This is\n");
        fprintf(stderr,"                         the default ordering of atoms.\n");
        fprintf(stderr,"            -descending  Prints structure ordered by atomic layer\n");
        fprintf(stderr,"                         surface (dimer) layer.\n");
        fprintf(stderr,"            -hfirst      Reorders atoms so that the terminating\n");
        fprintf(stderr,"                         hydrogen atoms come before any of the\n");
        fprintf(stderr,"                         cluster atoms. This is the default order\n");
        fprintf(stderr,"                         in which atoms are outputted.\n");
        fprintf(stderr,"            -hlast       Reorders atoms so that the terminating\n");
        fprintf(stderr,"                         hydrogen atoms come after the cluster\n");
        fprintf(stderr,"                         atoms.\n");        
        fprintf(stderr,"\n");

        fprintf(stderr,"Example use:\n");
        fprintf(stderr,"  sct Si2024 -gaussian \"4'\" > my_cluster.gjf \n");
        fprintf(stderr,"      Creates a single-dimer, single-row Si9H12 cluster in Gaussian input format.\n");
        fprintf(stderr,"      Note: The third argument is written as \"<four><prime>\", where \"four\" refers\n");
        fprintf(stderr,"      to the number of silicon layers below the dimer, and \"prime\" indicates that\n");
        fprintf(stderr,"      this is not a \"wide\" cluster.\n\n");
        fprintf(stderr,"  sct Si2024 -gaussian \"4'4'\" > my_cluster.gjf \n");
        fprintf(stderr,"      Creates a two-dimer cluster Si15H16.\n\n");
        fprintf(stderr,"  sct Si2024 -gaussian \"4'4'|4'4'\" > my_cluster.gjf \n");
        fprintf(stderr,"      Creates a four-dimer-in-two-rows cluster Si35H32.\n");
        fprintf(stderr,"      Note: Each \"four\" has a prime, and rows are separated by a vertical bar.\n\n");
        fprintf(stderr,"  sct Si2024 -gaussian \"2'4'2'\" > my_cluster.gjf \n");
        fprintf(stderr,"      Creates a cluster with varying depth, combining numbers for different depths.\n");
        fprintf(stderr,"\n");
	
        return 0;
    }

    // Expect template label next.
    
    _template = Template::newTemplate(argv[1]);
    if(_template==NULL) {    
        fprintf(stderr,"Unknown template %s.\n",argv[1]);
        return 0;
    }
    
    int iarg=2;
    while(iarg<argc) {
    
        char *arg = argv[iarg++];
        
        if(_strcmp(arg,"-c4x2")) {
            _bucklingtype=3;
            fprintf(stderr,"Select c4x2 Buckling.\n");
        }
        else if(_strcmp(arg,"-c4x2inv")) {
            _bucklingtype=4;
            fprintf(stderr,"Select c4x2 Buckling (inverted).\n");
        }
        else if(_strcmp(arg,"-p2x1")) {
            _bucklingtype=0;
            fprintf(stderr,"Select p2x1 Buckling.\n");
        }
        else if(_strcmp(arg,"-p2x2")) {
            _bucklingtype=1;
            fprintf(stderr,"Select p2x2 Buckling.\n");
        }
        else if(_strcmp(arg,"-p2x2inv")) {
            _bucklingtype=2;
            fprintf(stderr,"Select p2x2 Buckling (inverted).\n");
        }
        else if(_strcmp(arg,"-xyz")) {
            _output_format = Parser::XYZFormat;
        }
        else if(_strcmp(arg,"-gaussian")) {
            _output_format = Parser::GaussianFormat;
        }
        else if(_strcmp(arg,"-ascending")) {
            _order_ascending = true;
        }
        else if(_strcmp(arg,"-descending")) {
            _order_ascending = false;
        } 
        else if(_strcmp(arg,"-hfirst")) {
            _order_hfirst = true;
        }
        else if(_strcmp(arg,"-hlast")) {
            _order_ascending = true;
        }
        else {
            if(!_readClusterDescriptor(arg)) {
                fprintf(stderr,"Unable to parse cluster descriptor.\n");
                return 0;
            }
        }
    }    
    
    _template->assembleTemplate(_maxdepth+5);
    
    return 1;
}

void Parser::_addToken(int token) {
    
    if(_tcount>=_talloc) {
        _talloc+=1;
        int *newlist = new int[_talloc];
        for(int i=0;i<_tcount;i+=1) {
            newlist[i] = _tlist[i];
        }
        delete[] _tlist;
        _tlist = newlist;                      
    }
    _tlist[_tcount] = token;
    _tcount+=1;
}

int Parser::getBucklingOrientation(int row,int dimer) {

    switch(_bucklingtype) {
            
        case -1:    return 0;
        case 0:     return 0;                          // p2x1
        case 1:     return (dimer%2) ? 1 : -1;         // p2x2
        case 2:     return (dimer%2) ? -1 : 1;         // p2x2 inv
        case 3:     return ((dimer+row)%2) ? 1 : -1;   // c4x2 
        case 4:     return ((dimer+row)%2) ? -1 : 1;   // c4x2 inv 
        default:    return 0;    
    }
}
 
