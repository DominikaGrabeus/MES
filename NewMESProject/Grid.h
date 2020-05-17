#pragma once
#include <vector>
#include<iostream>
#include "Node.h"
#include "Element.h"
#include "GlobalData.h";
#include "JacobMatrix.h"
#include "UniversalElement.h"


using namespace std;
class Grid : public GlobalData {
public:
	Eigen::VectorXd* vectorPGlobal;
	Eigen::MatrixXd* matrixHGlobal;
	Eigen::MatrixXd* matrixCGlobal;
	Eigen::MatrixXd* matrixHBCGlobal;
	Eigen::MatrixXd* matrixHWithBCGlobal;
	vector<Node> nodesList;
	vector<Element> elementsList;
	Element setNodesInElement(int i, int j, int nH);
	void createGrid(float height, float width, int nH, int nW, double initialTemperature,double ambientTemperature, double heat, double density, double conductivity, double alfa, double simulationTime, double stepTime);
	void createNodesList(float height, float width, int nH, int nW, double temperature);
	void createElemensList(int nH, int nW);
	void printGrid();
	void agregateLocalMatrixToGlobalMatrix(Element element);
	void printAgregatedMatrixHAndC();
	void createMatrixHWithBC();


};
void Grid::createGrid(float height, float width, int nH, int nW, double initialTemperature, double ambientTemperature, double heat, double density, double conductivity, double alfa, double simulationTime, double stepTime) {
	
	this->GlobalData::setGlobalData(height,  width,  nH,  nW,  initialTemperature, ambientTemperature,  heat,  density, conductivity,  alfa,  simulationTime,  stepTime);
	this->createNodesList(height, width, nH, nW, initialTemperature);
	UniversalElement::UniversalElement();
	matrixHGlobal = new Eigen::MatrixXd(GlobalData::nN, GlobalData::nN);
	matrixHGlobal->fill(0);
	matrixCGlobal = new Eigen::MatrixXd(GlobalData::nN, GlobalData::nN);
	matrixCGlobal->fill(0);
	matrixHBCGlobal = new Eigen::MatrixXd(GlobalData::nN, GlobalData::nN);
	matrixHBCGlobal->fill(0);
	matrixHWithBCGlobal = new Eigen::MatrixXd(GlobalData::nN, GlobalData::nN);
	matrixHWithBCGlobal ->fill(0);
	vectorPGlobal = new Eigen::VectorXd(GlobalData::nN );
	vectorPGlobal->fill(0);
	this->createElemensList(nH, nW);


}

void Grid::createNodesList(float height, float width, int nH, int nW, double temperature) {
	double deltaX = width / ((double)nW - 1.0);
	double deltaY = height / ((double)nH - 1.0);
	for (int i = 0; i < nW; i++) {
		for (int j = 0; j < nH; j++) {
			float x = i * deltaX;
			float y = j * deltaY;
			int id = i * nH + j + 1;
			bool BC = false;
			if (x == 0 || x == height || y == 0 || y == width)
				BC = true;
			Node* newNode = new Node(x, y, id, temperature,BC);
			nodesList.push_back(*newNode);
		}
	}
}
void Grid::createElemensList(int nH, int nW) {
	for (int i = 0; i < nW - 1; i++) {
		for (int j = 0; j < nH - 1; j++) {
			Element element = setNodesInElement(i, j, nH);
			int id = i * (nH - 1) + j + 1;
			element.setElementId(id);
			elementsList.push_back(element);
		}
	}
}
Element Grid::setNodesInElement(int i, int j, int nH) {
	array<int, 4> nodesId;
	array<Node*, 4> nodes;
	nodesId[0] = j + i * nH;
	nodesId[1] = nodesId[0] + nH;
	nodesId[2] = nodesId[1] + 1;
	nodesId[3] = nodesId[0] + 1;
	for (int i = 0; i < 4; i++) {
		Node* node = &(nodesList[(nodesId[i])]);
		nodes[i] = node;
	}

	Element element = nodes;
	element.elementId;
	element.setMatrixHAndC(conductivity, heat, density, nodes);
	element.setMatrixHBCandVectorP(alfa, ambientTemperature, nodes);
	//cout << element.matrixAndVector.matrixHBCLocal << endl;
   // cout << element.matrixAndVector.vectorP << endl;
	agregateLocalMatrixToGlobalMatrix(element);


	return element;
}

void Grid::agregateLocalMatrixToGlobalMatrix(Element element) {
	double a;
	array<int, 4> nodesIDs;
	for (int i = 0; i < 4; i++)
		nodesIDs[i] = element.nodes[i]->getNodeId();
	for (int i = 0; i < 4; i++) {

		for (int j = 0; j < 4; j++) {

			(*matrixHGlobal)(nodesIDs[i] - 1, nodesIDs[j] - 1) += element.matrixHLocal.matrix(i, j);
			(*matrixCGlobal)(nodesIDs[i] - 1, nodesIDs[j] - 1) += element.matrixCLocal.matrix(i, j);
			(*matrixHBCGlobal)(nodesIDs[i] - 1, nodesIDs[j] - 1) += element.matrixAndVector.matrixHBCLocal(i, j);
		}

		(*vectorPGlobal)[nodesIDs[i] - 1] += (element.matrixAndVector.vectorP[i]);
	}

}

void Grid::printGrid() {
	for (int i = 0; i < GlobalData::nN; i++)
		nodesList[i].printNode();
	for (int i = 0; i < GlobalData::nE; i++)
		elementsList[i].printElement();
}

void Grid::printAgregatedMatrixHAndC() {
	cout << *matrixHGlobal << endl;
	cout << *matrixCGlobal << endl;
	cout << *matrixHBCGlobal << endl;
	cout << *vectorPGlobal << endl;
	cout << *matrixHWithBCGlobal << endl;

}

void Grid::createMatrixHWithBC() {
	*matrixHWithBCGlobal = *matrixHGlobal + *matrixHBCGlobal;
}



