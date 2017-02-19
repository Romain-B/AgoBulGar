#ifndef CELL_H
#define CELL_H 

//==============================
//    INCLUDES
//==============================

/**
 * @class CELL
 * @brief A CELL
 */

class Cell
{
public:
//==============================
//    CONSTRUCTORS
//==============================
  Cell(int x, int y);
 
//==============================
//    DESTRUCTOR
//==============================
  virtual ~Cell();
 
//==============================
//    GETTERS
//==============================
  inline float cA() const;
  inline float cB() const;
  inline float cC() const;

  inline float fit() const;

  inline int x() const;
  inline int y() const;

  inline float rAA() const;
  inline float rAB() const;
  inline float rBB() const;
  inline float rBC() const;

//==============================
//    SETTERS
//==============================

//==============================
//    OPERATORS
//==============================

//==============================
//    PUBLIC METHODS
//==============================
  virtual void compute_fitness() = 0;
  virtual float* metabolism(float csA, float csB, float csC) = 0;


protected:
//==============================
//    PROTECTED METHODS
//==============================

//==============================
// DECLARATION STATIC ATTRIBUTES
//==============================

//==============================
//    ATTRIBUTES
//==============================
  float cA_, cB_, cC_;    //Concentration of metabolites
  int x_,y_;              //Coordinates
  float fit_;             //Fitness

  static float rAA_, rAB_, rBB_, rBC_; //Metabolism rates
};


//==============================
//    GETTER DEFINITION
//==============================

  inline float Cell::cA() const
  {
    return cA_;
  }

  inline float Cell::cB() const
  {
    return cB_;
  }

  inline float Cell::cC() const
  {
    return cC_;
  }

  inline float Cell::fit() const
  {
    return fit_;
  }

  inline int Cell::x() const
  {
    return x_;
  }

  inline int Cell::y() const
  {
    return y_;
  }

  inline float Cell::rAA() const
  {
    return rAA_;
  }

  inline float Cell::rAB() const
  {
    return rAB_;
  }

  inline float Cell::rBB() const
  {
    return rBB_;
  }

  inline float Cell::rBC() const
  {
    return rBC_;
  }

//==============================
//    SETTER DEFINITION
//==============================

//==============================
//    OPERATOR DEFINITION
//==============================


#endif // CELL_H