#pragma once
#include <array>
#include<iostream>
#include "Node.h"
#include "AllMatrix.h"
#include "UniversalElement.h"
using namespace std;
class Element {
public:
	int elementId;
	array<Node*, 4> nodes;
	AllMatrix matrixHLocal;
	AllMatrix matrixCLocal;
	Element();
	Element(array<Node*, 4> Nodes);
	void setElementId(int id);
	void printElement();
	int getElementId();
	void setMatrixHAndC(double k, double cp, double ro, array<Node*, 4> Nodes);
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
	matrixHLocal.printMatrixH();
	matrixCLocal.printMatrixC();
}
