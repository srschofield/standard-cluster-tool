#include "Position.h"
#include <math.h>

Position::Position(void) {
  _pos[0] = 0;
  _pos[1] = 0;
  _pos[2] = 0;
}

Position::Position(const Position *pos) {
    _pos[0] = pos->_pos[0];
    _pos[1] = pos->_pos[1];
    _pos[2] = pos->_pos[2];
}

Position::Position(double x,double y,double z) {
  
  _pos[0] = x;
  _pos[1] = y;
  _pos[2] = z;
}

Position::Position(double *pos) {

  _pos[0] = pos[0];
  _pos[1] = pos[1];
  _pos[2] = pos[2];
}

Position::~Position() {
}

Position *Position::setTo(double x,double y,double z) {

  _pos[0] = x;
  _pos[1] = y;
  _pos[2] = z;

  return this;
}

Position *Position::setTo(const Position *pos) {

  _pos[0] = pos->_pos[0];
  _pos[1] = pos->_pos[1];
  _pos[2] = pos->_pos[2];

  return this;
}

Position *Position::addTo(const Position *pos) {

  _pos[0] += pos->_pos[0];
  _pos[1] += pos->_pos[1];
  _pos[2] += pos->_pos[2];

  return this;
}

Position *Position::addTo(double x, double y, double z) {
    
    _pos[0] += x;
    _pos[1] += y;
    _pos[2] += z;
    
    return this;
}


Position *Position::subTo(const Position *pos) {

  _pos[0] -= pos->_pos[0];
  _pos[1] -= pos->_pos[1];
  _pos[2] -= pos->_pos[2];

  return this;
}

Position *Position::multTo(double factor) {

  _pos[0] *= factor;
  _pos[1] *= factor;
  _pos[2] *= factor;

  return this;
}

Position *Position::multTo(double xfactor, double yfactor, double zfactor) {

  _pos[0] *= xfactor;
  _pos[1] *= yfactor;
  _pos[2] *= zfactor;

  return this;
}

bool Position::isEqualTo(const Position *pos, double thresh) {

  return ( ( fabs(_pos[0] - pos->_pos[0]) < thresh ) &&
           ( fabs(_pos[1] - pos->_pos[1]) < thresh ) &&
           ( fabs(_pos[2] - pos->_pos[2]) < thresh ) );  
}

double Position::distanceTo(const Position *pos) const {
    
    return sqrt( (_pos[0] - pos->_pos[0]) * (_pos[0] - pos->_pos[0]) +
                 (_pos[1] - pos->_pos[1]) * (_pos[1] - pos->_pos[1]) +
                 (_pos[2] - pos->_pos[2]) * (_pos[2] - pos->_pos[2]));
}



