//==============================
//    INCLUDES
//==============================
#include "Environment.h"
#include <cstdlib>
#include <ctime>

using std::cout;


//==============================
//  DEFINITION STATIC ATTRIBUTES
//==============================

  FP Environment::around[] = {&Environment::tl, &Environment::tc, &Environment::tr,
                                &Environment::cl, &Environment::cr, &Environment::bl, 
                                &Environment::bc, &Environment::br};


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
      tmp.push_back(new Spot(x,y, Ainit_, 0,0));

      int t = rand() % 2;
      if (t)
      { 
        cells_.push_back(new CellA(x, y));
      }
      else
      {
        cells_.push_back(new CellB(x, y));
      }
      tmp[y]->set_cell(cells_[cells_.size()-1]);
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

      //Generate Spot
      tmp.push_back(new Spot(x,y, Ainit_, 0,0));

      //Generate cell randomly between A and B
      int t = rand() % 2;
      if (t)
      { 
        cells_.push_back(new CellA(x, y));
      }
      else if(y)
      {
        cells_.push_back(new CellB(x, y));
      }

      //Set Spot pointer on cell
      tmp[y]->set_cell(cells_[cells_.size()-1]);
    }
    grid_.push_back(tmp);
  }

}

//==============================
//    DESTRUCTOR
//==============================
Environment::~Environment()
{

  //Spot deletes the cells
  for (u_int x = 0; x < W_; ++x)
  {
    for (u_int y = 0; y < H_; ++y)
    {
      delete grid_[x][y];
    }
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

void Environment::run(int it)
{
  for(u_int i = 0; i < it ; i++)
  {

    for (u_int x = 0; x < W_; ++x)
    {
      for (u_int y = 0; y < H_; ++y)
      {
        this->diffusion(x, y);
      }
    }


    this->cell_death();

    //Compet for cell gaps
    //  

    //Metabolism

    float* ret;
    for (u_int x = 0; x < W_; ++x)
    {
      for (u_int y = 0; y < H_; ++y)
      {
        Spot* s = grid_[x][y];
        if (! s->isEmpty())
        {
          //Metab in cell
          ret = s->cell() ->metabolism(s->cA(), s->cB(), s->cC());
          
          //Update of ABC in Spot
          s->c_update(s->cA() + ret[0], s->cB() + ret[1], s->cC() + ret[3]);
        }
      }
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
  for (int ix = 0; ix<W_; ix++)
  {
    for (int iy = 0; iy<H_; iy++)
    {

      float reaper =  (rand()%(1000))/1000.0;

      if (!grid_[ix][iy]->isEmpty_)
      {
        if (reaper < Pdth_)
        {

          // int xdead = (*it)->x();
          // int ydead = (*it)->y();
          float ca, cb, cc;

          ca = ((*grid_[ix][iy]).cell_)->cA();
          cb = ((*grid_[ix][iy]).cell_)->cB();
          cc = ((*grid_[ix][iy]).cell_)->cC();

          grid_[ix][iy]->c_update(ca, cb, cc);

          grid_[ix][iy]->del_cell();
          free_spot_.push_back(grid_[ix][iy]);


        }
      }
    }
  }
}

void Environment::diffusion(int x , int y) //Diffusion of metabolites A,B and C
{
	
  Spot* center = grid_[x][y];

  float cA_t = center->cA();
  float cB_t = center->cB();
  float cC_t = center->cC();

  cA_t = cA_t + D_ * this->tl(center)->cA();
  cB_t = cB_t + D_ * this->tl(center)->cB();
  cC_t = cC_t + D_ * this->tl(center)->cC();

  cA_t = cA_t + D_ * this->tc(center)->cA();
  cB_t = cB_t + D_ * this->tc(center)->cB();
  cC_t = cC_t + D_ * this->tc(center)->cC();

  cA_t = cA_t + D_ * this->tr(center)->cA();
  cB_t = cB_t + D_ * this->tr(center)->cB();
  cC_t = cC_t + D_ * this->tr(center)->cC();

  cA_t = cA_t + D_ * this->bl(center)->cA();
  cB_t = cB_t + D_ * this->bl(center)->cB();
  cC_t = cC_t + D_ * this->bl(center)->cC();

  cA_t = cA_t + D_ * this->bc(center)->cA();
  cB_t = cB_t + D_ * this->bc(center)->cB();
  cC_t = cC_t + D_ * this->bc(center)->cC();

  cA_t = cA_t + D_ * this->br(center)->cA();
  cB_t = cB_t + D_ * this->br(center)->cB();
  cC_t = cC_t + D_ * this->br(center)->cC();

  cA_t = cA_t + D_ * this->cl(center)->cA();
  cB_t = cB_t + D_ * this->cl(center)->cB();
  cC_t = cC_t + D_ * this->cl(center)->cC();

  cA_t = cA_t + D_ * this->cr(center)->cA();
  cB_t = cB_t + D_ * this->cr(center)->cB();
  cC_t = cC_t + D_ * this->cr(center)->cC();

  cA_t = cA_t - 9 * D_ * cA_t;
  cB_t = cB_t - 9 * D_ * cB_t;
  cC_t = cC_t - 9 * D_ * cC_t;

  grid_[x][y]->c_update(cA_t , cB_t , cC_t);

}

void Environment::competition()
{

  grid_[5][5]->del_cell();
  free_spot_.push_back(grid_[5][5]);

  
  for(auto it = free_spot_.begin() ; it != free_spot_.end() ; ++it)
  {
    float best_fitness = 0;
    Spot* best_cell_spot = nullptr;

    //Get best cell (if any)

    for(u_int i=0 ; i < 8 ; ++i)
    {
      Spot* tmp_spot;
      tmp_spot = ((this)->*(around[i]))(*it);

      if (! tmp_spot->isEmpty() && (tmp_spot->cell())->fit() >= best_fitness ) //HERE TO ADD MIN FIT
      {
        best_cell_spot =  tmp_spot;
        best_fitness = (best_cell_spot->cell())->fit();
        printf("\nHELLO\n cell type : \t%c\n", (tmp_spot->cell())->whatAmI());
      }
    }

    if (best_cell_spot != nullptr)
    {
      //Division
        //mutation, répartition ABC

      //Erase it
    }
    //free_spot_.erase()

  }

}

void Environment::cell_division(Spot* mother, Spot* daughter)
{
  float n_cA, n_cB, n_cC;

  n_cA = ((mother->cell())->cA())/2;
  n_cB = ((mother->cell())->cB())/2;
  n_cC = ((mother->cell())->cC())/2;

  char g_mother = (mother->cell())->whatAmI();

  float change = (rand()%(1000))/1000.0;

  if (change < Pmut_)
  {
    switch(g_mother)
    {
      case 'A': 
      delete mother->cell();

    }

  }


}

