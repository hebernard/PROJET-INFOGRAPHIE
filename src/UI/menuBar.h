#pragma once

#include "ofxDatGuiComponent.h"

class dropdown;
class menuBarButton;
class menuBarButtonAlt;

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
	menuBarButton* exportButton;
	menuBarButtonAlt* themeButton;

	void drawLogo();
	void drawLine();

	void onImportButtonEvent(ofxDatGuiButtonEvent e);
	void onExportButtonEvent(ofxDatGuiButtonEvent e);
	void onThemeButtonEvent(ofxDatGuiButtonEvent e);
};

