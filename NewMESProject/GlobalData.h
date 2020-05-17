#pragma once
class GlobalData {
public:

	float height;
	float width;
	int nH;  //liczba wezlow po dlugosci
	int nW;  //liczba wezlow po wysokosci
	int nE;  // liczba elementow  (mH-1)*(mW-1)
	int nN;  // liczba wezlow mH*mW
	double initialTemperature;
	double ambientTemperature;
	double heat;   //cieplo wlasciwe =cp
	double density;   //gestsc= ro
	double conductivity;   //k
	double alfa;
	double simulationTime;
	double stepTime;

	void setGlobalData(float height, float width, int nH, int nW, double initialTemperature, double ambientTemperature, double heat, double density, double conductivity, double alfa, double simulationTime, double stepTime);



};

void GlobalData::setGlobalData(float height, float width, int nH, int nW, double initialTemperature, double ambientTemperature, double heat, double density, double conductivity, double alfa,double simulationTime, double stepTime) {
	this->height = height;
	this->width = width;
	this->nH = nH;
	this->nW = nW;
	this->nE = (nH - 1) * (nW - 1);
	this->nN = nH * nW;
	this->initialTemperature = initialTemperature;
	this->ambientTemperature =ambientTemperature;
	this->heat = heat;
	this->density = density;
	this->conductivity = conductivity;
	this->alfa = alfa;
	this->simulationTime = simulationTime;
	this->stepTime = stepTime;

}