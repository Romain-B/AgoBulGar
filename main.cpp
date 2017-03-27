//==============================
//    INCLUDES
//==============================

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <unistd.h>

using std::cout;
using std::fstream;


#include "Environment.h"
#include "Spot.h"
#include "Cell.h"
#include "CellA.h"
#include "CellB.h"

#define RESET   "\033[0m"

#define BOLDRED     "\033[1m\033[31m"         /* Bold Red */
#define BOLDREDBG   "\033[1m\033[31;41m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"         /* Bold Green */
#define BOLDGREENBG "\033[1m\033[32;42m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"         /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"         /* Bold Blue */
#define BOLDBLUEBG  "\033[1m\033[34;44m"      /* Bold Blue */

//==============================
//    FUNCTION DECLARATION
//==============================
void print_cell_info(Cell* cell, int nb)
{
  cout << "\n Info on cell "<< nb <<"\n---------\n";

  cout << "\n Cell type :\t"<< cell->whatAmI();

  cout << "\n cA, cB, cC :\t" << cell->cA() << ","
                                     << cell->cB() << ","
                                     << cell->cC();

  cout << "\n fitness : \t" << cell->fit();
  cout << "\n Metabolim rates rAA, rAB, rBB, rBC : \t" << cell->rAA() << ","
                                                        << cell->rAB() << ","
                                                        << cell->rBB() << ","
                                                        << cell->rBC();
  cout << "\n----------------------\n";
}

void print_spot_info(Spot* spot, int nb)
{
  cout << "\n Info on spot "<< nb <<"\n---------\n";
  cout << "\n x,y :\t" << spot->x() << "," 
                              << spot->y();
  
  cout << "\n cA, cB, cC :\t" << spot->cA() << ","
                                     << spot->cB() << ","
                                     << spot->cC()<<"\n"; 
}


  //-------------
  //    TESTS
  //-------------

  void test_cell()
  {
    cout << "\n\t===============\n\tCELL TESTS\n\t===============\n";

    Cell* cell_1 = new CellA(0,0,0);
    Cell* cell_2 = new CellB(0,5,12.5);

    float A=12.3, B=10.2, C=2.5;

    cell_1 -> set_rates(0.1,0.1,0.1,0.1);

    print_cell_info(cell_1, 1);
    print_cell_info(cell_2, 2);

    float* s_c;

    //Metabolism test for CellA

    for(u_int i=0; i<3; ++i)
    {
      s_c = cell_1->metabolism(A,B,C);
      cout << "\n returned from metabolism :\t" << s_c[0] << "," << s_c[1] << "," << s_c[2];

      A += s_c[0];
      B += s_c[1];
      C += s_c[2];

      cout << "\n A, B, C \t" << A << "," << B << "," << C;
      cout <<"\n++++++++++\n";

      print_cell_info(cell_1, 1);
      delete [] s_c;
    }

    for(u_int i=0; i<3; ++i)
    {
      s_c = cell_2->metabolism(A,B,C);
      cout << "\n returned from metabolism :\t"<< s_c[0] << "," << s_c[1] << "," << s_c[2];

      A += s_c[0];
      B += s_c[1];
      C += s_c[2];

      cout << "\n A, B, C \t" << A << "," << B << "," << C;
      cout <<"\n++++++++++\n";


      print_cell_info(cell_2, 2);
      delete [] s_c;
    }

    
    delete cell_1;
    delete cell_2;
  }

  void test_spot()
  {
  
    cout << "\n\t===============\n\tSPOT TESTS\n\t===============\n";

    Spot* spot_1 = new Spot(0,0);
    Spot* spot_2 = new Spot(0,1);

    print_spot_info(spot_1, 1);
    print_spot_info(spot_2, 2);
  }

  void write_csv()
  {
    int iteration = 100;

    cout << "\n\t===============\n\tCSV TESTS\n\t===============\n";

    for (int i_Ainit = 0; i_Ainit < 50; ++i_Ainit ){

      for (int i_wipeT = 0; i_wipeT < 1500; i_wipeT+= 10){

        Environment env(0.1, 0.0, 0.02, 32, 0, i_Ainit);
        env.run(iteration, i_wipeT);
        int prop = env.proportion();
        cout << "A_init= "<<i_Ainit<<"; wipe_T = "<<i_wipeT<<"\n";
      }
    }
    
    cout << "\nDone.\n";

  }
void show_progress(int Amax, int Tmax, int Ai, int Ti, int T, int A, int st, float duration)
{
  int nb_it = (Amax/Ai+1) * (Tmax/Ti+1);
  int pos = (A/Ai)*31 + T/Ti+1;

  cout<<"\nAinit : "<<A<<"; T : "<<T<<" || Final state :\t";

  switch(st)
  {
    case -1 : cout<<BOLDGREEN<<"Exclusion"<<RESET; break;
    case  0 : cout<<BOLDRED<<"Extinction"<<RESET; break;
    case  1 : cout<<BOLDBLUE<<"Cohabitation"<<RESET; break;
  }
  cout <<"\t||\t Progress : "<<pos<<" / "<<nb_it<<" __ Time :"<<duration<<"s";

}

void final()
{
  Environment* env;
  fstream sim_data;

  //ITERATORS
  int Amax = 50, 
      Tmax = 1500;

  int iA = 1,
      iT = 1;

  int state;

  //CSV
  std::system("touch simdata.csv");
  sim_data.open("simdata.csv", fstream::out);
  sim_data << "Ainit ; T ; val";

  //TIME COUNT
  std::clock_t start;
  double duration;

  start = std::clock();


  for (int Ainit = 0 ; Ainit <= Amax ; Ainit+=iA)
  {
    for (int T = 0 ; T < Tmax ; T += iT)
    {
      state = 0;
      env = new Environment(0.1, 0.0, 0.02, 32, 0, Ainit);
      env->run(10000, T);
      state = env->proportion();

      sim_data<<"\n"<<Ainit<<";"<<T<<";"<<state;

      duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
      show_progress(Amax, Tmax, iA, iT, T, Ainit, state, duration);

    }
  }
  sim_data.close();
  //std::system("Rscript Plot_heatmap.R simdata.csv simdat.pdf");
}
void test_single()
{
  Environment * env;

  env = new Environment(0.1, 0.0, 0.02, 32, 0, 0.01);
  env->run(10000, 1500);
}



//==============================
//    MAIN
//==============================

int main(int argc, char const *argv[])
{  
  
  final();
  //test_single();
  cout << "\nDone.\n\n";
  return 0;
}

