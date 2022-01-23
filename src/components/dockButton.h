#pragma once

#include "ofxDatGuiComponent.h"

class dockButton : public ofxDatGuiButton
{
public:
	dockButton(string iconPath) : ofxDatGuiButton("dockButton")
	{
		mType = ofxDatGuiType::BUTTON;
		ofxDatGuiComponent::setWidth(40, 1);
		height = 40;

		icon.load(iconPath);
		icon.resize(24, 24);
	}

	void draw()
	{
		if (hovered)
		{
			ofSetColor(ofColor(227, 227, 227));
		}
		else if (mMouseDown)
		{
			ofSetColor(ofColor(238, 238, 238));
		}

		ofDrawRectRounded(x, y, getWidth(), getHeight(), 10);

		if (icon.isAllocated())
		{
			icon.draw(x + (getWidth() / 2 - icon.getWidth() / 2), y + (getHeight() / 2 - icon.getHeight() / 2));
		}
	}

	void setPosition(int newX, int newY)
	{
		x = newX;
		y = newY;
	}

	int getHeight()
	{
		return height;
	}

	void onMouseMoved(int x, int y)
	{
		if (isInBounds(x, y))
		{
			hovered = true;
		}
		else
		{
			hovered = false;
		}
	}

private:
	ofImage icon;
	int height;

	bool hovered = false;
	bool selected = false;

	bool isInBounds(int eX, int eY)
	{
		return eX >= x && eX <= x + getWidth() && eY >= y && eY <= y + getHeight();
	}
};

