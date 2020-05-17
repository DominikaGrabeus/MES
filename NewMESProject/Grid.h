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
	vector<Node> nodesList;
	vector<Element> elementsList;
	void createGrid(float height, float width, int nH, int nW, double initialTemperature,double ambientTemperature, double heat, double density, double conductivity, double alfa, double simulationTime, double stepTime);
	void printGrid();
	void printAllGlobalMatrix();
	void calculateEquation();
private:
	void createNodesList();
	void createElemensList();
	Element setNodesInElement(int i, int j, int nH);
	void agregateLocalMatrixToGlobalMatrix(Element element);
	double getMinTemperature();
	double getMaxTemperature();


};
void Grid::createGrid(float height, float width, int nH, int nW, double initialTemperature, double ambientTemperature, double heat, double density, double conductivity, double alfa, double simulationTime, double stepTime) {
	
	this->GlobalData::setGlobalData(height,  width,  nH,  nW,  initialTemperature, ambientTemperature,  heat,  density, conductivity,  alfa,  simulationTime,  stepTime);
	this->createNodesList();
	UniversalElement::UniversalElement();
	matrixHGlobal = new Eigen::MatrixXd(GlobalData::nN, GlobalData::nN);
	matrixHGlobal->fill(0);
	matrixCGlobal = new Eigen::MatrixXd(GlobalData::nN, GlobalData::nN);
	matrixCGlobal->fill(0);
	matrixHBCGlobal = new Eigen::MatrixXd(GlobalData::nN, GlobalData::nN);
	matrixHBCGlobal->fill(0);
	vectorPGlobal = new Eigen::VectorXd(GlobalData::nN );
	vectorPGlobal->fill(0);
	this->createElemensList();


}

void Grid::createNodesList() {
	double deltaX = GlobalData::width / ((double)GlobalData::nW - 1.0);
	double deltaY = GlobalData::height / ((double)GlobalData::nH - 1.0);
	for (int i = 0; i < GlobalData::nW; i++) {
		for (int j = 0; j < GlobalData::nH; j++) {
			float x = i * deltaX;
			float y = j * deltaY;
			int id = i * GlobalData::nH + j + 1;
			bool BC = false;
			if (x == 0 || x == GlobalData::height || y == 0 || y == GlobalData::width)
				BC = true;
			Node* newNode = new Node(x, y, id, GlobalData::initialTemperature,BC);
			nodesList.push_back(*newNode);
		}
	}
}
void Grid::createElemensList() {
	for (int i = 0; i < GlobalData::nW - 1; i++) {
		for (int j = 0; j < GlobalData::nH - 1; j++) {
			Element element = setNodesInElement(i, j, GlobalData::nH);
			int id = i * (GlobalData::nH - 1) + j + 1;
			element.setElementId(id);
			elementsList.push_back(element);
		}
	}
}
Element Grid::setNodesInElement(int i, int j, int nH) {
	array<int, 4> nodesId;
	array<Node*, 4> nodes;
	nodesId[0] = j + i * GlobalData::nH;
	nodesId[1] = nodesId[0] + GlobalData::nH;
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

void Grid::printAllGlobalMatrix() {
	cout << *matrixHGlobal << endl;
	cout << *matrixCGlobal << endl;
	cout << *matrixHBCGlobal << endl;
	cout << *vectorPGlobal << endl;
}


void Grid::calculateEquation() {
	Eigen::MatrixXd A(GlobalData::nN, GlobalData::nN);
	Eigen::VectorXd B(GlobalData::nN);
	Eigen::VectorXd t0(GlobalData::nN);
	Eigen::VectorXd t1(GlobalData::nN);

	for (double i =0 ; i <= simulationTime; i += stepTime) {
		cout << "Simulation time : " << i << "  Minimum temperature : " << getMinTemperature() << "  Maximum temperature : " << getMaxTemperature() << endl;
		A = (*matrixHGlobal + *matrixHBCGlobal) + (*matrixCGlobal / GlobalData::stepTime);
		for (int i = 0; i < GlobalData::nN; i++)
				t0[i] = nodesList[i].getTemperature();
		B = (*matrixCGlobal / GlobalData::stepTime) * t0 - *vectorPGlobal;
		t1 = A.householderQr().solve(B);
		for (int i = 0; i < GlobalData::nN; i++)
			nodesList[i].setTemperature(t1[i]);
	}

}

double Grid::getMinTemperature() {
	Eigen::VectorXd minVector(GlobalData::nN);
	for (int i = 0; i < GlobalData::nN; i++)
		minVector[i] = nodesList[i].getTemperature();

	return minVector.minCoeff();
}

double Grid::getMaxTemperature() {
	Eigen::VectorXd maxVector(GlobalData::nN);
	for (int i = 0; i < GlobalData::nN; i++)
		maxVector[i] = nodesList[i].getTemperature();

	return maxVector.maxCoeff();
}
