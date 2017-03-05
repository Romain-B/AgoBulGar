//==============================
//    INCLUDES
//==============================
#include "CellB.h"

//==============================
//  DEFINITION STATIC ATTRIBUTES
//==============================

//==============================
//    CONSTRUCTORS
//==============================
CellB::CellB():Cell()
{
 this->compute_fitness();
 geno_ = GenB;
}

CellB::CellB(float cAi, float cBi, float cCi):Cell(cAi, cBi, cCi)
{
 this->compute_fitness();
 geno_ = GenB;
}

//==============================
//    DESTRUCTOR
//==============================
CellB::~CellB(){}

//==============================
//    PUBLIC METHODS
//==============================
float* CellB::metabolism(float s_cA, float s_cB, float s_cC)
{
  //s_cA stands for Spot cA
  //ms_cA stands for Modified Spot cA

  float  ms_cA = 0, ms_cB = 0, ms_cC = 0;

  //Diffeq

  cC_ += 0.1*(cB_ * rBC_;
  cB_ += 0.1*(s_cB * rBB_ -cB_ * rBC_;

  ms_cB = -0.1*(rBB_ * s_cB);

  //prepare the returned array
  float* ms_c = new float[3];

  ms_c[0] = ms_cA;
  ms_c[1] = ms_cB;
  ms_c[2] = ms_cC; 

  this->compute_fitness();

  //WARNING : will need to free space in Environment calling metabolism !!
  return ms_c;

}

void CellB::compute_fitness()
{
  fit_ = cC_;
}