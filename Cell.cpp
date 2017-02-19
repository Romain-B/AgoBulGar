//==============================
//    INCLUDES
//==============================
#include "Cell.h"

//==============================
//  DEFINITION STATIC ATTRIBUTES
//==============================
float Cell::rAA_ = 0; 
float Cell::rAB_ = 0;
float Cell::rBB_ = 0;
float Cell::rBC_ = 0;
//==============================
//    CONSTRUCTORS
//=============================
Cell::Cell(int x, int y)
{
  x_ = x;
  y_ = y;

  cA_ = 0;
  cB_ = 0;
  cC_ = 0;
}

//==============================
//    DESTRUCTOR
//==============================
Cell::~Cell(){}

//==============================
//    PUBLIC METHODS
//==============================
char Cell::whatAmI()
{
  switch(geno_)
  {
    case GenA : return 'A'; break;
    case GenB : return 'B'; break;
  }
}


//==============================
//    PROTECTED METHODS
//==============================
void Cell::set_rates(float rAA, float rAB, float rBB, float rBC)
{
  rAA_ = rAA;
  rAB_ = rAB;
  rBB_ = rBB;
  rBC_ = rBC;
}
