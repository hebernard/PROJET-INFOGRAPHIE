#pragma once
#include "ofxDatGuiButton.h"
#include "ofImage.h"

class label;

class recButtonTheme : public ofxDatGuiTheme
{
public:
	recButtonTheme()
	{
		layout.width = 32;
		layout.height = 30;
		init();
	}
};

class recButton : public ofxDatGuiButton
{
public:
	recButton(std::string iconPath);

	void draw();
	void update(int x, int y);
	void updateIcon(std::string iconPath);
	void rec();

private:

	ofImage icon;
	bool recMode;

	void setTheme(const ofxDatGuiTheme* theme);
};


