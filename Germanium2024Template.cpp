#include "Germanium2024Template.h"


Germanium2024Template::Germanium2024Template(void) 
: Template("Germanium(001) (CASTEP 2024) Template",20) {
        
    _atomtype = 32;
    _repeat = 4.074493;
    
    _bondmin = 2.1;
    _bondmax = 3.1;
    _bondlength = 1.5397;
    
    // ----- Template Positional Parameters --------
    
    // [0,1] proto: ( 1/2, y, z)  with 0.5 < y < 1
    
    _tparam[0] = 0.658794531; _tparam[1] = 0.0;
    
    // [2,3] proto: (   0, y, z)  with 0.5 < y < 1
    
    _tparam[2] = 0.744483368; _tparam[3] = -1.252179743;
    
    // [4]   proto: (0, 1/2, za) under dimer row
    
    _tparam[4] = -2.788678358;
    
    // [5]   proto: (0,   0, zb) in trench 
    
    _tparam[5] = -2.631653343;
    
    // [6]   proto: (1/2, 1/2, za) under dimer 
        
    _tparam[6] = -4.221161494;
    
    // [7]   proto: (1/2, 0, zb) in trench
    
    _tparam[7] = -4.1056703;
    
    // [8,9] proto: ( 1/2, y, z)  with 0.5 < y < 1
    
    _tparam[8] = 0.753209538; _tparam[9] = -5.609160679;
    
    // [10, 11] proto: (   0, y, z)  with 0.5 < y < 1
    
    _tparam[10] = 0.75234824; _tparam[11] = -7.059846113;

    // [12]   proto: (0, 1/2, za) under dimer row
    
    _tparam[12] = -8.488930333;
    
    // [13]   proto: (0,   0, zb) in trench
    
    _tparam[13] = -8.525643904;
    
    // [14]   proto: (1/2, 1/2, za) under dimer 
    
    _tparam[14] = -9.944789336;

     // [15]   proto: (1/2, 0, zb) in trench
    
    _tparam[15] = -9.965814511;
    
    // [8,9] proto: ( 1/2, y, z)  with 0.5 < y < 1
    
    _tparam[16] = 0.749589222; _tparam[17] = -11.40220071;
    
    // [10, 11] proto: (   0, y, z)  with 0.5 < y < 1
    
    _tparam[18] = 0.749960284; _tparam[19] = -12.84561667;
    
    
    // ----- Dimer Buckling Parameter ---------------
    
    _buckling_up_y = 0.15;
    _buckling_up_z = 0.32;
    _buckling_down_y = -0.31;
    _buckling_down_z = -0.44;
}



Germanium2024Template::~Germanium2024Template() {
}

