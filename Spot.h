#ifndef SPOT_H
#define SPOT_H 

//==============================
//    INCLUDES
//==============================

/**
 * @class Spot
 * @brief A spot
 */

class Spot
{
public:
//==============================
//    CONSTRUCTORS
//==============================
   Spot();
//==============================
//    DESTRUCTOR
//==============================
   ~Spot();
//==============================
//    GETTERS
//==============================
  inline int x() const;
  inline int y() const;
  inline int cA() const;
  inline int cB() const;
  inline int cC() const;

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

//==============================
// DECLARATION STATIC ATTRIBUTES
//==============================

//==============================
//    ATTRIBUTES
//==============================
  public int x_, y_; //Position attributs

  public float cA_, cB_, cC_; //Concentration attribut
  
  protected bool isEmpty_; 
};
//==============================
//    GETTER DEFINITION
//==============================
inline int Spot::x() const{
	return x_;
}

inline int Spot::y() const{
	return y_;
}
inline float Spot::cA() const{
	return cA_;
}
inline float Spot::cB() const{
	return cB_;
}

inline float Spot::cC() const{
	return cC_;
}

//==============================
//    SETTER DEFINITION
//==============================

//==============================
//    OPERATOR DEFINITION
//==============================


#endif // SPOT_H