#pragma once
#include <array>
#include "JacobMatrix.h"
#include <Eigen/Dense>
#include <iostream>

using namespace std;

class AllMatrix : public UniversalElement {
public:
	Eigen::Matrix4d matrixH;
	Eigen::Matrix4d matrixC;
	array<JacobMatrix, 4> jacobMatrices;
	array<JacobMatrix, 4> reversedJacobMatrix;
	array<JacobMatrix, 4> transposedJacobMatricesWithDeterminants;
	array<double, 4> determinants;
	array<array<double,4>, 4>  derrivativeNbyX;
	array<array<double, 4>, 4> derrivativeNbyY;
	array<array<Eigen::Vector2d, 4>, 4> matrixContainingAllShapeFunctionInEveryPoint;
	Eigen::Matrix4d getMatrixH();
	Eigen::Matrix4d getMatrixC();



	void calculateMatrixH(double k, array<Node*, 4> nodes);
	void calculateMatrixC(double cp, double ro, array<Node*, 4> nodes);
	void setJacobMatrices(array<Node*, 4> nodes);
	void printMatrixH();
	void printMatrixC();
	Eigen::Matrix4d getFinalMatrixHInPoint(int i);
	void calculateNbydXAndbydY();
	void reverseJacobMatrix();


private :
	Eigen::Matrix4d setMatrixHInPoint(int PointIndex, double k);
	Eigen::Matrix4d getdNbyNxAnddNbydxTransposedMatrix(int pointIndex);
	Eigen::Vector4d getdNbydx(int PointIndex);
	Eigen::Vector4d getdNbydy(int PointIndex);
	Eigen::Matrix4d setMatrixCInPoint(int PointIndex, double cp, double ro);
	Eigen::Matrix4d getNAndNMatrix(int pointIndex);
};


void AllMatrix::calculateMatrixH(double k, array<Node*, 4> nodes) {
	for (int i = 0; i < 3; i++)
	{
		print(i);
		cout << endl;
	}
	setJacobMatrices(nodes);
	reverseJacobMatrix();
	calculateNbydXAndbydY();
	matrixH = setMatrixHInPoint(0, k) + setMatrixHInPoint(1, k) + setMatrixHInPoint(2, k) + setMatrixHInPoint(3, k);
}

Eigen::Matrix4d AllMatrix::setMatrixHInPoint(int PointIndex, double k) {
	Eigen::Matrix4d matrixHInPoint;
	matrixHInPoint = k * getFinalMatrixHInPoint(PointIndex);
	return matrixHInPoint;
}

Eigen::Matrix4d AllMatrix::getFinalMatrixHInPoint(int PointIndex) {
	Eigen::Matrix4d dNbyNxAnddNbydxTransposedMatrixAndDeterminant = getdNbyNxAnddNbydxTransposedMatrix(PointIndex) * jacobMatrices[PointIndex].jacobMatrix.determinant();
	return dNbyNxAnddNbydxTransposedMatrixAndDeterminant;
}

Eigen::Matrix4d AllMatrix::getdNbyNxAnddNbydxTransposedMatrix(int pointIndex)
{
	Eigen::Matrix4d dNbyNxAnddNbydxTransposedMatrix;
	Eigen::Vector4d dNbydX = getdNbydx(pointIndex);
	Eigen::Vector4d dNbydY = getdNbydy(pointIndex);
	dNbyNxAnddNbydxTransposedMatrix = dNbydX * dNbydX.transpose()+ dNbydY * dNbydY.transpose();
	return dNbyNxAnddNbydxTransposedMatrix;
}

Eigen::Vector4d AllMatrix::getdNbydx(int PointIndex)
{
	Eigen::Vector4d shapeFunctionDerrivativeBy;
	for (int i = 0; i < 4; i++)
			shapeFunctionDerrivativeBy[i] = derrivativeNbyX[PointIndex][3-i];
		
	return shapeFunctionDerrivativeBy;
}
Eigen::Vector4d AllMatrix::getdNbydy(int PointIndex)
{
	Eigen::Vector4d shapeFunctionDerrivativeBy;
	for (int i = 0; i < 4; i++)
			shapeFunctionDerrivativeBy[i] = derrivativeNbyY[PointIndex][i];
	
	return shapeFunctionDerrivativeBy;
}

void AllMatrix::calculateMatrixC(double cp, double ro, array<Node*, 4> nodes) {
	setJacobMatrices(nodes);
	matrixC=setMatrixCInPoint(0,cp, ro) + setMatrixCInPoint(1,cp,ro) + setMatrixCInPoint(2, cp,ro) + setMatrixCInPoint(3,cp,ro);
}

Eigen::Matrix4d AllMatrix::setMatrixCInPoint(int PointIndex, double cp, double ro) {
	Eigen::Matrix4d matrixCInPoint = getNAndNMatrix(PointIndex) * cp * ro;
	return matrixCInPoint;
}


Eigen::Matrix4d AllMatrix::getNAndNMatrix(int pointIndex)
{
	Eigen::Vector4d vectorFromUniversalElement = UniversalElement::calculatedPoints2D[pointIndex][0];
	Eigen::Matrix4d shapeFunctionsInPoint = vectorFromUniversalElement * vectorFromUniversalElement.transpose() * jacobMatrices[pointIndex].jacobMatrix.determinant();
	return shapeFunctionsInPoint;
}

void AllMatrix::setJacobMatrices(array<Node*, 4> nodes)
{
	
	for (int i = 0; i < 4; i++)
	{
		jacobMatrices[i].setJacobMatrix(nodes, i);
		
	}
}
void AllMatrix::reverseJacobMatrix() {
	for (int i = 0; i < 4; i++)
		reversedJacobMatrix[i].jacobMatrix = (1 / jacobMatrices[i].jacobMatrix.determinant()) * jacobMatrices[i].jacobMatrix.transpose();
}



 void AllMatrix::calculateNbydXAndbydY()
{
	 for (int i = 0; i < 4; i++) {
		 for (int j = 0; j < 4; j++){
			 derrivativeNbyX[i][j] = reversedJacobMatrix[i].jacobMatrix(0,0) * (UniversalElement::calculatedPoints2D[i][2])(j)+ reversedJacobMatrix[i].jacobMatrix(0, 1) * (UniversalElement::calculatedPoints2D[i][1])(j);
			 derrivativeNbyY[i][j] = reversedJacobMatrix[i].jacobMatrix(1,0) * (UniversalElement::calculatedPoints2D[i][2])(j)+ reversedJacobMatrix[i].jacobMatrix(1, 1) * (UniversalElement::calculatedPoints2D[i][1])(j);
				
		 }
	 }
}
 Eigen::Matrix4d AllMatrix::getMatrixH() {
	 return matrixH;
 }
 Eigen::Matrix4d AllMatrix::getMatrixC() {
	 return matrixC;
 }

 void AllMatrix::printMatrixH() {

	 cout << "JacobMatrices" << endl;
	 for (int i = 0; i < 4; i++)
		 cout << jacobMatrices[i].jacobMatrix << endl;
	 
	 cout << " " << endl;
	 cout << "TransposedJacobMatrices " << endl;
	 for (int i = 0; i < 4; i++)
	     cout << jacobMatrices[i].jacobMatrix.transpose() << endl;

	 cout << " " << endl;
	 cout << "TransposedJacobMatrices * 1/determinant " << endl;
	 for (int i = 0; i < 4; i++)
	     cout << 1 / jacobMatrices[i].jacobMatrix.determinant() * jacobMatrices[i].jacobMatrix.transpose() << endl;
	
	 cout << " " << endl;
	 cout << "Derrivative N by X" << endl;
	 for (int i = 0; i < 4; i++)
	 {
		 for (int j = 0; j < 4; j++) {
			 cout << derrivativeNbyX[i][j] << " ";
		 }
		 cout << endl;
	 }
	 cout << " " << endl;
	 cout << "Derrivative N by Y" << endl;
	 for (int i = 0; i < 4; i++)
	 {
		 for (int j = 0; j < 4; j++) {
			 cout << derrivativeNbyY[i][j] << " ";
		 }
		 cout << endl;
	 }
	 cout << " " << endl;
	 cout << "Matrix H in 4 Points" << endl;
	 for (int i = 0; i < 4; i++) {
		 cout << setMatrixHInPoint(i, 25) << endl;
		 cout << " " << endl;
	 }
	 cout << " " << endl;
	 cout << "Matrix H" << endl;
	 cout << matrixH << endl;
	
 }

 void AllMatrix::printMatrixC() {
	 cout << "Matrix C" << endl;
	 cout << matrixC << endl;


 }
