#pragma once
#include <array>
#include "JacobMatrix.h"
#include <Eigen/Dense>
#include <iostream>

using namespace std;

class MatrixH_C : public UniversalElement {
public:
	Eigen::Matrix4d matrix;
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


void MatrixH_C::calculateMatrixH(double k, array<Node*, 4> nodes) {
	/*
	for (int i = 0; i < 3; i++)
	{
		printShapeFunctions(i);               //0-N, 1-Eta, 2-Xsi
		cout << endl;
	}
	*/
	setJacobMatrices(nodes);
	reverseJacobMatrix();
	calculateNbydXAndbydY();
	matrix = setMatrixHInPoint(0, k) + setMatrixHInPoint(1, k) + setMatrixHInPoint(2, k) + setMatrixHInPoint(3, k);
	
}

Eigen::Matrix4d MatrixH_C::setMatrixHInPoint(int PointIndex, double k) {
	Eigen::Matrix4d matrixHInPoint;
	matrixHInPoint = k * getFinalMatrixHInPoint(PointIndex);
	return matrixHInPoint;
}

Eigen::Matrix4d MatrixH_C::getFinalMatrixHInPoint(int PointIndex) {
	Eigen::Matrix4d dNbyNxAnddNbydxTransposedMatrixAndDeterminant = getdNbyNxAnddNbydxTransposedMatrix(PointIndex) * jacobMatrices[PointIndex].jacobMatrix.determinant();
	return dNbyNxAnddNbydxTransposedMatrixAndDeterminant;
}

Eigen::Matrix4d MatrixH_C::getdNbyNxAnddNbydxTransposedMatrix(int pointIndex)
{
	Eigen::Matrix4d dNbyNxAnddNbydxTransposedMatrix;
	Eigen::Vector4d dNbydX = getdNbydx(pointIndex);
	Eigen::Vector4d dNbydY = getdNbydy(pointIndex);
	dNbyNxAnddNbydxTransposedMatrix = dNbydX * dNbydX.transpose()+ dNbydY * dNbydY.transpose();
	return dNbyNxAnddNbydxTransposedMatrix;
}

Eigen::Vector4d MatrixH_C::getdNbydx(int PointIndex)
{
	Eigen::Vector4d shapeFunctionDerrivativeBy;
	for (int i = 0; i < 4; i++)
			shapeFunctionDerrivativeBy[i] = derrivativeNbyX[PointIndex][3-i];
		
	return shapeFunctionDerrivativeBy;
}
Eigen::Vector4d MatrixH_C::getdNbydy(int PointIndex)
{
	Eigen::Vector4d shapeFunctionDerrivativeBy;
	for (int i = 0; i < 4; i++)
			shapeFunctionDerrivativeBy[i] = derrivativeNbyY[PointIndex][i];
	
	return shapeFunctionDerrivativeBy;
}

void MatrixH_C::calculateMatrixC(double cp, double ro, array<Node*, 4> nodes) {
	setJacobMatrices(nodes);
	matrix =setMatrixCInPoint(0,cp, ro) + setMatrixCInPoint(1,cp,ro) + setMatrixCInPoint(2, cp,ro) + setMatrixCInPoint(3,cp,ro);
}

Eigen::Matrix4d MatrixH_C::setMatrixCInPoint(int PointIndex, double cp, double ro) {
	Eigen::Matrix4d matrixCInPoint = getNAndNMatrix(PointIndex) * cp * ro;
	return matrixCInPoint;
}


Eigen::Matrix4d MatrixH_C::getNAndNMatrix(int pointIndex)
{
	Eigen::Vector4d vectorFromUniversalElement = UniversalElement::calculatedPoints2D[pointIndex][0];
	Eigen::Matrix4d shapeFunctionsInPoint = vectorFromUniversalElement * vectorFromUniversalElement.transpose() * jacobMatrices[pointIndex].jacobMatrix.determinant();
	return shapeFunctionsInPoint;
}

void MatrixH_C::setJacobMatrices(array<Node*, 4> nodes)
{
	
	for (int i = 0; i < 4; i++)
	{
		jacobMatrices[i].setJacobMatrix(nodes, i);
		
	}
}
void MatrixH_C::reverseJacobMatrix() {
	for (int i = 0; i < 4; i++)
		reversedJacobMatrix[i].jacobMatrix = (1 / jacobMatrices[i].jacobMatrix.determinant()) * jacobMatrices[i].jacobMatrix.transpose();
}



 void MatrixH_C::calculateNbydXAndbydY()
{
	 for (int i = 0; i < 4; i++) {
		 for (int j = 0; j < 4; j++){
			 derrivativeNbyX[i][j] = reversedJacobMatrix[i].jacobMatrix(0,0) * (UniversalElement::calculatedPoints2D[i][2])(j)+ reversedJacobMatrix[i].jacobMatrix(0, 1) * (UniversalElement::calculatedPoints2D[i][1])(j);
			 derrivativeNbyY[i][j] = reversedJacobMatrix[i].jacobMatrix(1,0) * (UniversalElement::calculatedPoints2D[i][2])(j)+ reversedJacobMatrix[i].jacobMatrix(1, 1) * (UniversalElement::calculatedPoints2D[i][1])(j);
				
		 }
	 }
}

 Eigen::Matrix4d MatrixH_C::getMatrixH() {
	 return matrix;
 }

 Eigen::Matrix4d MatrixH_C::getMatrixC() {
	 return matrix;
 }

 void MatrixH_C::printMatrixH() {

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
	 cout << matrix << endl;
	
 }

 void MatrixH_C::printMatrixC() {
	 cout << "Matrix C" << endl;
	 cout << matrix << endl;


 }
