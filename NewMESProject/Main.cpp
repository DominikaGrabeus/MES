#include "Grid.h"
#include"UniversalElement.h"

#include <iostream>


using namespace std;

int main()
{
	Grid grid1;
	
	grid1.createGrid(0.1, 0.1, 4, 4,100,1200,700,7800,25,300,500,50);
	//grid1.createGrid(0.025, 0.025, 2, 2, 100, 700, 7800, 30,25);
	//grid1.printGrid();
	grid1.createMatrixHWithBC();
	grid1.printAgregatedMatrixHAndC();



	system("pause");
}