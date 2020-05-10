#pragma once
class GlobalData {
public:

	float height;
	float width;
	int nH;  //liczba wezlow po dlugosci
	int nW;  //liczba wezlow po wysokosci
	int nE;  // liczba elementow  (mH-1)*(mW-1)
	int nN;  // liczba wezlow mH*mW
	double temperature;

	void setGlobalData(float height, float width, int nH, int nW, double temperature);

};

void GlobalData::setGlobalData(float height, float width, int nH, int nW, double temperature) {
	this->height = height;
	this->width = width;
	this->nH = nH;
	this->nW = nW;
	this->nE = (nH - 1) * (nW - 1);
	this->nN = nH * nW;
	this->temperature = temperature;

}