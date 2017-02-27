//==============================
//    INCLUDES
//==============================
#include "Spot.h"

//==============================
//  DEFINITION STATIC ATTRIBUTES
//==============================

//==============================
//    CONSTRUCTORS
//=============================
//default constructeur
Spot::Spot(){
	x_ = 0;
	y_ = 0;
	cA_ = 0;
	cB_ = 0;
	cC_ = 0;
	isEmpty_ = 0;
}

//Constructeur from position
Spot::Spot(int x, int y):x_(x),y_(y){
	cA_ = 0;
	cB_ = 0;
	cC_ = 0;
	isEmpty_ = 0;	
}



//==============================
//    DESTRUCTOR
//==============================
Spot::~Spot(){}
//==============================
//    PUBLIC METHODS
//==============================
