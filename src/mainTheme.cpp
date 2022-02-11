#include "mainTheme.h"

void mainTheme::setTheme(bool theme)
{
	//DarkTheme
	if (theme) {

		ofFontColor = ofColor(245, 245, 245);
		ofFontColorAlpha = ofColor(245, 245, 245, 128);
		fontColor = 245;
		logoTopLayerColor = 70;
		logoDownLayerColor = 36;
		logoPath = "images/logoDark.png";

		toolBarColor = 18;
		toolBarBorderColor = 53;
		toolBarButtonHoverColor = 35;

		panelColor = 49;
		panelBorderColor = 59;
		panelButtonHoverColor = 100;

		color1 = ofColor(87, 140, 245);
		color2 = ofColor(115, 157, 247);
		color3 = ofColor(58, 119, 243);

		sceneBackgroundColor = ofColor(36, 36, 36);
		gridColor1 = ofColor(50, 50, 50);
		gridColor2 = ofColor(150, 150, 150);

		currentTheme = true;
	}
	//LightTheme
	else {

		ofFontColor = ofColor(18, 18, 18);
		ofFontColorAlpha = ofColor(18, 18, 18, 128);
		fontColor = 18;
		logoTopLayerColor = 202;
		logoDownLayerColor = 168;
		logoPath = "images/logoLight.png";

		toolBarColor = 225;
		toolBarBorderColor = 195;
		toolBarButtonHoverColor = 186;

		panelColor = 196;
		panelBorderColor = 186;
		panelButtonHoverColor = 150;

		color1 = ofColor(3, 218, 198);
		color2 = ofColor(4, 255, 232);
		color3 = ofColor(3, 191, 174);

		sceneBackgroundColor = ofColor(196, 196, 196);
		gridColor1 = ofColor(150, 150, 150);
		gridColor2 = ofColor(200, 200, 200);

		currentTheme = false;
	}
}

bool mainTheme::getTheme()
{
	return currentTheme;
}
