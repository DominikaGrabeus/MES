#pragma once
#include <Eigen/Dense>
#include <array>
#include "UniversalElement.h"
#include "Node.h";
using namespace std;
class JacobMatrix : public UniversalElement {
public:
	Eigen::Matrix2d jacobMatrix;
	double dXbydXsi;
	double dXbydEta;
	double dYbydXsi;
	double dYbydEta;

	void setJacobMatrix(array<Node*, 4>, int index);
	JacobMatrix();

private:
	double getJacobMatrixN1(int i, int index, Node* node);
	double getJacobMatrixN2(int i, int index, Node* node);
	double getJacobMatrixN3(int i, int index, Node* node);
	double getJacobMatrixN4(int i, int index, Node* node);
	double dNbydXsi(int pointFromUniversalElementIndex, int shapeFunctionIndex);
	double dNbydEta(int pointFromUniversalElementIndex, int shapeFunctionIndex);

};

JacobMatrix::JacobMatrix() {}

void JacobMatrix::setJacobMatrix(array<Node*, 4>nodes, int index) {
	
	this->dXbydXsi = getJacobMatrixN1(0, index, nodes[0]) + getJacobMatrixN1(1, index, nodes[1]) + getJacobMatrixN1(2, index, nodes[2]) + getJacobMatrixN1(3, index, nodes[3]);
	this->dXbydEta = getJacobMatrixN2(0, index, nodes[0]) + getJacobMatrixN2(1, index, nodes[1]) + getJacobMatrixN2(2, index, nodes[2]) + getJacobMatrixN2(3, index, nodes[3]);
	this->dYbydXsi = getJacobMatrixN3(0, index, nodes[0]) + getJacobMatrixN3(1, index, nodes[1]) + getJacobMatrixN3(2, index, nodes[2]) + getJacobMatrixN3(3, index, nodes[3]);
	this->dYbydEta = getJacobMatrixN4(0, index, nodes[0]) + getJacobMatrixN4(1, index, nodes[1]) + getJacobMatrixN4(2, index, nodes[2]) + getJacobMatrixN4(3, index, nodes[3]);
	jacobMatrix(0, 0) = dXbydXsi;
	jacobMatrix(1, 0) = dXbydEta;
	jacobMatrix(0, 1) = dYbydXsi;
	jacobMatrix(1, 1) = dYbydEta;
}

double JacobMatrix::getJacobMatrixN1(int i, int index, Node* node) {
	return ((dNbydXsi(index, i)) * node->getX());
}

double JacobMatrix::getJacobMatrixN2(int i, int index, Node* node) {
	return ((dNbydEta(index, i)) * node->getX());
}

double JacobMatrix::getJacobMatrixN3(int i, int index, Node* node) {
	return ((dNbydXsi(index, i)) * node->getY());
}

double JacobMatrix::getJacobMatrixN4(int i, int index, Node* node) {
	return ((dNbydEta(index, i)) * node->getY());
}
double JacobMatrix::dNbydXsi(int pointFromUniversalElementIndex, int shapeFunctionIndex) {
	return (UniversalElement::calculatedPoints2D[pointFromUniversalElementIndex][2])(shapeFunctionIndex);
}
double JacobMatrix::dNbydEta(int pointFromUniversalElementIndex, int shapeFunctionIndex) {
	return (UniversalElement::calculatedPoints2D[pointFromUniversalElementIndex][1])(shapeFunctionIndex);
}

