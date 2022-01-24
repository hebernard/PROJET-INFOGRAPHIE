#pragma once

#include "ofxDatGuiComponent.h"

class dockButtonTheme : public ofxDatGuiTheme
{
public:
	dockButtonTheme()
	{
		layout.width = 40;
		layout.height = 40;
		init();
	}
};

class dockButton : public ofxDatGuiButton
{
public:
	dockButton(string iconPath) : ofxDatGuiButton("dockButton")
	{
		mType = ofxDatGuiType::BUTTON;

		icon.load(iconPath);
		icon.resize(24, 24);
		setTheme(new dockButtonTheme());
	}

	void setTheme(const ofxDatGuiTheme* theme)
	{
		setComponentStyle(theme);
		ofxDatGuiComponent::setWidth(theme->layout.width, theme->layout.labelWidth);
	}

	void draw()
	{
		ofPushStyle();
		ofFill();
		if (mFocused && mMouseDown)
		{
			ofSetColor(ofColor(227, 227, 227));
		}
		else if (mMouseOver)
		{
			ofSetColor(ofColor(238, 238, 238));
		}

		ofDrawRectRounded(x, y, getWidth(), getHeight(), 10);

		if (icon.isAllocated())
		{
			icon.draw(x + (getWidth() / 2 - icon.getWidth() / 2), y + (getHeight() / 2 - icon.getHeight() / 2));
		}
		ofPopStyle();
	}

	void update()
	{
		ofxDatGuiComponent::update();
	}

	void setPosition(int newX, int newY)
	{
		x = newX;
		y = newY;
	}

	int getHeight()
	{
		return mStyle.height;
	}

private:
	ofImage icon;
};

