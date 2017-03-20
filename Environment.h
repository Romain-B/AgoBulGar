#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H 

//==============================
//    INCLUDES
//==============================
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <iostream>

#include "Cell.h"
#include "CellA.h"
#include "CellB.h"
#include "Spot.h"

using std::vector;
using std::array;

/**
 * @class Environement
 * @brief Manage the environment
 */

class Environment;
typedef Spot* (Environment::*FP)(Spot*);


class Environment
{

public:
//==============================
//    CONSTRUCTORS
//==============================
 	
 	Environment();
  Environment(float R , float Pmut , float Pdth , int size , float Wmin , int Ainit);		//Custom constructor

//==============================
//    DESTRUCTOR
//==============================
  ~Environment();
 
//==============================
//    GETTERS
//==============================

//==============================
//    SETTERS
//==============================

//==============================
//    OPERATORS
//==============================

//==============================
//    PUBLIC METHODS
//==============================

  void env_wipe();
  void run(int it, int T);
  void print_grid();
  void write_csv();
  void init_csv();
  
  

protected:
//==============================
//    PROTECTED METHODS
//==============================
  Spot* tl(Spot* center);
  Spot* tc(Spot* center);
  Spot* tr(Spot* center);

  Spot* cl(Spot* center);
  Spot* cr(Spot* center);

  Spot* bl(Spot* center);
  Spot* bc(Spot* center);
  Spot* br(Spot* center);

  void diffusion(int x , int y );
  void competition();
  void cell_death();
  void cell_division(Spot* mother, Spot* daughter);
  void cell_mutation(Spot* c);




//==============================
// DECLARATION STATIC ATTRIBUTES
//==============================

//==============================
//    ATTRIBUTES
//==============================
	int H_; 				// Height	
	int W_; 				// Width
	float D_;				// Diffusion coefficient
	float Pdth_;		// Death probability
	float Pmut_;		// Mutation probability
  int Ainit_;     // cA init
  std::ofstream data_csv;

	vector<vector <Spot*>> grid_;	//Matrix of Spot
	vector<Spot*> free_spot_;	// Contains free spots


  //Array of function pointers to Spots around center
  static FP around[8];
};




//==============================
//    GETTER DEFINITION
//==============================

//==============================
//    SETTER DEFINITION
//==============================

//==============================
//    OPERATOR DEFINITION
//==============================

//==============================
//  FRIEND FUNCTION DEFINITION
//==============================



#endif // ENVIRONMENT_H