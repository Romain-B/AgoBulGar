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
void print_cell_info(Cell* cell, int nb)
{
  cout << "\n Info on cell "<< nb <<"\n---------\n";

  cout << "\n x,y :\t" << cell->x() << "," 
                              << cell->y();

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


  //-------------
  //    TESTS
  //-------------

  void test_cell()
  {
    cout << "\n\t===============\n\tCELL TESTS\n\t===============\n";

    Cell* cell_1 = new CellA(0,0);
    Cell* cell_2 = new CellB(0,5);

    print_cell_info(cell_1, 1);
    print_cell_info(cell_2, 2);



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

