#ifndef INCL_POSITION
#define INCL_POSITION

class Position {

 private:

  double _pos[3];

 public:

  Position(void);

  Position(const Position *pos);

  Position(double x, double y, double z);

  Position(double *pos);

  ~Position();

  Position *clone(void) const {
    return new Position(this);
  }

  double getElement(const int i) const {
    return _pos[i];
  }

  Position *setTo(double x,double y,double z);

  Position *setTo(const Position *pos);

  Position *addTo(const Position *pos);
    
    Position *addTo(double x,double y,double z);  

  Position *subTo(const Position *pos);
  
  Position *multTo(double factor);

  Position *multTo(double xfactor, double yfactor, double zfactor); 

  bool isEqualTo(const Position *pos, double thresh=1e-5);
    
    double distanceTo(const Position *pos) const;  
 
};

#endif

