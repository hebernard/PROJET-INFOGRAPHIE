#pragma once

#include "ofxDatGuiButton.h"
#include "ofImage.h"
#include "mainTheme.h"

class label;

class dropdownButtonTheme : public ofxDatGuiTheme
{
public:
	dropdownButtonTheme()
	{
		layout.width = 250;
		layout.height = 40;
		init();
	}
};

class dropdownButton : public ofxDatGuiButton
{
public:
	dropdownButton(std::string iconPath, std::string text);

	void draw();
	void update(int x, int y);

private:
	mainTheme& t = t.getInstance();

	label* m_label;
	ofImage icon;

	void setTheme(const ofxDatGuiTheme* theme);
};

