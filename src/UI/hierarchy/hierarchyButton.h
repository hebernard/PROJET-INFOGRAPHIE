#pragma once

#include "ofxDatGuiButton.h"
#include "ofImage.h"
#include "mainTheme.h"

class label;
class object;
class hierarchySmallButton;

class hierarchyButtonTheme : public ofxDatGuiTheme
{
public:
	hierarchyButtonTheme()
	{
		layout.width = 300;
		layout.height = 40;
		init();
	}
};

class hierarchyButton : public ofxDatGuiButton
{
public:
	hierarchyButton(object& obj, std::string iconPath, std::string text);

	void draw();
	void update(int x, int y);

private:
	mainTheme& t = t.getInstance();

	label* m_label;
	ofImage icon;
	object& m_obj;

	hierarchySmallButton* deleteButton;
	hierarchySmallButton* propertiesButton;
	hierarchySmallButton* visibleButton;

	void setTheme(const ofxDatGuiTheme* theme);
	void onClick(ofxDatGuiButtonEvent e);
};

