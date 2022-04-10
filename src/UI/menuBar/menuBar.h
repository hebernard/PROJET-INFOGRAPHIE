#pragma once

#include "ofxDatGuiComponent.h"

class dropdown;
class menuBarButton;
class recButton;
class menuBarButtonAlt;

class menuBar : public ofxDatGuiComponent
{
public:
	menuBar();
	~menuBar();

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
	dropdown* raytracingDropdown;

	menuBarButton* importButton;
	menuBarButton* renderButton;
	menuBarButtonAlt* themeButton;

	void drawLogo();
	void drawLine();

	void onImportButtonEvent();
	void onThemeButtonEvent();
};

