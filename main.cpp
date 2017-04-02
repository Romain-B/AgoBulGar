//==============================
//    INCLUDES
//==============================

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
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

void show_help()
{
  std::cerr << "\nCELL LAB SIMULATION"
          << "\n-------------------"
          << "\nThis program needs some arguments to function.\nThis help message also appears with -h or --help."
          << "\n"
          << "\n The command MUST have one of the following argument :\n"
          << "\n\t -F, --FULL   \t Executes the full simulation"
          << "\n\t -G, --GRAPHIC\t Executes one run with grid shown. (T and Ainit are given with 'start' options)"
          << "\n\n Optionnal parameters, followed by value :\n"
          << "\n\t -c, --csv    \t name of the csv file to write simulation outputs. (default simdata.csv)"
          << "\n\t -o, --outpdf \t name of the output pdf for heatmap. (default simdata.pdf)\n"
          << "\n\t -i, --Ti     \t Incrementation  of T. (default 50)"
          << "\n\t -j, --Ai     \t Incrementation  of Ainit. (default 5)\n"
          << "\n\t -m, --Tmax   \t Max value of T. (default 1500)"
          << "\n\t -n, --Amax   \t Max value of Ainit. (default 50)\n"
          << "\n\t -s, --Tstart \t Start value of T. (default 0)"
          << "\n\t -t, --Astart \t Start value of Ainit. (default 0)\n"
          << "\n\t -r, --runstep\t Number of steps per simulation. (default 10 000)\n\n"
          ;
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
void show_progress(int pos, int nb_it, int T, float A, int st, float duration)
{
  cout<<"\nAinit : "<<A<<"; T : "<<T<<" || Final state :\t";

  switch(st)
  {
    case -1 : cout<<BOLDGREEN<<"Exclusion"<<RESET; break;
    case  0 : cout<<BOLDRED<<"Extinction"<<RESET; break;
    case  1 : cout<<BOLDBLUE<<"Cohabitation"<<RESET; break;
  }
  cout <<"\t||\t Progress : "<<pos<<" / "<<nb_it<<" __ Time :"<<duration<<"s";

}

void final(std::string csv, std::string outpdf, int Amax, int Tmax, float iA, int iT, int Tstart, float Astart, int runstep, float pmut)
{
  Environment* env;
  fstream sim_data;
  std::stringstream out;

  //ITERATORS

  int total_it = (Amax/iA - Astart/iA)*(Tmax/iT - Tstart/iT) +1;
  int pos = 1;
  int state;

  //CSV
  std::system(("touch data/"+csv).c_str());
  out << "Ainit ; T ; val";

  //TIME COUNT
  std::clock_t start;
  double duration;

  start = std::clock();


  for (float Ainit = Astart; Ainit <= Amax ; Ainit+=iA)
  {
    for (int T = Tstart ; T <= Tmax ; T += iT)
    {
      state = 0;
      env = new Environment(0.1, pmut, 0.02, 32, 0.001, Ainit);
      env->run(5000, T);
      state = env->proportion();

      out<<"\n"<<Ainit<<";"<<T<<";"<<state;

      duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
      show_progress(pos, total_it, T, Ainit, state, duration);

      pos++; 
    }
  }

  sim_data.open(csv, fstream::out);
  sim_data<<out.str();
  sim_data.close();
  std::system(("Rscript Plot_heatmap.R data/"+csv+" out/"+outpdf).c_str());
}

void test_single(float Ainit, int T, int runstep, float pmut)
{
  Environment * env;

  env = new Environment(0.1, pmut, 0.02, 32, 0.001, Ainit);
  env->run_graphic(runstep, T);
}



//==============================
//    MAIN
//==============================

int main(int argc, char const *argv[])
{  
  
  if (argc < 2)
  {
    show_help();
    return 1;
  }

  std::string csv="simdata.csv",
              outpdf = "simdata.pdf";

  int Tstart = 0, Ti = 50, 
      Tmax = 1500, Amax = 50,
      runstep = 10000;
  float Astart = 0, Ai = 5, pmut = 0.0;

  bool exec;


  for (int i=1 ; i < argc ; ++i)
  {
    std::string arg = argv[i];
    

    
    if(("-h"==arg) || ("--help"==arg))
      {show_help(); return 1;}

    if(("-F"==arg) || ("--FULL"==arg))
      {exec = 1;}
    if(("-G"==arg) || ("--GRAPHIC"==arg))
      {exec = 0;}

    if(("-o"==arg) || ("--outpdf"==arg))
      {
        if(i+1 < argc)
        {outpdf = argv[++i];}
      }
    if(("-c"==arg) || ("--csv"==arg))
      {
        if(i+1 < argc)
        {csv = argv[++i];}
      }

    if(("-i"==arg) || ("--Ti"==arg))
      {
        if(i+1 < argc)
        {Ti = atoi(argv[++i]);}
      }
    if(("-j"==arg) || ("--Ai"==arg))
      {
        if(i+1 < argc)
        {Ai = atof(argv[++i]);}
      }

    if(("-m"==arg) || ("--Tmax"==arg))
      {
        if(i+1 < argc)
        {Tmax = atoi(argv[++i]);}
      }
    if(("-n"==arg) || ("--Amax"==arg))
      {
        if(i+1 < argc)
        {Amax = atoi(argv[++i]);}
      }

    if(("-s"==arg) || ("--Tstart"==arg))
      {
        if(i+1 < argc)
        {Tstart = atoi(argv[++i]);}
      }
    if(("-t"==arg) || ("--Astart"==arg))
      {
        if(i+1 < argc)
        {Astart = atoi(argv[++i]);}
      }

    if(("-r"==arg) || ("--runstep"==arg))
      {
        if(i+1 < argc)
        {runstep = atoi(argv[++i]);}
      }
    
    if(("-p"==arg) || ("--Pmut"==arg))
      {
        if(i+1 < argc)
        {pmut = atof(argv[++i]);}
      }
  }
  if(exec)
    final(csv, outpdf, Amax, Tmax, Ai, Ti, Tstart, Astart, runstep, pmut);
  
  else 
    test_single(Astart, Tstart, runstep, pmut);
  cout << "\nDone.\n\n";
  return 0;
}

