#pragma once
#include <array>
#include<iostream>
#include "Node.h"
#include "MatrixH_C.h"
#include "MatrixHBCandVectorP.h"
#include "UniversalElement.h"
using namespace std;
class Element {
public:
	int elementId;
	array<Node*, 4> nodes;
	MatrixH_C matrixHLocal;
	MatrixH_C matrixCLocal;
	MatrixHBCandVectorP matrixAndVector;
	Element();
	Element(array<Node*, 4> Nodes);
	void setElementId(int id);
	void printElement();
	int getElementId();
	void setMatrixHAndC(double k, double cp, double ro, array<Node*, 4> Nodes);
	void setMatrixHBCandVectorP(double convection, double temperature, array<Node*, 4> Nodes);
};

Element::Element() {
	this->nodes = { 0,0,0,0 };
}

Element::Element(array<Node*, 4> Nodes) {
	this->nodes = Nodes;
}
void Element::setElementId(int id)
{
	this->elementId = id;
}
void Element::printElement() {
	cout << "element : " << elementId << " " << endl;
	nodes[0]->printNode();
	nodes[1]->printNode();
	nodes[2]->printNode();
	nodes[3]->printNode();
}
int Element::getElementId() {
	return elementId;
}

void Element::setMatrixHAndC(double k, double cp, double ro, array<Node*, 4> nodes)
{
	matrixHLocal.calculateMatrixH(k, nodes);
	matrixCLocal.calculateMatrixC(cp, ro, nodes);
	//matrixHLocal.printMatrixH();
	//matrixCLocal.printMatrixC();
}
void Element::setMatrixHBCandVectorP(double convection, double temperature, array<Node*, 4> Nodes) {
	matrixAndVector.calculateMatrixHBCandVectorP(convection, temperature, Nodes);
}
