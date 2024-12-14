#include <stdio.h>
#include <stdlib.h>
#include "AtomList.h"

AtomList::AtomList(void) {

    
  _count = 0;
  _alloc = 100;
  _list = new Atom *[_alloc];
}

AtomList::~AtomList() {

  for(int i=0;i<_count;i+=1) {
    delete _list[i];
  }
  delete[] _list;
}

// addAtom: atomlist takes ownership. 

void AtomList::addAtom(Atom *atom) {
  
  if(_count >= _alloc) {
      
    _alloc += 100;
    Atom **newlist = new Atom *[_alloc];
    
    for(int i=0;i<_count;i+=1) {
      newlist[i] = _list[i];
    }
    delete[] _list;
    _list = newlist;
  }

  _list[_count] = atom;
  _count+=1;
}

void AtomList::addAtomIfUnique(Atom *atom, double thresh) { 
    
    if(doesPositionExist(atom->getPosition(), thresh)) {
        delete atom;
    }
    else {
        addAtom(atom);        
    }
}

    


bool AtomList::doesPositionExist(const Position *pos, double thresh) const {

  for(int i=0;i<_count;i+=1) {    
    if(_list[i]->getPosition()->isEqualTo(pos,thresh)) return true;
  }

  return false;
}

void AtomList::print(void) const {
    
    for(int i=0;i<_count;i+=1) {
        
        Atom *atom = _list[i];
        
        printf("%2s %12.6lf %12.6lf %12.6lf  %3d\n",
            atom->getAtomicSymbol(),
               atom->getPosition()->getElement(0),
               atom->getPosition()->getElement(1),
               atom->getPosition()->getElement(2),
               atom->getLayer());               
    }
}

void AtomList::printXYZ(const char *title) const {
    
    printf("%d\n",_count);
    printf("%s\n",title);
    
    for(int i=0;i<_count;i+=1) {
        
        Atom *atom = _list[i];
        
        printf("%2s %12.6lf %12.6lf %12.6lf\n",
               atom->getAtomicSymbol(),
               atom->getPosition()->getElement(0),
               atom->getPosition()->getElement(1),
               atom->getPosition()->getElement(2));               
    }
}

void AtomList::printGaussian(void) const {
    
    printf("0 1\n");
    
    for(int iat=0;iat<_count;iat+=1) {
        
        Atom *atom = _list[iat];
        
        if(atom->getLayer() == -1) {
            
            printf("%2s -1 %12.6lf %12.6lf %12.6lf\n",
                   atom->getAtomicSymbol(),
                   atom->getPosition()->getElement(0),
                   atom->getPosition()->getElement(1),
                   atom->getPosition()->getElement(2)); 
        } 
        else {
            
            printf("%2s    %12.6lf %12.6lf %12.6lf\n",
                   atom->getAtomicSymbol(),
                   atom->getPosition()->getElement(0),
                   atom->getPosition()->getElement(1),
                   atom->getPosition()->getElement(2));             
        }        
    }
}


double AtomList::nearestDistance(const Position *pos, double thresh) const {
    
    int idx;
    
    return nearestDistanceWithIndex(pos,idx,thresh);
    
}

double AtomList::nearestDistanceWithIndex(const Position *pos, int &index, double thresh) const {
    
    double mindist = 1e10;
    index = -1;

    for(int iat=0;iat<_count;iat+=1) {
        
        double dist = _list[iat]->getPosition()->distanceTo(pos);

        if(dist<mindist) { 
            mindist=dist;
            index = iat;
        }
        if(mindist<thresh) break;
    }
    
    return mindist;
}


void AtomList::reorderByLayer(bool ascending, bool hfirst) {
  
    Atom **newlist = new Atom *[_alloc];
    int ncount = 0;

    // --- terminating atoms, if those have been requested to come first.
    
    if(hfirst) {

        // transfer terminating atoms to newlist

        for(int iat=0;iat<_count;iat+=1) {
            if(_list[iat]->getLayer() == -1) {
                newlist[ncount++] = _list[iat];
            }        
        }

        // reorder by z-coordinate

        int idx = 1;
        while(idx<ncount) { 
	  if((!ascending && 
              newlist[idx]->getPosition()->getElement(2) > 
              newlist[idx-1]->getPosition()->getElement(2)) ||
             (ascending &&
	      newlist[idx]->getPosition()->getElement(2) <
              newlist[idx-1]->getPosition()->getElement(2))) {
	    Atom *intm = newlist[idx];
            newlist[idx] = newlist[idx-1];
            newlist[idx-1] = intm;
            if(idx>1) idx-=1;
 	  }
	  else {
	    idx +=1;
	  }
	}
    }
    
    // find largest depth
    
    int maxdepth=0;
    for(int iat=0;iat<_count;iat+=1) {
        if(_list[iat]->getLayer()>maxdepth) maxdepth = _list[iat]->getLayer();        
    }
    
    // reorder non-terminating cluster atoms either ascending or descending as requested.
        
    if(ascending) {
    
        for(int ilay=maxdepth;ilay>0;ilay-=1) {
            for(int iat=0;iat<_count;iat+=1) {
                if(_list[iat]->getLayer() == ilay) {
                    newlist[ncount++] = _list[iat];
                }
            }
        }        
    }        
    else {
        for(int ilay=1;ilay<=maxdepth;ilay+=1) {
            for(int iat=0;iat<_count;iat+=1) {
                if(_list[iat]->getLayer() == ilay) {
                    newlist[ncount++] = _list[iat];
                }
            }
        }        
    }
    
    // --- terminating atoms, if those have been requested to come last.
    
    if(!hfirst) {
        for(int iat=0;iat<_count;iat+=1) {
            if(_list[iat]->getLayer() == -1) {
                newlist[ncount++] = _list[iat];
            }        
        }
    }

    // Sanity Check
    
    if(_count != ncount) {
        fprintf(stderr,"Unexpected error during reordering ...\n");
        exit(EXIT_FAILURE);
    }
    
    // Clean up
    
    delete[] _list;
    _list = newlist;
}




