#include "Silicon2024Template.h"


Silicon2024Template::Silicon2024Template(void) 
: Template("Silicon(001) (CASTEP 2024) Template",20) {
        
    _atomtype = 14;
    _repeat = 3.8668346;
    
    _bondmin = 2.0;
    _bondmax = 3.0;
    _bondlength = 1.4776;
    
    // ----- Template Positional Parameters --------
    
    // [0,1] proto: ( 1/2, y, z)  with 0.5 < y < 1
    
    _tparam[0] = 0.648945169; _tparam[1] = 0.0;
    
    // [2,3] proto: (   0, y, z)  with 0.5 < y < 1
    
    _tparam[2] = 0.738531374; _tparam[3] = -1.090447436;
    
    // [4]   proto: (0, 1/2, za) under dimer row
    
    _tparam[4] = -2.589906467;
    
    // [5]   proto: (0,   0, zb) in trench 
    
    _tparam[5] = -2.332670125;
    
    // [6]   proto: (1/2, 1/2, za) under dimer 
        
    _tparam[6] = -3.926506898;
    
    // [7]   proto: (1/2, 0, zb) in trench
    
    _tparam[7] = -3.739732659;
    
    // [8,9] proto: ( 1/2, y, z)  with 0.5 < y < 1
    
    _tparam[8] = 0.755673144; _tparam[9] = -5.200600144;
    
    // [10, 11] proto: (   0, y, z)  with 0.5 < y < 1
    
    _tparam[10] = 0.75421216; _tparam[11] = -6.570408025;

    // [12]   proto: (0, 1/2, za) under dimer row
    
    _tparam[12] = -7.907587125;
    
    // [13]   proto: (0,   0, zb) in trench
    
    _tparam[13] = -7.971154757;
    
    // [14]   proto: (1/2, 1/2, za) under dimer 
    
    _tparam[14] = -9.290891499;

     // [15]   proto: (1/2, 0, zb) in trench
    
    _tparam[15] = -9.333477269;
    
    // [8,9] proto: ( 1/2, y, z)  with 0.5 < y < 1
    
    _tparam[16] = 0.748735384; _tparam[17] = -10.68743;
    
    // [10, 11] proto: (   0, y, z)  with 0.5 < y < 1
    
    _tparam[18] = 0.749368111; _tparam[19] = -12.06086136;
    
    
    // ----- Dimer Buckling Parameter ---------------
    
    _buckling_up_y = 0.15;
    _buckling_up_z = 0.32;
    _buckling_down_y = -0.31;
    _buckling_down_z = -0.44;
}



Silicon2024Template::~Silicon2024Template() {
}

