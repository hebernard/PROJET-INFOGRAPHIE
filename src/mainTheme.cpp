#include "mainTheme.h"

void mainTheme::setTheme(bool theme)
{
	//DarkTheme
	if (theme) {

		fontColor = ofColor(245, 245, 245);
		fontColorAlpha = ofColor(245, 245, 245, 128);
		logoTopLayerColor = ofColor(70, 70, 70);
		logoDownLayerColor = ofColor(36, 36, 36);
		logoPath = "images/logoDark.png";
		themePath = "images/icons/moon.png";

		toolBarColor = ofColor(18, 18, 18);
		toolBarBorderColor = ofColor(53, 53, 53);
		toolBarButtonHoverColor = ofColor(35, 35, 35);

		panelColor = ofColor(49, 49, 49);
		panelBorderColor = ofColor(59, 59, 59);
		panelButtonHoverColor = ofColor(100, 100, 100);

		color1 = ofColor(87, 140, 245);
		color2 = ofColor(115, 157, 247);
		color3 = ofColor(58, 119, 243);

		sceneBackgroundColor = ofColor(36, 36, 36);
		gridColor1 = ofColor(50, 50, 50, 120);
		gridColor2 = ofColor(150, 150, 150);

		currentTheme = true;
	}
	//LightTheme
	else {

		fontColor = ofColor(46, 46, 46);
		fontColorAlpha = ofColor(46, 46, 46, 128);
		logoTopLayerColor = ofColor(217, 217, 217);
		logoDownLayerColor = ofColor(196, 196, 196);
		logoPath = "images/logoLight.png";
		themePath = "images/icons/sun.png";

		toolBarColor = ofColor(237, 237, 237);
		toolBarBorderColor = ofColor(178, 178, 178);
		toolBarButtonHoverColor = ofColor(219, 219, 219);

		panelColor = ofColor(232, 232, 232);
		panelBorderColor = ofColor(212, 212, 212);
		panelButtonHoverColor = ofColor(195, 195, 195);

		color1 = ofColor(86, 138, 242);
		color2 = ofColor(91, 146, 255);
		color3 = ofColor(81, 131, 229);

		sceneBackgroundColor = ofColor(128, 128, 128);
		gridColor1 = ofColor(100, 100, 100, 120);
		gridColor2 = ofColor(200, 200, 200);

		currentTheme = false;
	}
}

bool mainTheme::getTheme()
{
	return currentTheme;
}
