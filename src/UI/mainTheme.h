#pragma once
#include "ofMain.h"

class mainTheme
{
public:

	static bool darkTheme;

	//Font & logo paths
	static const std::string fontRegularPath;
	static const std::string fontMediumPath;
	static std::string logoPath();
	static std::string themePath();

	//Font colors
	static ofColor logoTopLayerColor();
	static ofColor logoDownLayerColor();

	//Logo colors
	static ofColor fontColor();
	static ofColor fontColorAlpha();

	//Menu tool bar colors
	static ofColor toolBarColor();
	static ofColor toolBarBorderColor();
	static ofColor toolBarButtonHoverColor();

	//Dropdown & Hierarchy colors
	static ofColor panelColor();
	static ofColor panelBorderColor();
	static ofColor panelButtonHoverColor();

	//Contrast colors
	static ofColor color1();
	static ofColor color2();
	static ofColor color3();

	static ofColor recColor();

	//Scene & Grid colors
	static ofColor sceneBackgroundColor();
	static ofColor gridColor1();
	static ofColor gridColor2();

};


