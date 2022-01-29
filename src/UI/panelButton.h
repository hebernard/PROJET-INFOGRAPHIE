#pragma once

#include "ofxDatGuiButton.h"

class label;

class panelButtonTheme : public ofxDatGuiTheme
{
public:
	panelButtonTheme()
	{
		layout.width = 224;
		layout.height = 36;
		init();
	}
};

class panelButton : public ofxDatGuiButton
{
public:
	panelButton(string iconPath);
	void setTheme(const ofxDatGuiTheme* theme);

	void draw();
	void update();
	void setPosition(int x, int y);

private:
	ofImage icon;
	label* m_label;

	int iconOffset;
};

