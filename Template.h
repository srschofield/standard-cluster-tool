#ifndef INCL_TEMPLATE_H
#define INCL_TEMPLATE_H

#include "AtomList.h"
#include "Position.h"

class Template {

 protected:

    AtomList *_atlist;

    const char *_title; // Description of template structure.
    const int _ntparam; // Number of template parameters.    
    double *_tparam;    // Array to hold the template parameters.
    int _atomtype; // Atomic index. 
    double _repeat;
    double _bondmin;
    double _bondmax;
    double _bondlength;
    double _buckling_up_y;
    double _buckling_up_z;
    double _buckling_down_y;
    double _buckling_down_z;
    
    bool _surfacePosition(int idx,
                          Position &pos,
                          int &layer,int &sitetype);

    void _bulkPosition(int idx,
                       Position &pos,
                       int &layer, int &sitetype, double &zlast);
        
    Template(const char *title, int ntparam);

    static bool _strcmp(const char *a, const char *b);
    
public:

   ~Template();
    
    void assembleTemplate(int maxlayer);
    
    /** Factory method for various predefined templates. */
    
    static Template *newTemplate(const char *label);
    
    AtomList *getAtomList(void) {
        return _atlist;
    } 
    
    const char *getTitle(void) const {
        return _title;
    }
    
    double getRepeat(void) const { 
        return _repeat;
    }
    
    double getBondMin(void) const {
        return _bondmin;
    }
    
    double getBondMax(void) const {
        return _bondmax;
    }
    
    double getBondLength(void) const {
        return _bondlength;
    }
    
    double getBucklingUpY(void) const {
        return _buckling_up_y;
    }
   
    double getBucklingUpZ(void) const {
        return _buckling_up_z;
    }
    
    double getBucklingDownY(void) const {
        return _buckling_down_y;
    }
    
    double getBucklingDownZ(void) const {
        return _buckling_down_z;
    }
};

#endif
