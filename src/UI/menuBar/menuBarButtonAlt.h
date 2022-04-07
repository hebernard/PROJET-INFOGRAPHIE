#pragma once

#include "ofxDatGuiButton.h"
#include "ofImage.h"

class label;

class menuBarButtonAltTheme : public ofxDatGuiTheme
{
public:
	menuBarButtonAltTheme()
	{
		layout.width = 32;
		layout.height = 30;
		init();
	}
};

class menuBarButtonAlt : public ofxDatGuiButton
{
public:
	menuBarButtonAlt(std::string iconPath);

	void draw();
	void update(int x, int y);
	void updateIcon(std::string iconPath);

protected:
	void onMouseRelease(ofPoint m);

private:

	ofImage icon;

	void setTheme(const ofxDatGuiTheme* theme);
};


