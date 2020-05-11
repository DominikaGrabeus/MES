#pragma once
#include<iostream>
using namespace std;
class Node
{
private:
	float x;
	float y;
	int id;
	double temperature;
	bool BC;

public:
	Node();
	Node(float x, float y, int id, double temperature, bool BC);
	int getNodeId();
	void printNode();
	float getX();
	float getY();
	bool getBC();
	double getDistance(Node node);


private:
	void setBCValue(double a, double b);

};
Node::Node()
{
	this->x = 0;
	this->y = 0;
	this->id = 0;
	this->BC = false;
}


Node::Node(float x, float y, int id, double temperature, bool BC)
{
	this->x = x;
	this->y = y;
	this->id = id;
	this->temperature = temperature;
	this->BC = BC;

}

void Node::setBCValue(double height, double weight) {
	if (x == 0 || x == height || y == 0 || y == weight)
		BC = true;
	else
		BC = false;
}
void Node::printNode() {
	cout << "node :" << id << " " << "      x: " << x << "    y: " << y << endl;
}
int Node::getNodeId() {

	return id;
}
float Node::getX() {
	return x;
}
float Node::getY() {
	return y;

}
bool Node::getBC() {
	return BC;
}
double Node::getDistance(Node node) {
	return sqrt(pow((node.x) - (this->x), 2) + pow((node.y) - (this->y), 2));
}
