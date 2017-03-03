#ifndef SPOT_H
#define SPOT_H 

//==============================
//    INCLUDES
//==============================

#include "Cell.h"

/**
 * @class Spot
 * @brief A spot
 */

class Spot
{
  friend class Environment;
public:
//==============================
//    CONSTRUCTORS
//==============================
   //default constructeur
  Spot();

   //Constructeur from position only
  Spot(int x, int y); 

  //Constructor with concentration
  Spot(int x, int y, float cA, float cB, float cC);
//==============================
//    DESTRUCTOR
//==============================
  ~Spot();
//==============================
//    GETTERS
//==============================
  inline int x() const;
  inline int y() const;
  inline float cA() const;
  inline float cB() const;
  inline float cC() const;
  inline Cell* cell();

//==============================
//    SETTERS
//==============================

//==============================
//    OPERATORS
//==============================

//==============================
//    PUBLIC METHODS
//==============================
void c_update(float cA, float cB, float cC); //Set [ABC]
void ct1_update(float cA, float cB, float cC);  //Set [ABC] at t+1
void time_update();                           //Update time

bool isEmpty();



protected:
//==============================
//    PROTECTED METHODS
//==============================
  void set_cell(Cell*);
  void del_cell();

//==============================
// DECLARATION STATIC ATTRIBUTES
//==============================

//==============================
//    ATTRIBUTES
//==============================
  int x_, y_; //Position attributes
  float cA_, cB_, cC_; //Concentration attributes
  float cA1_, cB1_, cC1_; //Concentration at t+1

  Cell* cell_;

  bool isEmpty_; 
};

//==============================
//    GETTER DEFINITION
//==============================
inline int Spot::x() const
{
	return x_;
}

inline int Spot::y() const
{
	return y_;
}
inline float Spot::cA() const
{
	return cA_;
}
inline float Spot::cB() const
{
	return cB_;
}

inline float Spot::cC() const
{
	return cC_;
}

inline Cell* Spot::cell()
{
  return cell_;
}
//==============================
//    SETTER DEFINITION
//==============================

//==============================
//    OPERATOR DEFINITION
//==============================


#endif // SPOT_H