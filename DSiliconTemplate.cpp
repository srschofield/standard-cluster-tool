#include "DSiliconTemplate.h"


DSiliconTemplate::DSiliconTemplate(void) 
: Template("DMol3 Silicon(001) Template",20) {
        
    _atomtype = 14;
    _repeat = 3.870202;
    
    _bondmin = 2.0;
    _bondmax = 3.0;
    _bondlength = 1.49;
    
    // ----- Template Positional Parameters --------
    
    // [0,1] proto: ( 1/2, y, z)  with 0.5 < y < 1
    
    _tparam[0] = 0.656479; _tparam[1] = 0.0;
    
    // [2,3] proto: (   0, y, z)  with 0.5 < y < 1
    
    _tparam[2] = 0.735554; _tparam[3] = -1.225155;
    
    // [4]   proto: (0, 1/2, za) under dimer row
    
    _tparam[4] = -2.728919;
    
    // [5]   proto: (0,   0, zb) in trench 
    
    _tparam[5] = -2.468132;
    
    // [6]   proto: (1/2, 1/2, za) under dimer 
        
    _tparam[6] = -4.055784;
    
    // [7]   proto: (1/2, 0, zb) in trench
    
    _tparam[7] = -3.873386;
    
    // [8,9] proto: ( 1/2, y, z)  with 0.5 < y < 1
    
    _tparam[8] = 0.755311; _tparam[9] = -5.331447;
    
    // [10, 11] proto: (   0, y, z)  with 0.5 < y < 1
    
    _tparam[10] = 0.753868; _tparam[11] = -6.698465;

    // [12]   proto: (0, 1/2, za) under dimer row
    
    _tparam[12] = -8.040053;
    
    // [13]   proto: (0,   0, zb) in trench
    
    _tparam[13] = -8.092237;
    
    // [14]   proto: (1/2, 1/2, za) under dimer 
    
    _tparam[14] = -9.416280;

     // [15]   proto: (1/2, 0, zb) in trench
    
    _tparam[15] = -9.451977;
    
    // [8,9] proto: ( 1/2, y, z)  with 0.5 < y < 1
    
    _tparam[16] = 0.748983; _tparam[17] = -10.802016;
    
    // [10, 11] proto: (   0, y, z)  with 0.5 < y < 1
    
    _tparam[18] = 0.749243; _tparam[19] = -12.169537;
    
    // ----- Dimer Buckling Parameter ---------------
    
    _buckling_up_y = 0.15;
    _buckling_up_z = 0.32;
    _buckling_down_y = -0.31;
    _buckling_down_z = -0.44;
}



DSiliconTemplate::~DSiliconTemplate() {
}

