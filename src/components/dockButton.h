#pragma once

#include "ofxDatGuiButton.h"

class dockButtonTheme : public ofxDatGuiTheme
{
public:
	dockButtonTheme()
	{
		layout.width = 44;
		layout.height = 36;
		init();
	}
};

class dock;

class dockButton : public ofxDatGuiToggle
{
public:
	int index;

	dockButton(int index, std::string iconPath, dock& dock);
	bool operator != (const dockButton& other);

	void onToggled(ofxDatGuiToggleEvent e);
	void setTheme(const ofxDatGuiTheme* theme);

	void draw();
	void update();

	void setPosition(int newX, int newY);
	int getHeight();

private:
	ofImage icon;
	const int roundness;

	dock& m_dock;
};

