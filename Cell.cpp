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
float Cell::min_fit_ = 0;
//==============================
//    CONSTRUCTORS
//=============================
Cell::Cell()
{

  cA_ = 0;
  cB_ = 0;
  cC_ = 0;
}

Cell::Cell(float cAi, float cBi, float cCi)
{
  cA_ = cAi;
  cB_ = cBi;
  cC_ = cCi;
}

//==============================
//    DESTRUCTOR
//==============================
Cell::~Cell(){}

//==============================
//    PUBLIC METHODS
//==============================
char Cell::whatAmI()
/*
Give the type of the cell
*/
{
  switch(geno_)
  {
    case GenA : return 'A'; break;
    case GenB : return 'B'; break;
  }
}

void Cell::set_c(float cAi, float cBi, float cCi)
/*
Update concentration of the cell
*/
{
  cA_ = cAi;
  cB_ = cBi;
  cC_ = cCi;
  this->compute_fitness();
}


//==============================
//    PROTECTED METHODS
//==============================
void Cell::set_rates(float rAA, float rAB, float rBB, float rBC)
/*
define metabolism rates (Class fonction)
*/
{
  rAA_ = rAA;
  rAB_ = rAB;
  rBB_ = rBB;
  rBC_ = rBC;
}

void Cell::set_min_fit(float mf)
/*
set minimum fitness (Class fonction)
*/
{
  min_fit_ = mf;
}
