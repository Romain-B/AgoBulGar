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
	isEmpty_ = 1;
}

//Constructeur from position
Spot::Spot(int x, int y):x_(x),y_(y){
	cA_ = 0;
	cB_ = 0;
	cC_ = 0;
	isEmpty_ = 1;	
}

//Constructor with concentration
Spot::Spot(int x, int y, float cA, float cB, float cC):
					x_(x), y_(y), cA_(cA), cB_(cB), cC_(cC)
  {
  	isEmpty_ = 1;
  }



//==============================
//    DESTRUCTOR
//==============================
Spot::~Spot(){}
//==============================
//    PUBLIC METHODS
//==============================
//update concentration after diffusion
void Spot::c_update(float cA, float cB, float cC)
{
  cA_ = cA;
  cB_ = cB;
  cC_ = cC;
}

bool Spot::isEmpty()
{
  return isEmpty_;
}


