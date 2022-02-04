#pragma once

#include "ofxDatGuiComponent.h"

class dropdown;
class menuBarButton;

class menuBar : public ofxDatGuiComponent
{
public:
	menuBar();
	void setTheme(const ofxDatGuiTheme* theme) {}

	void draw();
	void update();

	void setPosition(int x, int y);

	void notifyDropdownClicked(int index);

private:
	ofRectangle rect;
	ofImage logo;

	dropdown* dropdown2d;
	dropdown* dropdown3d;

	menuBarButton* importButton;

	void drawLogo();
	void drawLine();

	void onImportButtonEvent(ofxDatGuiButtonEvent e);
};

