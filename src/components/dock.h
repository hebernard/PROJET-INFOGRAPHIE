#pragma once

#include "ofxDatGuiComponent.h"

class dockButton;
class importPanel;

class dockTheme : public ofxDatGuiTheme
{
public:
	dockTheme()
	{
		layout.width = 66;
		layout.height = 600;
		init();
	}
};

class dock : public ofxDatGuiComponent
{
public:
	dock();
	virtual ~dock();

	void setTheme(const ofxDatGuiTheme* theme);

	void update();
	void drawClosed();
	void drawOpened();
	void draw();

	void setPosition(int x, int y);

	void notifyButtonToggled(int index, bool toggled);

private:
	ofRectangle mRect;
	ofRectangle openedRect;
	const int roundness;
	bool isOpened;

	std::vector<dockButton*> dockButtons;
	int currentToggled;

	importPanel* m_importPanel;
};

