//==============================
//    INCLUDES
//==============================
#include "Environment.h"

//==============================
//  DEFINITION STATIC ATTRIBUTES
//==============================

//==============================
//    CONSTRUCTORS
//==============================

Environment::Environment(float R , float Pmut , float Pdth , int size , float Wmin , int Ainit)
{
	Pmut_ = 0;
	Pdth_ = 0.02;
	D_ = 0.1;
	W_ = size;
	H_ = W_;
		
}


//==============================
//    DESTRUCTOR
//==============================

//==============================
//    PUBLIC METHODS
//==============================
