//==============================
//    INCLUDES
//==============================
#include "Environment.h"
#include <cstdlib>
#include <ctime>



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

  Ainit_ = Ainit;

  srand(time(0));

  for (u_int x = 0; x < W_; ++x)
  {
    vector<Spot*> tmp;
    for (u_int y = 0; y < H_; ++y)
    {
      tmp.push_back(new Spot(x,y));

      int t = rand() % 2;
      if (t)
      { 
        cells_.push_back(new CellA(x, y));
      }
      else
      {
        cells_.push_back(new CellB(x, y));
      }
    }
    grid_.push_back(tmp);
  }
		
}

Environment::Environment()
{
  Pmut_ = 0;
  Pdth_ = 0.02;
  D_ = 0.1;
  W_ = 32;
  H_ = 32;

  Ainit_ = 25;

  srand(time(0));

  
  for (u_int x = 0; x < W_; ++x)
  {
    vector<Spot*> tmp;
    for (u_int y = 0; y < H_; ++y)
    {
      tmp.push_back(new Spot(x,y));

      int t = rand() % 2;
      if (t)
      { 
        cells_.push_back(new CellA(x, y));
      }
      else
      {
        cells_.push_back(new CellB(x, y));
      }
    }
    grid_.push_back(tmp);
  }

}

//==============================
//    DESTRUCTOR
//==============================
Environment::~Environment()
{
  for (u_int x = 0; x < W_; ++x)
  {
    for (u_int y = 0; y < H_; ++y)
    {
      delete grid_[x][y];
    }
  }

  for(u_int i = 0; i < cells_.size() ; i++)
  {
    delete cells_[i];
  }
}

//==============================
//    PUBLIC METHODS
//==============================

void Environment::env_wipe()
{
  for (u_int x = 0; x < W_; ++x)
  {
    for (u_int y = 0; y < H_; ++y)
    {
      grid_[x][y]->c_update(Ainit_, 0, 0);
    }
  }
}

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

  return grid_[tlx][tly];

}

Spot* Environment::tc(Spot* center)
{
  //Top Center : x ; y+1

  int x = center->x(), y = center->y();

  int tcx, tcy;

  tcx = x;
  tcy = (y < H_-1) ? y+1 : 0;

  return grid_[tcx][tcy];

}

Spot* Environment::tr(Spot* center)
{
  //Top right : x+1 ; y+1

  int x = center->x(), y = center->y();

  int trx, try_;

  trx = (x < W_-1) ? x+1 : 0;
  try_ = (y < H_-1) ? y+1 : 0;

  return grid_[trx][try_];

}

Spot* Environment::cl(Spot* center)
{
  //Center left : x-1 ; y

  int x = center->x(), y = center->y();

  int clx, cly;

  clx = (x > 0) ? x-1 : W_-1;
  cly = y;

  return grid_[clx][cly];

}

Spot* Environment::cr(Spot* center)
{
  //Top left : x+1 ; y

  int x = center->x(), y = center->y();

  int crx, cry;

  crx = (x < W_-1) ? x+1 : 0;
  cry = y;

  return grid_[crx][cry];

}

Spot* Environment::bl(Spot* center)
{
  //Top left : x-1 ; y-1

  int x = center->x(), y = center->y();

  int blx, bly;

  blx = (x > 0) ? x-1 : W_-1;
  bly = (y > 0) ? y-1 : H_-1;

  return grid_[blx][bly];

}

Spot* Environment::bc(Spot* center)
{
  //Top left : x ; y-1

  int x = center->x(), y = center->y();

  int bcx, bcy;

  bcx = x;
  bcy = (y > 0) ? y-1 : H_-1;

  return grid_[bcx][bcy];

}

Spot* Environment::br(Spot* center)
{
  //Top left : x+1 ; y-1

  int x = center->x(), y = center->y();

  int brx, bry;

  brx = (x < W_-1) ? x+1 : 0;
  bry = (y > 0) ? y-1 : H_-1;

  return grid_[brx][bry];

}


//Cellular Death
void Environment::cell_death()
{
  for (auto it = cells_.begin(); it!= cells_.end();++it)
  {
    float reaper =  (rand()%(1000))/1000.0;
    if (reaper < Pdth_)
    {

      int xdead = (*it)->x();
      int ydead = (*it)->y();
      float ca, cb, cc;
      ca = (*it)->cA();
      cb = (*it)->cB();
      cc = (*it)->cC();

      grid_[xdead][ydead]->c_update(ca, cb, cc);

      cells_.erase(it);
      free_spot_.push_back(grid_[xdead][ydead]);

    }
  }
}


void Environment::diffusion(int x , int y) //Diffusion of metabolites A,B and C
{
	float cA_t = (grid_[x][y])->cA();
	float cB_t = (grid_[x][y])->cB();
	float cC_t = (grid_[x][y])->cC();

	cA_t = cA_t + D_ * this->tl(grid_[x][y])->cA();
	cB_t = cB_t + D_ * this->tl(grid_[x][y])->cB();
	cC_t = cC_t + D_ * this->tl(grid_[x][y])->cC();

	cA_t = cA_t + D_ * this->tc(grid_[x][y])->cA();
	cB_t = cB_t + D_ * this->tc(grid_[x][y])->cB();
	cC_t = cC_t + D_ * this->tc(grid_[x][y])->cC();

	cA_t = cA_t + D_ * this->tr(grid_[x][y])->cA();
	cB_t = cB_t + D_ * this->tr(grid_[x][y])->cB();
	cC_t = cC_t + D_ * this->tr(grid_[x][y])->cC();

	cA_t = cA_t + D_ * this->bl(grid_[x][y])->cA();
	cB_t = cB_t + D_ * this->bl(grid_[x][y])->cB();
	cC_t = cC_t + D_ * this->bl(grid_[x][y])->cC();

	cA_t = cA_t + D_ * this->bc(grid_[x][y])->cA();
	cB_t = cB_t + D_ * this->bc(grid_[x][y])->cB();
	cC_t = cC_t + D_ * this->bc(grid_[x][y])->cC();

	cA_t = cA_t + D_ * this->br(grid_[x][y])->cA();
	cB_t = cB_t + D_ * this->br(grid_[x][y])->cB();
	cC_t = cC_t + D_ * this->br(grid_[x][y])->cC();

	cA_t = cA_t + D_ * this->cl(grid_[x][y])->cA();
	cB_t = cB_t + D_ * this->cl(grid_[x][y])->cB();
	cC_t = cC_t + D_ * this->cl(grid_[x][y])->cC();

	cA_t = cA_t + D_ * this->cr(grid_[x][y])->cA();
	cB_t = cB_t + D_ * this->cr(grid_[x][y])->cB();
	cC_t = cC_t + D_ * this->cr(grid_[x][y])->cC();

	cA_t = cA_t - 9 * D_ * cA_t;
	cB_t = cB_t - 9 * D_ * cB_t;
	cC_t = cC_t - 9 * D_ * cC_t;

	grid_[x][y]->c_update(cA_t , cB_t , cC_t);

}

void Environment::competition()
{
	for(auto it = free_spot_.begin() ; it != free_spot_.end() ; ++it)
	{
		
	}

}
