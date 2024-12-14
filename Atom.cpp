#include "Atom.h"

const char *Atom::atomicsymbol[] = {
  "X",
  "H",                                                                                 "He",
  "Li","Be",                                                  "B" ,"C" ,"N" ,"O" ,"F" ,"Ne",
  "Na","Mg",                                                  "Al","Si","P" ,"S" ,"Cl","Ar",
  "K" ,"Ca","Sc","Ti","V" ,"Cr","Mn","Fe","Co","Ni","Cu","Zn","Ga","Ge","As","Se","Br","Kr",
  "Rb","Sr","Y" ,"Zr","Nb","Mo","Tc","Ru","Rh","Pd","Ag","Cd","In","Sn","Sb","Te","I" ,"Xe",
  "Cs","Ba","La",
  "Ce","Pr","Nd","Pm","Sm","Eu","Gd","Tb","Dy","Ho","Er","Tm","Yb","Lu",
  "Hf","Ta","W" ,"Re","Os","Ir","Pt","Au","Hg","Tl","Pb","Bi","Po","At","Rn" };


Atom::Atom(const Atom *atom) {
    _type = atom->_type;
    _layer = atom->_layer;
    _sitetype =  atom->_sitetype;
    _pos = atom->_pos->clone();
    _bflag = atom->_bflag;

}

Atom::Atom(int type, const Position *pos, int layer, int sitetype) {
    _type = type;
    _layer = layer;
    _sitetype = sitetype;
    _pos = pos->clone();
    _bflag=0;
}

Atom::~Atom(void) {
    delete _pos;
}



