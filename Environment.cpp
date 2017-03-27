//==============================
//    INCLUDES
//==============================
#include "Environment.h"
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using std::cout;

//the following are UBUNTU/LINUX ONLY terminal color codes.
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDREDBG     "\033[1m\033[31;41m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDGREENBG   "\033[1m\033[32;42m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDBLUEBG   "\033[1m\033[34;44m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


//==============================
//  DEFINITION STATIC ATTRIBUTES
//==============================

FP Environment::around[] = {&Environment::tl, &Environment::tc, &Environment::tr,
  &Environment::cl, &Environment::cr, &Environment::bl, 
  &Environment::bc, &Environment::br};


//==============================
//    CONSTRUCTORS
//==============================

  Environment::Environment(float R , float Pmut , float Pdth , int size , float Wmin , float Ainit)
  {
   Pmut_ = Pmut;
   Pdth_ = Pdth;
   D_ = 0.1;
   W_ = size;
   H_ = W_;
   nbA_ = 0;
   

   Ainit_ = Ainit;

   srand(time(0));

   Cell::set_rates(R,R,R,R);
   Cell::set_min_fit(Wmin);



   vector<Spot*> tmp;
   Cell* c;
   int t;

   for (u_int x = 0; x < W_; ++x)
   {

    tmp.clear();
    for (u_int y = 0; y < H_; ++y)
    {
      tmp.push_back(new Spot(x,y, Ainit_, 0,0));

      c = nullptr;
      t = rand() % 2;

      if (t)
      { 
        c = new CellA();
        ++nbA_;
      }
      else
      {
        c = new CellB();
      }
      tmp[y]->set_cell(c);

    }
    grid_.push_back(tmp);
  }

}

Environment::Environment()
{
  Pmut_ = 0.02;
  Pdth_ = 0.1;
  D_ = 0.1;
  W_ = 32;
  H_ = 32;
  nbA_ = 0;

  Ainit_ = 25;

  srand(time(0));

  Cell::set_rates(0.1,0.1,0.1,0.1);
  //Cell::set_min_fit(0.01);

  vector<Spot*> tmp;
  Cell* c;
  int t;
  
  for (u_int x = 0; x < W_; ++x)
  {
    tmp.clear();
    for (u_int y = 0; y < H_; ++y)
    {

      //Generate Spot
      tmp.push_back(new Spot(x,y, Ainit_, 0,0));
      
      //Generate cell randomly between A and B
      c = nullptr;
      t = rand() % 2;
      if (t)
      { 
        c = new CellA();
        ++nbA_;
      }
      else
      {
        c = new CellB();
      }

      //Set Spot pointer on cell
      tmp[y]->set_cell(c);
      
    }
    grid_.push_back(tmp);
  }

}

//==============================
//    DESTRUCTOR
//==============================
Environment::~Environment()
{
  auto it = free_spot_.begin();
  while(it != free_spot_.end())
  {
    free_spot_.erase(it);
  }
  
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
  /*
  Resets the metabolites in grid to (Ainit,0,0)
  No alteration of Cell
  */

  for (u_int x = 0; x < W_; ++x)
  {
    for (u_int y = 0; y < H_; ++y)
    {
      grid_[x][y]->c_update(Ainit_, 0, 0);
    }
  }
}

void Environment::run(int it, int T)
{
  /*
  General execution of Environment for 'it' iterations and wipes
  every 'T' steps.

  1- diffuses the metabolites in grid
  2- kills cells according to Pmut_
  3- competition for empty spots (and division)
  4- metabolism
  */

  for(u_int i = 0; i < it ; i++)
  {

    //Diffusion 
    for (u_int x = 0; x < W_; ++x)
    {
      for (u_int y = 0; y < H_; ++y)
      {
        this->diffusion(x, y);
      }
    }
    for (u_int x = 0; x < W_; ++x)
    {
      for (u_int y = 0; y < H_; ++y)
      {
        grid_[x][y]->time_update();
      }
    }

    //Cell death
    this->cell_death(); 

    //Competition
    this->competition(); 

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
          s->c_update(s->cA() + ret[0], s->cB() + ret[1], s->cC() + ret[2]);
          delete ret;
        }
      }
    }

    if (T != 0 && 0 == i%T)
    {
      this-> env_wipe();
    }
 
  }


}

void Environment::print_grid()
{
  /*
  Displays the colored grid of cells and 
  -Number of A
  -Number of B
  -Mean fitness of A
  -Mean fitness of B
  -Total of A metabolites in grid
  -Total of B metabolites in grid
  -Total of C metabolites in grid
  */

  int iA = 0, iB = 0, iE = 0;
  float tA = 0, tB = 0, tC = 0;
  float m_fitA = 0.0, m_fitB = 0.0;

  std::system("clear");
  cout << "\n\t GRID OF "<<W_<<" BY "<<H_<<"\n--------------------\n";
  
  for(u_int y = 0; y < H_ ; ++y)
  {
    cout <<"\n\t";

    for(u_int x = 0; x < W_ ; ++x)
    {
      tA += grid_[x][y]->cA();
      tB += grid_[x][y]->cB();
      tC += grid_[x][y]->cC();

      if(! grid_[x][y]->isEmpty())
      {
        if ('A' == grid_[x][y]->cell()->whatAmI())
        {
          cout << BOLDBLUEBG <<"A "<<RESET;
          ++iA;
          m_fitA += grid_[x][y]->cell()->fit();
        }
        if ('B' == grid_[x][y]->cell()->whatAmI())
        {
          cout << BOLDREDBG <<"B "<<RESET;
          ++iB;
          m_fitB += grid_[x][y]->cell()->fit();
        }
      }
      else
      {
        cout << BOLDGREENBG << ". "<<RESET;
        ++iE;
      }

    }
  }
  m_fitA = m_fitA/iA;
  m_fitB = m_fitB/iB;

  cout <<BOLDBLUE<<"\n\n\tCellA :\t"<<iA<<BOLDRED<<"\n\tCellB :\t"<<iB<< BOLDGREEN <<"\n\tEmpty :\t"<<iE<<"\n"<<RESET;
  cout <<BOLDBLUE<<"\n\n\tMean fitness of A :\t"<<m_fitA<<BOLDRED<<"\n\tMean fitness of B :\t"<<m_fitB<<RESET;

  cout << "\n\nMetabolites on grid :";
  cout <<"\n\tTotal of A :\t"<<tA<<"\n\tTotal of B :\t"<<tB<<"\n\tTotal of C :\t"<<tC<<"\n";

}

int Environment::proportion()
{
  /*
  Returns the state of the system :
  1 if cohabitation
  -1 if exclusion of B
  0 if extinction
  */

  if (nbA_ == 0){return 0;}

  for(u_int y = 0; y < H_ ; ++y)
  {

    for(u_int x = 0; x < W_ ; ++x)
    {

      if(!grid_[x][y]->isEmpty())
      {
        if ('B' == grid_[x][y]->cell()->whatAmI())
        {
         return 1;
       }
     }
   }
 }

  return -1;
}

//==============================
//    PROTECTED METHODS
//==============================


Spot* Environment::tl(Spot* center)
{
  /*Top left : x-1 ; y+1*/

  int x = center->x(), y = center->y();

  int tlx, tly;

  tlx = (x > 0) ? x-1 : W_-1;
  tly = (y < H_-1) ? y+1 : 0;

  return grid_[tlx][tly];

}

Spot* Environment::tc(Spot* center)
{
  /*Top Center : x ; y+1*/

  int x = center->x(), y = center->y();

  int tcx, tcy;

  tcx = x;
  tcy = (y < H_-1) ? y+1 : 0;

  return grid_[tcx][tcy];

}

Spot* Environment::tr(Spot* center)
{
  /*Top right : x+1 ; y+1*/

  int x = center->x(), y = center->y();

  int trx, try_;

  trx = (x < W_-1) ? x+1 : 0;
  try_ = (y < H_-1) ? y+1 : 0;

  return grid_[trx][try_];

}

Spot* Environment::cl(Spot* center)
{
  /*Center left : x-1 ; y*/

  int x = center->x(), y = center->y();

  int clx, cly;

  clx = (x > 0) ? x-1 : W_-1;
  cly = y;

  return grid_[clx][cly];

}

Spot* Environment::cr(Spot* center)
{
  /*Center right : x+1 ; y*/

  int x = center->x(), y = center->y();

  int crx, cry;

  crx = (x < W_-1) ? x+1 : 0;
  cry = y;

  return grid_[crx][cry];

}

Spot* Environment::bl(Spot* center)
{
  /*Bottom left : x-1 ; y-1*/

  int x = center->x(), y = center->y();

  int blx, bly;

  blx = (x > 0) ? x-1 : W_-1;
  bly = (y > 0) ? y-1 : H_-1;

  return grid_[blx][bly];

}

Spot* Environment::bc(Spot* center)
{
  /*Bottom center : x ; y-1*/

  int x = center->x(), y = center->y();

  int bcx, bcy;

  bcx = x;
  bcy = (y > 0) ? y-1 : H_-1;

  return grid_[bcx][bcy];

}

Spot* Environment::br(Spot* center)
{
  /*Bottom right : x+1 ; y-1*/

  int x = center->x(), y = center->y();

  int brx, bry;

  brx = (x < W_-1) ? x+1 : 0;
  bry = (y > 0) ? y-1 : H_-1;

  return grid_[brx][bry];

}


void Environment::cell_death()
{
  /*
  Kills cells according to Pmut_
  */
  
  for (u_int ix = 0; ix < W_; ++ix)
  {
    for (u_int iy = 0; iy < H_; ++iy)
    {

      float reaper =  (rand()%(1000))/1000.0;

      if (! grid_[ix][iy]->isEmpty() && reaper < Pdth_)
      {
        float ca = grid_[ix][iy]->cA(), 
        cb = grid_[ix][iy]->cB(), 
        cc = grid_[ix][iy]->cC();

        ca += ((grid_[ix][iy])->cell())->cA();
        cb += ((grid_[ix][iy])->cell())->cB();
        cc += ((grid_[ix][iy])->cell())->cC();
        grid_[ix][iy]->c_update(ca, cb, cc);

        if (grid_[ix][iy]->cell()->whatAmI()=='A'){--nbA_;}

        grid_[ix][iy]->del_cell();
        free_spot_.push_back(grid_[ix][iy]); 
      }
    }
  }
}

void Environment::diffusion(int x , int y) 
{
  /*
  Diffusion of metabolites A,B and C according to Moore's algorithm
  */
	
  Spot* center = grid_[x][y];

  float cA_t = center->cA();
  float cB_t = center->cB();
  float cC_t = center->cC();

  for(u_int i = 0 ; i < 8 ; ++i)
  {

    cA_t += D_ * (this->*around[i])(center)->cA();
    cB_t += D_ * (this->*around[i])(center)->cB();
    cC_t += D_ * (this->*around[i])(center)->cC();
  }

  cA_t = cA_t - 8 * D_ * center->cA();
  cB_t = cB_t - 8 * D_ * center->cB();
  cC_t = cC_t - 8 * D_ * center->cC();


  //modification of A,B,C at t1, NOT t
  grid_[x][y]->ct1_update(cA_t , cB_t , cC_t);

}

void Environment::competition()
{  
  /*
  Competition for division in free spots, based on cell fitness.
  */

  for(auto it = free_spot_.begin(); it != free_spot_.end() ;)
  {
    float best_fitness = 0;
    Spot* best_cell_spot = nullptr;

    //Get best cell (if any)

    for(u_int i=0 ; i < 8 ; ++i)
    {
      Spot* tmp_spot;
      tmp_spot = ((this)->*(around[i]))(*it);

      if (! tmp_spot->isEmpty() && (tmp_spot->cell())->fit() > best_fitness) //HERE TO ADD MIN FIT
      {
        best_cell_spot =  tmp_spot;
        best_fitness = (best_cell_spot->cell())->fit();
      }
    }

    //Divide if a cell was chosen
    if (best_cell_spot != nullptr)
    {
      this->cell_division(best_cell_spot , *it);
      //cout << "\nHello "<<(*it)->cell() ->whatAmI();

      //remove the spot from the free_spot_ list
      free_spot_.erase(it);
    }
    else
    {
      ++it;
    }

  }

}

void Environment::cell_division(Spot* mother, Spot* daughter)
{
  float n_cA, n_cB, n_cC;

  n_cA = ((mother->cell())->cA())/2;
  n_cB = ((mother->cell())->cB())/2;
  n_cC = ((mother->cell())->cC())/2;

  char g_mother = (mother->cell())->whatAmI();



  switch(g_mother)
  {
    case 'A':daughter->set_cell(new CellA(n_cA, n_cB, n_cC)); nbA_++;
    break;
    case 'B':daughter->set_cell(new CellB(n_cA, n_cB, n_cC)); 
    break;
  }
  
  (mother->cell())->set_c(n_cA, n_cB, n_cC);

  float change = (rand()%(1000))/1000.0;
  if (change < Pmut_)
  {
    this->cell_mutation(mother);
  }

  change = (rand()%(1000))/1000.0;
  if (change < Pmut_)
  {
    this->cell_mutation(daughter);
  }

}

void Environment::cell_mutation(Spot* c)
{
  float n_cA, n_cB, n_cC;

  n_cA = (c->cell())->cA();
  n_cB = (c->cell())->cB();
  n_cC = (c->cell())->cC();


  char g_cell = (c->cell())->whatAmI();

  switch(g_cell)
  {
    case 'A': 
    nbA_--;
    c->del_cell();
    c->set_cell(new CellB(n_cA, n_cB, n_cC));
    break;
    case 'B':
    nbA_++;
    c->del_cell();
    c->set_cell(new CellA(n_cA, n_cB, n_cC));break;
    break;


  }

}




