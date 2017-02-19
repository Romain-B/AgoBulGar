//==============================
//    INCLUDES
//==============================
#include "CellA.h"
#include "Cell.h"

//==============================
//  DEFINITION STATIC ATTRIBUTES
//==============================

//==============================
//    CONSTRUCTORS
//==============================
CellA::CellA(int x, int y):Cell(x,y)
{
 this->compute_fitness();
}

//==============================
//    DESTRUCTOR
//==============================
CellA::~CellA(){}

//==============================
//    PUBLIC METHODS
//==============================
float* CellA::metabolism(float csA, float csB, float csC)
{
  return &csA;
}

void CellA::compute_fitness()
{
  fit_ = cB_;
}