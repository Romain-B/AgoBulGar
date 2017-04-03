//==============================
//    INCLUDES
//==============================
#include "CellA.h"

//==============================
//  DEFINITION STATIC ATTRIBUTES
//==============================

//==============================
//    CONSTRUCTORS
//==============================
CellA::CellA():Cell()
{
 this->compute_fitness();
 geno_ = GenA;
}

CellA::CellA(float cAi, float cBi, float cCi):Cell(cAi, cBi, cCi)
{
 this->compute_fitness();
 geno_ = GenA;
}

//==============================
//    DESTRUCTOR
//==============================
CellA::~CellA(){}

//==============================
//    PUBLIC METHODS
//==============================
float* CellA::metabolism(float s_cA, float s_cB, float s_cC)
/*
Set the metalism of the cell
*/
{
  //s_cA stands for Spot cA
  //ms_cA stands for Modified Spot cA

  float  ms_cA = 0, ms_cB = 0, ms_cC = 0;

  //Diffeq

  cA_ += 0.1*(s_cA * rAA_);     //Absorb
  cB_ += 0.1*(cA_ * rAB_);      //Transform
  cA_ += 0.1*(-cA_ * rAB_);     //Remove used product

  ms_cA = -0.1*(rAA_ * s_cA);
  
  //prepare the returned array
  float* ms_c = new float[3];

  ms_c[0] = ms_cA;
  ms_c[1] = ms_cB;
  ms_c[2] = ms_cC; 

  this->compute_fitness();

  //WARNING : will need to free space in Environment calling metabolism !!
  return ms_c;

}

void CellA::compute_fitness()
/*
Update fitness
*/
{
  fit_ = (cB_ > min_fit_) ? cB_ : 0;
}


