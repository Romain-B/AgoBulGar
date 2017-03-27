//==============================
//    INCLUDES
//==============================

#include <cstdio>
#include <cstdlib>
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
  //cout << "\nSpot is empty : "<< spot->isEmpty_;  
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
    

      //ARE NOW PROTECTED AGAIN 
      // env.cell_death();
      // env.competition();
      //env.print_grid();

    cout << "\nDone.\n";

  }

void final()
{
  Environment* env;
  fstream sim_data;

  int Amax = 50, 
      Tmax = 1500;

  int state;

  sim_data.open("simdata.csv",  fstream::in | fstream::out);
  sim_data << "Ainit ; T ; val";

  for (int Ainit = 0 ; Ainit <= Amax ; Ainit+= 10)
  {
    for (int T = 0 ; T < Tmax ; T += 100)
    {
      state = 0;
      env = new Environment(0.1, 0.0, 0.02, 32, 0, Ainit);
      env->run(1000, T);
      state = env->proportion();

      sim_data<<"\n"<<Ainit<<";"<<T<<";"<<state;
      cout<<"\n A_init = "<<Ainit<<"; T = "<<T<<"; state ="<<state;

    }
  }

  sim_data.close();

  std::system("Rscript Plot_heatmap.R simdata.csv simdtat.pdf");
}



//==============================
//    MAIN
//==============================

int main(int argc, char const *argv[])
{  
  
  final();
  cout << "\nDone.\n\n";
  return 0;
}

