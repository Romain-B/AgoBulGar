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
   //default constructeur
  Spot();

   //Constructeur from position only
  Spot(int x, int y); 
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

//==============================
//    SETTERS
//==============================

//==============================
//    OPERATORS
//==============================

//==============================
//    PUBLIC METHODS
//==============================
void c_update(float cA, float cB, float cC);

bool isEmpty();


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
  int x_, y_; //Position attributs
  float cA_, cB_, cC_; //Concentration attribut
  bool isEmpty_; 
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