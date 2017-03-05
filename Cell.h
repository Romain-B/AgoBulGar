#ifndef CELL_H
#define CELL_H 

//==============================
//    INCLUDES
//==============================

/**
 * @class CELL
 * @brief A CELL
 */

enum Genotype{GenA, GenB};

class Cell
{
public:
//==============================
//    CONSTRUCTORS
//==============================
  Cell();
  Cell(float cAi, float cBi, float cCi);
 
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
  virtual float* metabolism(float s_cA, float s_cB, float s_cC) = 0;
  virtual void set_c(float cAi, float cBi, float cCi);

  virtual char whatAmI();

  
  //will be protected after testing
  static void set_rates(float rAA, float rAB, float rBB, float rBC);
  static void set_min_fit(float mf);

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
  float fit_;             //Fitness
  Genotype geno_;         //Genotype

  static float rAA_, rAB_, rBB_, rBC_; //Metabolism rates
  static float min_fit_;   //Minimum fitness
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