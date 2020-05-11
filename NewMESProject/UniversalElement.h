#pragma once
#include <math.h>
#include "MatrixH_C.h"

class UniversalElement {
public:
	array<array< Eigen::Vector4d,3>,4> calculatedPoints2D;
	UniversalElement();
	Eigen::Vector4d shapeFunctionValue;
	Eigen::Vector4d shapeFunctionXsi;
	Eigen::Vector4d shapeFunctionEta;

	Eigen::Vector4d getShapeFunctiondNdXsi();
	Eigen::Vector4d getShapeFunctiondNdEta();
	Eigen::Vector4d getShapeFunctionsValueN();
	void printShapeFunctions(int ShapeFunctionEtaOrXsiOrN);


private:

	void setNodesInUniversalElement2D();
	array< Eigen::Vector4d, 3> setNodeShapeFunction(double xsi, double eta);
	Eigen::Vector4d setShapeFunctionValueN(double xsi, double eta);
	Eigen::Vector4d setShapeFunctiondNdEta(double xsi);
	Eigen::Vector4d setShapeFunctiondNdXsi(double eta);
};

UniversalElement::UniversalElement() {
	setNodesInUniversalElement2D();
}


void UniversalElement::setNodesInUniversalElement2D() {
	calculatedPoints2D[0] = setNodeShapeFunction((-1 / sqrt(3)), (-1 / sqrt(3)));
	calculatedPoints2D[1] = setNodeShapeFunction((1 / sqrt(3)), (-1 / sqrt(3)));
	calculatedPoints2D[2] = setNodeShapeFunction((1 / sqrt(3)), (1 / sqrt(3)));
	calculatedPoints2D[3] = setNodeShapeFunction((-1 / sqrt(3)), (1 / sqrt(3)));
}

array< Eigen::Vector4d, 3>  UniversalElement::setNodeShapeFunction(double xsi, double eta)
{
	array< Eigen::Vector4d, 3> NodeShapeFunctionInPoint;
	NodeShapeFunctionInPoint[0] = setShapeFunctionValueN(xsi, eta);
	NodeShapeFunctionInPoint[1] = setShapeFunctiondNdEta(xsi);
	NodeShapeFunctionInPoint[2] = setShapeFunctiondNdXsi( eta);
	return NodeShapeFunctionInPoint;

}
Eigen::Vector4d UniversalElement::setShapeFunctionValueN(double xsi, double eta) {
	this->shapeFunctionValue[0] = 0.25 * (1 - xsi) * (1 - eta);
	this->shapeFunctionValue[1] = 0.25 * (1 + xsi) * (1 - eta);
	this->shapeFunctionValue[2] = 0.25 * (1 + xsi) * (1 + eta);
	this->shapeFunctionValue[3] = 0.25 * (1 - xsi) * (1 + eta);
	return shapeFunctionValue;
}
Eigen::Vector4d UniversalElement::setShapeFunctiondNdEta(double xsi) {
	this->shapeFunctionEta[0] = -0.25 * (1 - xsi);
	this->shapeFunctionEta[1] = -0.25 * (1 + xsi);
	this->shapeFunctionEta[2] = 0.25 * (1 + xsi);
	this->shapeFunctionEta[3] = 0.25 * (1 - xsi);
	return shapeFunctionEta;
}
Eigen::Vector4d UniversalElement::setShapeFunctiondNdXsi(double eta) {
	this->shapeFunctionXsi[0] = -0.25 * (1 - eta);
	this->shapeFunctionXsi[1] = 0.25 * (1 - eta);
	this->shapeFunctionXsi[2] = 0.25 * (1 + eta);
	this->shapeFunctionXsi[3] = -0.25 * (1 + eta);
	return shapeFunctionXsi;

}

Eigen::Vector4d UniversalElement::getShapeFunctiondNdXsi()
{
	return shapeFunctionXsi;
}
Eigen::Vector4d UniversalElement::getShapeFunctiondNdEta()
{
	return shapeFunctionEta;
}
Eigen::Vector4d UniversalElement::getShapeFunctionsValueN()
{
	return shapeFunctionValue;
}
void UniversalElement::printShapeFunctions(int ShapeFunctionEtaOrXsiOrN) {
	for (int i= 0; i < 4; i++)
	{
		cout << calculatedPoints2D[i][ShapeFunctionEtaOrXsiOrN] << endl;


	}
}