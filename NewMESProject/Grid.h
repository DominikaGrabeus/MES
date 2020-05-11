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
	Eigen::Vector4d tmp;
	Eigen::MatrixXd* matrixHGlobal;
	Eigen::MatrixXd* matrixCGlobal;
	vector<Node> nodesList;
	vector<Element> elementsList;
	double cp;
	double ro;
	double conductivity;
	Element setNodesInElement(int i, int j, int nH);
	void createGrid(float height, float width, int nH, int nW, double temperature, double cp, double ro, double conductivity, double convection);
	void createNodesList(float height, float width, int nH, int nW, double temperature);
	void createElemensList(int nH, int nW);
	void printGrid();
	void agregateLocalMatrixToGlobalMatrix(Element element);
	void printAgregatedMatrixHAndC();

};
void Grid::createGrid(float height, float width, int nH, int nW, double temperature, double cp, double ro, double conductivity,double convection) {
	this->cp = cp;
	this->ro = ro;
	this->conductivity = conductivity;
	this->GlobalData::setGlobalData(height, width, nH, nW, temperature,convection);
	this->createNodesList(height, width, nH, nW, temperature);
	UniversalElement::UniversalElement();
	matrixHGlobal = new Eigen::MatrixXd(GlobalData::nN, GlobalData::nN);
	matrixHGlobal->fill(0);
	matrixCGlobal = new Eigen::MatrixXd(GlobalData::nN, GlobalData::nN);
	matrixCGlobal->fill(0);
	this->createElemensList(nH, nW);
	for (int i = 0; i < 4; i++) {
		tmp(i) = i;
	}


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
	element.setMatrixHAndC(conductivity, cp, ro, nodes);
	element.setMatrixHBCandVectorP(convection, temperature, nodes);
	cout << element.matrixHBCLocal.bottomMatrix << endl;
	cout << element.matrixHBCLocal.rightMatrix << endl;
	cout << element.matrixHBCLocal.topMatrix << endl;
	cout << element.matrixHBCLocal.leftMatrix << endl;
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
		}
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

}


