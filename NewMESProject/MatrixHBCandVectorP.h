#pragma once
#include "UniversalElement.h"
#include "Node.h"
#include <Eigen/Dense>
#include <cmath>

class MatrixHBCandVectorP {
public:
	Eigen::Vector4d bottomVector;
	Eigen::Vector4d rightVector;
	Eigen::Vector4d topVector;
	Eigen::Vector4d leftVector;
	Eigen::Matrix4d bottomMatrix;
	Eigen::Matrix4d rightMatrix;
	Eigen::Matrix4d topMatrix;
	Eigen::Matrix4d leftMatrix;
	double xsi1, eta1, xsi2, eta2;

	void calculateMatrixHBCandVectorP(double convection, double temperature, array<Node*, 4> nodes);

private:
	Eigen::Matrix4d calculateMatrixInProperSide(double eta1, double eta2, double xsi1, double xsi2);
	double calculateDeterminant(Node node1, Node node2);
	Eigen::Vector4d calculateShapeFunction1dInMatrixHBC(double eta, double xsi);
};

 void MatrixHBCandVectorP::calculateMatrixHBCandVectorP(double convection, double temperature, array<Node*, 4> nodes) {
	
	 bottomMatrix.fill(0);
	 rightMatrix.fill(0);
	 topMatrix.fill(0);
	 leftMatrix.fill(0);
	 bottomVector.fill(0);
	 rightVector.fill(0);
	 topVector.fill(0);
	 leftVector.fill(0);

	 if ((nodes[0]->getBC()) && (nodes[1]->getBC())) {
		 eta1 = -1;
		 eta2 = -1;
		 xsi1 = -1 / sqrt(3);
		 xsi2 = 1 / sqrt(3);
		 double detJ = calculateDeterminant(*nodes[0], *nodes[1]);
		 bottomMatrix = calculateMatrixInProperSide(eta1, eta2, xsi1, xsi2) * convection * detJ;
	 }
	 if ((nodes[1]->getBC()) && (nodes[2]->getBC())) {
		 eta1 = -1 / sqrt(3);
		 eta2 = 1 / sqrt(3);
		 xsi1 = 1;
		 xsi2 = 1;
		 double detJ = calculateDeterminant(*nodes[1], *nodes[2]);
		 rightMatrix = calculateMatrixInProperSide(eta1, eta2, xsi1, xsi2) * convection * detJ;
	 }
	 if ((nodes[2]->getBC()) && (nodes[3]->getBC())) {
		 eta1 = 1;
		 eta2 = 1;
		 xsi1 = 1 / sqrt(3);
		 xsi2 = -1 / sqrt(3);
		 double detJ = calculateDeterminant(*nodes[2], *nodes[3]);
		 topMatrix = calculateMatrixInProperSide(eta1, eta2, xsi1, xsi2) * convection * detJ;
	 }
	 if ((nodes[3]->getBC()) && (nodes[0]->getBC())) {
		 eta1 = 1 / sqrt(3);
		 eta2 = -1 / sqrt(3);
		 xsi1 = -1;
		 xsi2 = -1;
		 double detJ = calculateDeterminant(*nodes[3], *nodes[0]);
		 leftMatrix = calculateMatrixInProperSide(eta1, eta2, xsi1, xsi2) * convection * detJ;
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

 Eigen::Vector4d MatrixHBCandVectorP::calculateShapeFunction1dInMatrixHBC(double eta, double xsi ) {
	 Eigen::Vector4d ShapeFunction1d;
	 ShapeFunction1d[0] = 0.25 * (1 - xsi) * (1 - eta);
	 ShapeFunction1d[1] = 0.25 * (1 + xsi) * (1 - eta);
	 ShapeFunction1d[2] = 0.25 * (1 + xsi) * (1 + eta);
	 ShapeFunction1d[3] = 0.25 * (1 - xsi) * (1 + eta);
	 return ShapeFunction1d;

}