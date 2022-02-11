#pragma once

#include "ofMain.h"

class mainTheme
{
public:

	 //Font & Logo Colors
	 ofColor fontColor;
	 ofColor fontColorAlpha;
	 ofColor logoTopLayerColor;
	 ofColor logoDownLayerColor;

	 //Menu Tool Bar Colors
	 ofColor toolBarColor;
	 ofColor toolBarBorderColor;
	 ofColor toolBarButtonHoverColor;

	 //Dropdown & Hierarchy Colors
	 ofColor panelColor;
	 ofColor panelBorderColor;
	 ofColor panelButtonHoverColor;

	 //Contrast Colors
	 ofColor color1;
	 ofColor color2;
	 ofColor color3;

	 //Scene & Grid Colors
	 ofColor sceneBackgroundColor;
	 ofColor gridColor1;
	 ofColor gridColor2;

	 //Paths
	 string logoPath;
	 string themePath;
	 const string fontRegularPath = "fonts/inter_regular.ttf";
	 const string fontMediumPath = "fonts/inter_medium.ttf";
	 
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

