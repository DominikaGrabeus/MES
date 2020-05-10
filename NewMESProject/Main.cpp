#include "Grid.h"
#include"UniversalElement.h"

#include <iostream>


using namespace std;

int main()
{
	Grid grid1;

	grid1.createGrid(0.1, 0.1, 4, 4, 100, 700, 7800, 25);
	//grid1.createGrid(0.025, 0.025, 2, 2, 25, 700, 7800, 30);
	//grid1.printGrid();
	grid1.printAgregatedMatrixHAndC();


	system("pause");
}