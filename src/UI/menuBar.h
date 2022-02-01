#pragma once

#include "ofxDatGuiComponent.h"

class dropdown;

class menuBar : public ofxDatGuiComponent
{
public:
	menuBar();
	void setTheme(const ofxDatGuiTheme* theme) {}

	void draw();
	void update();

	void setPosition(int x, int y);

private:
	ofRectangle rect;
	ofImage logo;
	dropdown* dropdown2d;
	dropdown* dropdown3d;

	void drawLogo();
	void drawLine();
};

