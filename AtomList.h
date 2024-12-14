#ifndef INCL_ATOMLIST_H
#define INCL_ATOMLIST_H

#include "Atom.h"

class AtomList {

private:

    int _count;
    int _alloc;
    Atom **_list;

public:

    AtomList(void);

    ~AtomList();

    int getCount(void) const {
        return _count;
    }

    Atom *getAtom(int index) {
        return _list[index];
    }

    /** add an atom to the atomlist. The atomlist takes ownership. */

    void addAtom(Atom *atom); 
    
    /** Add an atom to the atomlis, provided it does not duplicate an existing atom in the list.
        The atomlist takes ownership of the object. A non-unique atom is deleted. */  
    
    void addAtomIfUnique(Atom *atom, double thresh=1e-5);  

    bool doesPositionExist(const Position *pos, double thresh=1e-5) const;

    bool doesPositionExist(Atom *atom, double thresh=1e-5) const {
        return doesPositionExist(atom->getPosition(),thresh);
    }
    
    double nearestDistance(const Position *pos, double thresh=1e-5) const;

    double nearestDistanceWithIndex(const Position *pos, int &idx, double thresh=1e-5) const;

    /** Reorder atoms so that terminating atoms come first, and then go from deepest to surface nearest layer. */
    
    void reorderByLayer(bool ascending=true, bool hfirst=true);
        
    /** Print the atom list as an XYZ file. */
    
    void printXYZ(const char *title = "XYZ") const;

    /** Print the atom list as a prototype Gaussian Input Structure with constraints flags. */
    
    void printGaussian(void) const;

    /** Print the atom list as a DMol3 structure. */
    
    void printDMol(void) const;
    
    void print(void) const;    
};

#endif

