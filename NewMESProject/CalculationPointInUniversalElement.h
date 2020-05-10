#pragma once
#include <Eigen/Dense>
/*
class CalculationPointInUniversalElement {
	
public:
	Eigen::Vector4d shapeFunctionValue;
	Eigen::Vector4d shapeFunctionXsi;
	Eigen::Vector4d shapeFunctionEta;
	double importance;
	void setNodeShapeFunction(double xsi, double eta);
private:
	void setShapeFunctionValueN(double xsi, double eta);
	void setShapeFunctiondNdXsi(double eta);
	void setShapeFunctiondNdEta(double xsi);


public:
	Eigen::Vector4d getShapeFunctiondNdXsi();
	Eigen::Vector4d getShapeFunctiondNdEta();
	Eigen::Vector4d getShapeFunctionsValueN();
	void printShapeFunctiondNdXsi();
	void printShapeFunctiondNdEta();
};
void CalculationPointInUniversalElement::setNodeShapeFunction(double xsi, double eta)
{
	this->setShapeFunctionValueN(xsi, eta);
	this->setShapeFunctiondNdXsi(eta);
	this->setShapeFunctiondNdEta(xsi);

}
void CalculationPointInUniversalElement::setShapeFunctionValueN(double xsi, double eta) {
	this->shapeFunctionValue[0] = 0.25 * (1 - xsi) * (1 - eta);
	this->shapeFunctionValue[1] = 0.25 * (1 + xsi) * (1 - eta);
	this->shapeFunctionValue[2] = 0.25 * (1 + xsi) * (1 + eta);
	this->shapeFunctionValue[3] = 0.25 * (1 - xsi) * (1 + eta);
}
void CalculationPointInUniversalElement::setShapeFunctiondNdEta(double xsi) {
	this->shapeFunctionEta[0] = -0.25 * (1 - xsi);
	this->shapeFunctionEta[1] = -0.25 * (1 + xsi);
	this->shapeFunctionEta[2] = 0.25 * (1 + xsi);
	this->shapeFunctionEta[3] = 0.25 * (1 - xsi);
}
void CalculationPointInUniversalElement::setShapeFunctiondNdXsi(double eta) {
	this->shapeFunctionXsi[0] = -0.25 * (1 - eta);
	this->shapeFunctionXsi[1] = 0.25 * (1 - eta);
	this->shapeFunctionXsi[2] = 0.25 * (1 + eta);
	this->shapeFunctionXsi[3] = -0.25 * (1 + eta);

}
Eigen::Vector4d CalculationPointInUniversalElement::getShapeFunctiondNdXsi()
{
	return shapeFunctionXsi;
}
Eigen::Vector4d CalculationPointInUniversalElement::getShapeFunctiondNdEta()
{
	return shapeFunctionEta;
}
Eigen::Vector4d CalculationPointInUniversalElement::getShapeFunctionsValueN()
{
	return shapeFunctionValue;
}
void CalculationPointInUniversalElement::printShapeFunctiondNdXsi() {
	for (int j = 0; j < 4; j++) {
		cout << shapeFunctionXsi[j];
		cout << "    ";
	}
	cout << "  " << endl;
}
void CalculationPointInUniversalElement::printShapeFunctiondNdEta() {
	for (int j = 0; j < 4; j++) {
		cout << shapeFunctionEta[j];
		cout << "    ";
	}
	cout << "  " << endl;
}
*/
