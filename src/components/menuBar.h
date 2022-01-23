#pragma once

#include "ofxDatGuiComponent.h"
#include "ofxDatGui.h"

class menuBar : public ofxDatGuiComponent
{
public:
	menuBar() : ofxDatGuiComponent("menuBar")
	{
		window = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
		window->addLabel("test");
		window->addFolder("test1");
	}

	~menuBar()
	{
		window = nullptr;
	}

	void setTheme(const ofxDatGuiTheme* theme)
	{
		// todo set theme for each item
	}

	void update()
	{
		window->update();
	}

	void draw()
	{
		window->draw();
	}

private:
	ofxDatGui* window;
};

