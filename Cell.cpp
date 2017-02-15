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

  this->compute_fitness();

}

//==============================
//    DESTRUCTOR
//==============================
Cell::~Cell(){}

//==============================
//    PUBLIC METHODS
//==============================

//==============================
//    PROTECTED METHODS
//==============================
void Cell::compute_fitness()
{
  fit_ = cA_+cB_+cC_;
}