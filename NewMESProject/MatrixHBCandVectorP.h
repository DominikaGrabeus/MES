#pragma once
#include "UniversalElement.h"
#include "Node.h"
#include <Eigen/Dense>
#include <cmath>

class MatrixHBCandVectorP {
public:
	Eigen::Vector4d vectorP;
	Eigen::Matrix4d matrixHBCLocal;
	double xsi1, eta1, xsi2, eta2;

	void calculateMatrixHBCandVectorP(double convection, double temperature, array<Node*, 4> nodes);

private:
	Eigen::Matrix4d calculateMatrixInProperSide(double eta1, double eta2, double xsi1, double xsi2);
	Eigen::Vector4d calculateVectorInProperSide(double eta1, double eta2, double xsi1, double xsi2);
	double calculateDeterminant(Node node1, Node node2);
	Eigen::Vector4d calculateShapeFunction1dInMatrixHBC(double eta, double xsi);
};

 void MatrixHBCandVectorP::calculateMatrixHBCandVectorP(double convection, double temperature, array<Node*, 4> nodes) {
	 matrixHBCLocal.fill(0);
	 vectorP.fill(0);

	 if ((nodes[0]->getBC()) && (nodes[1]->getBC())) {
		 eta1 = -1;
		 eta2 = -1;
		 xsi1 = -1 / sqrt(3);
		 xsi2 = 1 / sqrt(3);
		 double detJ = calculateDeterminant(*nodes[0], *nodes[1]);
		 matrixHBCLocal += calculateMatrixInProperSide(eta1, eta2, xsi1, xsi2) * convection * detJ;
		 vectorP += -calculateVectorInProperSide(eta1, eta2, xsi1, xsi2) * convection * temperature * detJ;
	 }
	 if ((nodes[1]->getBC()) && (nodes[2]->getBC())) {
		 eta1 = -1 / sqrt(3);
		 eta2 = 1 / sqrt(3);
		 xsi1 = 1;
		 xsi2 = 1;
		 double detJ = calculateDeterminant(*nodes[1], *nodes[2]);
		 matrixHBCLocal += calculateMatrixInProperSide(eta1, eta2, xsi1, xsi2) * convection * detJ;
		 vectorP += -calculateVectorInProperSide(eta1, eta2, xsi1, xsi2) * convection * temperature * detJ;
	 }
	 if ((nodes[2]->getBC()) && (nodes[3]->getBC())) {
		 eta1 = 1;
		 eta2 = 1;
		 xsi1 = 1 / sqrt(3);
		 xsi2 = -1 / sqrt(3);
		 double detJ = calculateDeterminant(*nodes[2], *nodes[3]);
		 matrixHBCLocal += calculateMatrixInProperSide(eta1, eta2, xsi1, xsi2) * convection * detJ;
		 vectorP += -calculateVectorInProperSide(eta1, eta2, xsi1, xsi2) * convection * temperature * detJ;
	 }
	 if ((nodes[3]->getBC()) && (nodes[0]->getBC())) {
		 eta1 = 1 / sqrt(3);
		 eta2 = -1 / sqrt(3);
		 xsi1 = -1;
		 xsi2 = -1;
		 double detJ = calculateDeterminant(*nodes[3], *nodes[0]);
		 matrixHBCLocal += calculateMatrixInProperSide(eta1, eta2, xsi1, xsi2) * convection * detJ;
		 vectorP += -calculateVectorInProperSide(eta1, eta2, xsi1, xsi2) * convection * temperature * detJ;
	 }
 }
 double MatrixHBCandVectorP::calculateDeterminant(Node node1, Node node2) {
	 return sqrt(pow(node1.getX() - node2.getX(), 2) + pow(node1.getY() - node2.getY(), 2)) / 2;
 }

 Eigen::Matrix4d MatrixHBCandVectorP::calculateMatrixInProperSide(double eta1, double eta2, double xsi1, double xsi2)
{
	 Eigen::Matrix<double, 4, 4> matrix1 = calculateShapeFunction1dInMatrixHBC(eta1,xsi1) * calculateShapeFunction1dInMatrixHBC(eta1, xsi1).transpose();
	 Eigen::Matrix<double, 4, 4> matrix2 = calculateShapeFunction1dInMatrixHBC(eta2, xsi2) * calculateShapeFunction1dInMatrixHBC(eta2, xsi2).transpose();
     return (matrix1 + matrix2);
}

 Eigen::Vector4d MatrixHBCandVectorP::calculateVectorInProperSide(double eta1, double eta2, double xsi1, double xsi2) {

	 Eigen::Vector4d vector1 = calculateShapeFunction1dInMatrixHBC(eta1, xsi1);
	 Eigen::Vector4d vector2 = calculateShapeFunction1dInMatrixHBC(eta2, xsi2);
	 return (vector1 + vector2);

 }

 Eigen::Vector4d MatrixHBCandVectorP::calculateShapeFunction1dInMatrixHBC(double eta, double xsi ) {
	 Eigen::Vector4d ShapeFunction1d;
	 ShapeFunction1d[0] = 0.25 * (1 - xsi) * (1 - eta);
	 ShapeFunction1d[1] = 0.25 * (1 + xsi) * (1 - eta);
	 ShapeFunction1d[2] = 0.25 * (1 + xsi) * (1 + eta);
	 ShapeFunction1d[3] = 0.25 * (1 - xsi) * (1 + eta);
	 return ShapeFunction1d;

}