#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H 

//==============================
//    INCLUDES
//==============================
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <array>

#include "Cell.h"
#include "Spot.h"

using std::vector;
using std::array;

/**
 * @class Environement
 * @brief Manage the environment
 */

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


protected:
//==============================
//    PROTECTED METHODS
//==============================
  Spot* tl(Spot* center);

//==============================
// DECLARATION STATIC ATTRIBUTES
//==============================

//==============================
//    ATTRIBUTES
//==============================
	int H_; 				// Height	
	int W_; 				// Width
	float D_;				//Diffusion coefficient
	float Pdth_;		// Death probability
	float Pmut_;		//Mutation probability
	vector<vector <Spot>> grid_;	//Matrix of Spot
	//vector<Spot> free_spot_;	// Contains free spots
	//vector<Cell> cells_;		  //Contains cells

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