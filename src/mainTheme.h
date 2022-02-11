#pragma once

#include "ofMain.h"

class mainTheme
{
public:

	 //Font & Logo Colors
	 ofColor ofFontColor;
	 ofColor ofFontColorAlpha;
	 int fontColor;
	 int logoTopLayerColor;
	 int logoDownLayerColor;
	 string logoPath;

	 //Menu Tool Bar Colors
	 int toolBarColor;
	 int toolBarBorderColor;
	 int toolBarButtonHoverColor;

	 //Dropdown & Hierarchy Colors
	 int panelColor;
	 int panelBorderColor;
	 int panelButtonHoverColor;

	 //Contrast Colors
	 ofColor color1;
	 ofColor color2;
	 ofColor color3;

	 //Scene & Grid Colors
	 ofColor sceneBackgroundColor;
	 ofColor gridColor1;
	 ofColor gridColor2;
	 
	 static mainTheme& getInstance()
	 {
		 static mainTheme instance;
		 return instance;
	 }

	 void setTheme(bool theme);
	 bool getTheme();

private:

	mainTheme() {}

	bool currentTheme;

};

