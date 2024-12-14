#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Template.h"
#include "SiliconTemplate.h"
#include "Silicon2024Template.h"
#include "Germanium2024Template.h"
#include "DSiliconTemplate.h"

Template::Template(const char *title, int ntparam) :
_title(title), _ntparam(ntparam) {
    
    _tparam = new double[_ntparam];
    _atlist = NULL;
}

Template::~Template() {
    
    delete[] _tparam;  
    if(_atlist!=NULL) delete _atlist;
}

bool Template::_surfacePosition(int idx,
                                Position &pos,
                                int &layer,int &sitetype) {

    int lindex = idx%15;
    int bindex = idx/15;
    double *par = _tparam + 8*bindex;

    switch(lindex) {
    // ------ layer 1 ----- 	     
    case 0:  if(8*bindex+1>=_ntparam) return false;
             pos.setTo(0.5, par[0], par[1]);
             layer = 4*bindex + 1;
             sitetype = (0*4) + 0;
             break;
    case 1:  if(8*bindex+1>=_ntparam) return false;
             pos.setTo(0.5, 1.0-par[0], par[1]);
             layer = 4*bindex + 1;
             sitetype = (0*4) + 1;
             break;
    // ------ layer 2 ----- 	     
    case 2:  if(8*bindex+3>=_ntparam) return false;
             pos.setTo(0, par[2], par[3]); 	   
             layer = 4*bindex + 2;
             sitetype = (1*4) + 0;
             break;
    case 3:  if(8*bindex+3>=_ntparam) return false;
             pos.setTo(0, 1.0-par[2], par[3]); 	   
             layer = 4*bindex + 2;
             sitetype = (1*4) + 1;
             break;
    case 4:  if(8*bindex+3>=_ntparam) return false;
             pos.setTo(1.0, par[2], par[3]); 	   
             layer = 4*bindex + 2;
             sitetype = (1*4) + 2;  
             break;
    case 5:  if(8*bindex+3>=_ntparam) return false;
             pos.setTo(1.0, 1.0-par[2], par[3]); 	   
             layer = 4*bindex + 2;
             sitetype = (1*4) + 3;
             break;
    // ------ layer 3a ----- 	     
    case 6:  if(8*bindex+4>=_ntparam) return false;
             pos.setTo(0.0, 0.5, par[4]);
             layer = 4*bindex + 3;
             sitetype = (2*4) + 0;
             break; 
    case 7:  if(8*bindex+4>=_ntparam) return false;
             pos.setTo(1.0, 0.5, par[4]);
             layer = 4*bindex + 3;
             sitetype = (2*4) + 1;
             break;
    // ------ layer 3b ----- 	     
    case 8:  if(8*bindex+5>=_ntparam) return false;
             pos.setTo(0.0, 0.0, par[5]);
             layer = 4*bindex + 3;
            sitetype = (3*4) + 0;
             break;
    case 9:  if(8*bindex+5>=_ntparam) return false;
             pos.setTo(1.0, 0.0, par[5]);
             layer = 4*bindex + 3;
             sitetype = (3*4) + 1;
             break; 
    case 10: if(8*bindex+5>=_ntparam) return false;
             pos.setTo(0.0, 1.0, par[5]);
             layer = 4*bindex + 3;
            sitetype = (3*4) + 2;
             break;
    case 11: if(8*bindex+5>=_ntparam) return false;
             pos.setTo(1.0, 1.0, par[5]);
             layer = 4*bindex + 3;            
            sitetype = (3*4) + 3;
             break;
    // ------ layer 4a ----- 	     
    case 12: if(8*bindex+6>=_ntparam) return false;
             pos.setTo(0.5, 0.5, par[6]);
             layer = 4*bindex + 4;
             sitetype = (4*4) + 0;
             break;
    // ------ layer 4b ----- 	     
    case 13: if(8*bindex+7>=_ntparam) return false;
             pos.setTo(0.5, 0.0, par[7]);
             layer = 4*bindex + 4;
             sitetype = (5*4) + 0;
             break;
    case 14: if(8*bindex+7>=_ntparam) return false;
             pos.setTo( 0.5, 1.0, par[7]);
             layer = 4*bindex + 4;
             sitetype = (5*4) + 1;
             break;
    }
    return true;
}


void Template::_bulkPosition(int idx,
                             Position &pos,
                             int &layer, int &sitetype,double &zlast) {

    int lindex = idx%15;   
    int bindex = idx/15;

    switch(lindex) {

    case 0:  zlast-=_repeat*sqrt(2.0)/4.0;
             pos.setTo(0.5, 0.25, zlast);
             layer = 4*bindex + 1;
             sitetype = (0*4)+0;
             break;
    case 1:  pos.setTo(0.5, 0.75, zlast);
             layer = 4*bindex + 1;
             sitetype = (0*4)+1;
             break;
    // ------ layer 2 ----- 	     
    case 2:  zlast-=_repeat*sqrt(2.0)/4.0;
             pos.setTo(0, 0.25, zlast);
             layer = 4*bindex + 2;
             sitetype = (1*4)+0;
             break;
    case 3:  pos.setTo(0, 0.75, zlast);
             layer = 4*bindex + 2;
             sitetype = (1*4)+1;
             break;
    case 4:  pos.setTo(1.0, 0.25, zlast);
             layer = 4*bindex + 2;
             sitetype = (1*4)+2;
             break;
    case 5:  pos.setTo(1.0, 0.75, zlast);
             layer = 4*bindex + 2;
             sitetype = (1*4)+3;
             break;
    // ------ layer 3a ----- 	     
    case 6:  zlast-=_repeat*sqrt(2.0)/4.0;
             pos.setTo(0.0, 0.5, zlast);
             layer = 4*bindex + 3;
             sitetype = (2*4)+0;
             break; 
    case 7:  pos.setTo(1.0, 0.5, zlast);
             layer = 4*bindex + 3;
             sitetype = (2*4)+1;
             break;
    // ------ layer 3b ----- 	     
    case 8:  pos.setTo(0.0, 0.0, zlast);
             layer = 4*bindex + 3;
             sitetype = (3*4)+0;
             break;
    case 9:  pos.setTo(1.0, 0.0, zlast);
             layer = 4*bindex + 3;
             sitetype = (3*4)+1;
             break; 
    case 10: pos.setTo(0.0, 1.0, zlast);
             layer = 4*bindex + 3;
             sitetype = (3*4)+2;
             break;
    case 11: pos.setTo(1.0, 1.0, zlast);
             layer = 4*bindex + 3;
             sitetype = (3*4)+3;
             break;
    // ------ layer 4a ----- 	     
    case 12: zlast-=_repeat*sqrt(2.0)/4.0;
             pos.setTo(0.5, 0.5, zlast);
             layer = 4*bindex + 4;
             sitetype = (4*4)+0;
             break;
    // ------ layer 4b ----- 	     
    case 13: pos.setTo(0.5, 0.0, zlast);
             layer = 4*bindex + 4;
             sitetype = (5*4)+0;
             break;
    case 14: pos.setTo(0.5, 1.0, zlast);
             layer = 4*bindex + 4;
             sitetype = (5*4)+1;
             break;
    }
}

void Template::assembleTemplate(int maxlayers) {

    int iparam = 0;
    int idx = 0;
    double zlast=0;
    Position pos;

    _atlist = new AtomList();
    
    while(true) { 
        
        int layer,sitetype;

        if(!_surfacePosition(idx,pos,layer,sitetype)) {

            _bulkPosition(idx,pos,layer,sitetype,zlast);
        }

        if(layer>maxlayers) break;
        
        zlast = pos.getElement(2);

        pos.multTo(_repeat,2*_repeat,1.0);
   
        _atlist->addAtom( new Atom(_atomtype,&pos,layer,sitetype) );

        idx+=1;  
    }
}

bool Template::_strcmp(const char *a,const char *b) {
    
    while(true) {
        if(*a != *b) return false;
        if(*a == '\0') return true;
        a+=1;
        b+=1;
    }    
}

Template *Template::newTemplate(const char *label) {
    
    if(_strcmp(label,"Si")) {
        return new SiliconTemplate();
    }
    else if(_strcmp(label,"DSi")) {
        return new DSiliconTemplate();
    }
    else if(_strcmp(label,"Si2024")) {
        return new Silicon2024Template();
    }
    else if(_strcmp(label,"Ge2024")) {
        return new Germanium2024Template();
    }
    else {
        return NULL;
    }
}


