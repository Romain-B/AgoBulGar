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
	Pmut_ = Pmut;
	Pdth_ = Pdth;
	D_ = 0.1;
	W_ = size;
	H_ = W_;
		
}

Environment::Environment()
{
  Pmut_ = 0;
  Pdth_ = 0.02;
  D_ = 0.1;
  W_ = 32;
  H_ = 32;
    
}

//==============================
//    DESTRUCTOR
//==============================
Environment::~Environment(){}

//==============================
//    PUBLIC METHODS
//==============================

//==============================
//    PROTECTED METHODS
//==============================


Spot* Environment::tl(Spot* center)
{
  //Top left : x-1 ; y+1

  int x = center->x(), y = center->y();

  int tlx, tly;

  tlx = (x > 0) ? x-1 : W_-1;
  tly = (y < H_-1) ? y+1 : 0;

  return &grid_[tlx][tly];

}

Spot* Environment::tc(Spot* center)
{
  //Top left : x ; y+1

  int x = center->x(), y = center->y();

  int tlx, tly;

  tlx = x;
  tly = (y < H_-1) ? y+1 : 0;

  return &grid_[tlx][tly];

}

Spot* Environment::tr(Spot* center)
{
  //Top left : x+1 ; y+1

  int x = center->x(), y = center->y();

  int tlx, tly;

  tlx = (x < W_-1) ? x+1 : 0;
  tly = (y < H_-1) ? y+1 : 0;

  return &grid_[tlx][tly];

}

Spot* Environment::cl(Spot* center)
{
  //Top left : x-1 ; y

  int x = center->x(), y = center->y();

  int tlx, tly;

  tlx = (x > 0) ? x-1 : W_-1;
  tly = y;

  return &grid_[tlx][tly];

}

Spot* Environment::cr(Spot* center)
{
  //Top left : x+1 ; y

  int x = center->x(), y = center->y();

  int tlx, tly;

  tlx = (x < W_-1) ? x+1 : 0;
  tly = y;

  return &grid_[tlx][tly];

}

Spot* Environment::bl(Spot* center)
{
  //Top left : x-1 ; y-1

  int x = center->x(), y = center->y();

  int tlx, tly;

  tlx = (x > 0) ? x-1 : W_-1;
  tly = (y > 0) ? y-1 : H_-1;

  return &grid_[tlx][tly];

}

Spot* Environment::bc(Spot* center)
{
  //Top left : x ; y-1

  int x = center->x(), y = center->y();

  int tlx, tly;

  tlx = x;
  tly = (y > 0) ? y-1 : H_-1;

  return &grid_[tlx][tly];

}

Spot* Environment::br(Spot* center)
{
  //Top left : x+1 ; y-1

  int x = center->x(), y = center->y();

  int tlx, tly;

  tlx = (x < W_-1) ? x+1 : 0;
  tly = (y > 0) ? y-1 : H_-1;

  return &grid_[tlx][tly];

}