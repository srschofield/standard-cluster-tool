#include "SiliconTemplate.h"


SiliconTemplate::SiliconTemplate(void) 
: Template("Silicon(001) Template",20) {
        
    _atomtype = 14;
    _repeat = 3.838418;
    
    _bondmin = 2.0;
    _bondmax = 3.0;
    _bondlength = 1.49;
    
    // ----- Template Positional Parameters --------
    
    // [0,1] proto: ( 1/2, y, z)  with 0.5 < y < 1
    
    _tparam[0] = 0.65674; _tparam[1] = 0.0;
    
    // [2,3] proto: (   0, y, z)  with 0.5 < y < 1
    
    _tparam[2] = 0.73501; _tparam[3] = -1.23481;
    
    // [4]   proto: (0, 1/2, za) under dimer row
    
    _tparam[4] = -2.75008;
    
    // [5]   proto: (0,   0, zb) in trench 
    
    _tparam[5] = -2.48026;
    
    // [6]   proto: (1/2, 1/2, za) under dimer 
        
    _tparam[6] = -4.08838;
    
    // [7]   proto: (1/2, 0, zb) in trench
    
    _tparam[7] = -3.89289;
    
    // [8,9] proto: ( 1/2, y, z)  with 0.5 < y < 1
    
    _tparam[8] = 0.75631; _tparam[9] = -5.36582;
    
    // [10, 11] proto: (   0, y, z)  with 0.5 < y < 1
    
    _tparam[10] = 0.75455; _tparam[11] = -6.74308;

    // [12]   proto: (0, 1/2, za) under dimer row
    
    _tparam[12] = -8.08830;
    
    // [13]   proto: (0,   0, zb) in trench
    
    _tparam[13] = -8.15307;
    
    // [14]   proto: (1/2, 1/2, za) under dimer 
    
    _tparam[14] = -9.47663;

     // [15]   proto: (1/2, 0, zb) in trench
    
    _tparam[15] = -9.52270;
    
    // [8,9] proto: ( 1/2, y, z)  with 0.5 < y < 1
    
    _tparam[16] = 0.74851; _tparam[17] = -10.87850;
    
    // [10, 11] proto: (   0, y, z)  with 0.5 < y < 1
    
    _tparam[18] = 0.74888; _tparam[19] = -12.25946;
    
    
    // ----- Dimer Buckling Parameter ---------------
    
    _buckling_up_y = 0.15;
    _buckling_up_z = 0.32;
    _buckling_down_y = -0.31;
    _buckling_down_z = -0.44;
}



SiliconTemplate::~SiliconTemplate() {
}

