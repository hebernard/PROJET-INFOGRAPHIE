#pragma once

#include "ofxDatGuiComponent.h"
#include "mainTheme.h"

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

	mainTheme& t = t.getInstance();

	ofRectangle rect;
	ofImage logo;

	dropdown* dropdown2d;
	dropdown* dropdown3d;

	menuBarButton* importButton;
	menuBarButton* themeButton;

	void drawLogo();
	void drawLine();

	void onImportButtonEvent(ofxDatGuiButtonEvent e);
	void onThemeButtonEvent(ofxDatGuiButtonEvent e);
};

