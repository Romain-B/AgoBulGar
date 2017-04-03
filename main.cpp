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

//Color definitions for terminal print

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
          << "\n\t -r, --runstep\t Number of steps per simulation. (default 10 000)"
          << "\n\t -d, --Diff   \t Diffusion factor. (default 0.1)\n\n"
          << "\n\t -p, --Pmut   \t Probability of mutation. (default 0.0)"
          << "\n\t -q, --Pdeath \t Probability of death. (default 0.02)\n\n"
          ;
}


void show_progress(int pos, int nb_it, int T, float A, float st, float duration)
{
  //Show the progress of the simulation.

  cout<<"\nAinit : "<<A<<"; T : "<<T<<" || Final state :\t";

  if(0!= st && st<1)
    cout<<BOLDGREEN<<"Exclusion"<<RESET;

  else if(st>1) 
    cout<<BOLDBLUE<<"Cohabitation"<<RESET; 
  else
    cout<<BOLDRED<<"Extinction"<<RESET;
  
  cout <<"\t||\t Progress : "<<pos<<" / "<<nb_it<<" __ Time :"<<duration<<"s";

}

void full(std::string csv, std::string outpdf, int Amax, int Tmax, float iA, int iT, int Tstart, float Astart, int runstep, float pmut, float pdeath, float D)
{
  //Execute full simulation. 
  Environment* env;
  fstream sim_data;
  std::stringstream out;

  //ITERATORS

  int total_it = (Amax/iA - Astart/iA +1)*(Tmax/iT - Tstart/iT+1) ;
  int pos = 1;
  float state;

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
      env = new Environment(0.1, pmut, pdeath, 32, 0.001, Ainit, D);
      env->run(runstep, T);
      state = env->proportion();
      cout <<"\n"<< env->proportion();

      out<<"\n"<<Ainit<<";"<<T<<";"<<state;

      duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
      show_progress(pos, total_it, T, Ainit, state, duration);

      pos++; 
    }
  }

  //Write to stringtream during simulation and to csv after in one go. Faster.
  sim_data.open(("data/"+csv), fstream::out);
  sim_data<<out.str();
  sim_data.close();

  std::system(("Rscript Plot_heatmap.R data/"+csv+" out/"+outpdf).c_str());
}

void graphic(float Ainit, int T, int runstep, float pmut, float pdeath, float D)
{
  //Execute graphical simulation.
  Environment * env;

  env = new Environment(0.1, pmut, pdeath, 32, 0.001, Ainit, D);
  env->run_graphic(runstep, T);
}



//==============================
//    MAIN
//==============================

int main(int argc, char const *argv[])
{  
  
  bool opt = 1;

  for (int i=1 ; i < argc ; ++i)
  {
    //Check if the NECESSARY arguments are there.
    if("-F" == argv[i] || "--FULL"==argv[i] 
      || "-G" == argv[i] || "--GRAPHIC" == argv[i])
      opt = 0;
  }

  if (argc < 2 || opt)
  {
    show_help();
    return 1;
  }

  std::string csv="simdata.csv",
              outpdf = "simdata.pdf";

  int Tstart = 0, Ti = 50, 
      Tmax = 1500, Amax = 50,
      runstep = 10000;
  float Astart = 0, Ai = 5, pmut = 0.0, pdeath = 0.02, D = 0.1;

  bool exec;

//Argument Management
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
    if(("-q"==arg) || ("--Pdeath"==arg))
      {
        if(i+1 < argc)
        {pdeath = atof(argv[++i]);}
      }
  }
  if(exec)
    full(csv, outpdf, Amax, Tmax, Ai, Ti, Tstart, Astart, runstep, pmut, pdeath, D);
  
  else 
    graphic(Astart, Tstart, runstep, pmut, pdeath, D);
  cout << "\nDone.\n\n";
  return 0;
}

