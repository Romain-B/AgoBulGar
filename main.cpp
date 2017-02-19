//==============================
//    INCLUDES
//==============================

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using std::cout;


#include "Environment.h"
#include "Spot.h"
#include "Cell.h"
#include "CellA.h"
#include "CellB.h"

//==============================
//    FUNCTION DECLARATION
//==============================


  //-------------
  //    TESTS
  //-------------

  void test_cell()
  {
    cout << "\n\t===============\n\tCELL TESTS\n\t===============\n";

    Cell* cell_1 = new CellA(0,0);

    cout << "\n cell_1 x,y :\t" << cell_1->x() << "," 
                                << cell_1->y();

    cout << "\n cell_1 cA, cB, cC :\t" << cell_1->cA() << ","
                                       << cell_1->cB() << ","
                                       << cell_1->cC();

    cout << "\n cell_1 fitness : \t" << cell_1->fit();
    cout << "\n Metabolim rates rAA, rAB, rBB, rBC : \t" << cell_1->rAA() << ","
                                                          << cell_1->rAB() << ","
                                                          << cell_1->rBB() << ","
                                                          << cell_1->rBC();


    delete cell_1;
  }

//==============================
//    MAIN
//==============================

int main(int argc, char const *argv[])
{
  test_cell();

  cout << "\nDone.\n\n";
  return 0;
}

