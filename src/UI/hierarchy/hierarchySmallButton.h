#pragma once

#include "ofxDatGuiButton.h"

class hierarchySmallButtonTheme : public ofxDatGuiTheme
{
public:
	hierarchySmallButtonTheme()
	{
		layout.width = 30;
		layout.height = 30;
		init();
	}
};

class hierarchySmallButton : public ofxDatGuiButton
{
public:
	hierarchySmallButton(std::string iconPath);

	void draw();
	void update(int x, int y);

	void changeIcon(std::string path);

private:
	ofImage icon;

	void setTheme(const ofxDatGuiTheme* theme);
};

