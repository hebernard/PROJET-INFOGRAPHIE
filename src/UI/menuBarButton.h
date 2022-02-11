#pragma once

#include "ofxDatGuiButton.h"
#include "mainTheme.h"

class label;

class menuBarButtonTheme : public ofxDatGuiTheme
{
public:
	menuBarButtonTheme()
	{
		layout.width = 100;
		layout.height = 30;
		init();
	}
};

class menuBarButton : public ofxDatGuiButton
{
public:
	menuBarButton(std::string text);

	void draw();
	void update(int x, int y);

private:
	mainTheme& t = t.getInstance();

	label* m_label;

	void setTheme(const ofxDatGuiTheme* theme);
};

