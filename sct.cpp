#include <stdio.h>
#include <stdlib.h> 
#include "AtomList.h"
#include "SiliconTemplate.h"
#include "Silicon2024Template.h"
#include "Germanium2024Template.h"
#include "DSiliconTemplate.h"
#include "Parser.h"

int main(int argc, char *argv[]) {

    fprintf(stderr,"Standard Cluster Tool - v1.5 (6 August 2012)\n");
    fprintf(stderr,"Oliver Warschkow, School of Physics, The University of Sydney\n");

    Parser parser;
    
    if(!parser.readArguments(argc,argv)) {
        fprintf(stderr,"Exiting due to input error\n");
        exit(EXIT_FAILURE);
    }
    
    Template *temp = parser.getTemplate();                       
                           
    fprintf(stderr,"Using template: %s\n",temp->getTitle());
    
    AtomList *cluster = new AtomList();



    Position offset;
    AtomList *tlist = temp->getAtomList();    

    AtomList **holdlist = new AtomList *[parser.getMaxRow()]; // holds outer atoms in case of priming.
    for(int ir=0;ir<parser.getMaxRow();ir+=1) {
        holdlist[ir] = new AtomList();
    }
          
    int irow = 0;
    int idim = 0;
    
    for(int itok=0;itok<parser.getTokenCount();itok+=1) {
        
        int depth = parser.getToken(itok)%100;
        bool flag = (parser.getToken(itok)/100)>0;
        
        if(depth<0) {
            
            irow+=1;
            idim=0;
        } 
        else {
            
            int buck = parser.getBucklingOrientation(irow,idim);
            
            offset.setTo(idim*temp->getRepeat(),irow*2.0*temp->getRepeat(),0);
            
            for(int iat=0;iat<tlist->getCount();iat+=1) {
                
                Atom *tatom = tlist->getAtom(iat);
 
                Atom *atom = tatom->clone();
                atom->getPosition()->addTo(&offset);
                                
                if(tatom->getLayer()>depth) break;
                if(flag &&
                   (tatom->getSiteType()/4==5 ||
                    tatom->getSiteType()/4==3)) {
                       holdlist[irow]->addAtomIfUnique(atom);
                       continue;
                }
                
                if(atom->getLayer()==1) {
                    atom->setBucklingFlag(buck);
                }
                                          
                cluster->addAtomIfUnique(atom);
            }
            idim+=1;
        }
    }
    
    /// No go through the holdlist and add any atoms that are held in two adjacent rows.

    for(int ir=0;ir<parser.getMaxRow()-1;ir+=1) {
    
        AtomList *list1 = holdlist[ir];
        AtomList *list2 = holdlist[ir+1];
        
        for(int iat=0;iat<list1->getCount();iat+=1) {
            
            if(list2->doesPositionExist(list1->getAtom(iat)->getPosition())) {
                cluster->addAtomIfUnique(list1->getAtom(iat)->clone());
            }
        }
    }
    
    /// ---- Hydrogen Termination
    
    AtomList *hterm = new AtomList();
    
    Position hpos;     // use to calc H-position in.
    Position atompos;  // use to calc surrounding atom pos in.
    
    for(int irow=-1;irow<=parser.getMaxRow();irow+=1) {
        for(int idim=-1;idim<=parser.getMaxDimer();idim+=1) {
            
            offset.setTo(idim*temp->getRepeat(),irow*2.0*temp->getRepeat(),0);

            double mindist = 0.0;
            for(int iat=0;iat<tlist->getCount();iat+=1) {
                
                Atom *atom = tlist->getAtom(iat);

                if(atom->getLayer()>=parser.getMaxDepth()+2) break;  

                atompos.setTo(atom->getPosition());
                atompos.addTo(&offset);
                
                if(!cluster->doesPositionExist(&atompos,1e-5)) {
                
                    for(int icl=0;icl<cluster->getCount();icl+=1) {

                        Position *clpos = cluster->getAtom(icl)->getPosition();
                        
                        double dist = atompos.distanceTo(clpos);
                        if(dist>temp->getBondMin() && dist<temp->getBondMax()) {
      
                            // found a bond ... need a terminating H atom.
                    
                            hpos.setTo(&atompos);
                            hpos.subTo(clpos);
                            hpos.multTo(temp->getBondLength()/dist);
                            hpos.addTo(clpos);
                            
                            hterm->addAtomIfUnique(new Atom(1,&hpos,-1,-1));
                        }
                    }
                }
            }
        }
    }

    // Add all terminating atoms to the cluster.
    
    for(int iat=0;iat<hterm->getCount();iat+=1) {        
        cluster->addAtom( hterm->getAtom(iat)->clone() );        
    }
    
    delete hterm;
    
    /// Find the centre of all dimers
    
    Position centre(0.0,0.0,0.0);
    int ccount = 0;
    
    for(int iat=0;iat<cluster->getCount();iat+=1) {
        
        Atom *atom = cluster->getAtom(iat);
        if(atom->getLayer()==1) {
            centre.addTo(atom->getPosition());
            ccount += 1;
        }
    }
    centre.multTo(1.0/((double) ccount));
    
    for(int iat=0;iat<cluster->getCount();iat+=1) {        
        cluster->getAtom(iat)->getPosition()->subTo(&centre);
    }
    
    // Put dimer buckling into effect.
    
    for(int iat=0;iat<cluster->getCount();iat+=1) {
        
        Atom *atom = cluster->getAtom(iat);
        int buck = atom->getBucklingFlag();
        if(buck>0) {
            if(atom->getSiteType()==0) {
                atom->getPosition()->addTo(0.0, temp->getBucklingUpY(), temp->getBucklingUpZ());
            } 
            else {
                atom->getPosition()->addTo(0.0, -temp->getBucklingDownY(), temp->getBucklingDownZ());
            }            
        } 
        else if(buck<0) {
            if(atom->getSiteType()==0) {
                atom->getPosition()->addTo(0.0, temp->getBucklingDownY(), temp->getBucklingDownZ());
            } 
            else {
                atom->getPosition()->addTo(0.0, -temp->getBucklingUpY(), temp->getBucklingUpZ());
            }                  
        }                
    }
    
    // ----- Reorder atoms ------------------------
    
    cluster->reorderByLayer(parser.getOrderAscending(),parser.getOrderHFirst());
    
    // ---------- Print out cluster statistics
    
    int hcount = 0;
    int clcount = 0;
    int *lcount = new int[parser.getMaxDepth()+1];
    for(int ilay=0;ilay<=parser.getMaxDepth();ilay+=1) {
        lcount[ilay] = 0;
    }
    for(int iat=0;iat<cluster->getCount();iat+=1) {
        Atom *atom=cluster->getAtom(iat);
        if(atom->getLayer() == -1) {
            hcount+=1;
        }
        else {
            clcount+=1;
            lcount[atom->getLayer()]+=1;
        }
    }    
    fprintf(stderr,"Stoichiometry ..... Si%dH%d\n",clcount,hcount);
    fprintf(stderr,"Termination ....... %4d atoms\n",hcount);  
    for(int ilay=1;ilay<=parser.getMaxDepth();ilay+=1) {
        fprintf(stderr,"Layer %3d ......... %4d atoms\n",ilay,lcount[ilay]);
    }
    fprintf(stderr,"Total Atom Count .. %4d atoms\n",cluster->getCount());

    // ---------- Print out cluster --------

    if(parser.getOutputFormat() == Parser::XYZFormat) {
        fprintf(stderr,"Writing structure in XYZ-format.\n");
        cluster->printXYZ();
    }
    else if(parser.getOutputFormat() == Parser::GaussianFormat) {
        fprintf(stderr,"Writing structure in Gaussian input format.\n");
        cluster->printGaussian();
    }

    // ------ all done ----------------------

    fprintf(stderr,"Exiting normally ...\n");
    
    exit(EXIT_SUCCESS);
}

