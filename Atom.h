#ifndef INCL_ATOM_H
#define INCL_ATOM_H

#include "Position.h"

class Atom {

 private:

    Position *_pos;
    int _type;
    int _layer;
    int _sitetype;
    int _bflag;

    static const char *atomicsymbol[];  
    
 public:

    Atom(const Atom *atom);

  Atom(int type, const Position *pos, int layer, int sitetype);

  ~Atom();

  Atom *clone(void) const {
    return new Atom(this);
  }

  Position *getPosition(void) {
    return _pos;
  }

  int getType(void) const {
    return _type;
  }

  int getLayer(void) const {
    return _layer;
  }
    
    int getSiteType(void) const {
        return _sitetype;
    }

    const char *getAtomicSymbol(void) {
        return atomicsymbol[_type];
    }

    int getBucklingFlag(void) const {
        return _bflag;
    }

    void setBucklingFlag(int flag) {
        _bflag=flag;
    }
    
};

#endif
