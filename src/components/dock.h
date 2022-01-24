#pragma once

#include "ofxDatGuiComponent.h"
#include "ofxDatGui.h"
#include "dockButton.h"

class dock : public ofxDatGuiComponent
{
public:
	dock() : ofxDatGuiComponent("dock")
	{
		setTheme(ofxDatGuiComponent::getTheme());

		// todo
		dockButton* test = new dockButton("images\\icons\\airplane.png");
		dockButton* test2 = new dockButton("images\\icons\\airplane.png");
		dockButton* test3 = new dockButton("images\\icons\\airplane.png");
		dockButton* test4 = new dockButton("images\\icons\\airplane.png");
		dockButtons.push_back(test);
		dockButtons.push_back(test2);
		dockButtons.push_back(test3);
		dockButtons.push_back(test4);

		mRect.width = 50;
		//mRect.height = dockButtons.size() * dockButtons.front()->getWidth() + ((dockButtons.size() + 1) * 10);
		mRect.height = 600;
	}

	~dock()
	{
		for (auto i : dockButtons) delete i;
	}

	void setTheme(const ofxDatGuiTheme* theme)
	{
		setComponentStyle(theme);
	}

	void update()
	{
		setPosition(xOffset, ofGetHeight() / 2 - mRect.height / 2);

		for (auto i : dockButtons)
		{
			i->update();
		}
	}

	void draw()
	{
		ofPushStyle();
		ofFill();
		// dark border
		ofSetColor(ofColor(223, 223, 223));
		ofDrawRectRounded(mRect.x - 4, mRect.y - 4, mRect.width + 8, mRect.height + 8, 14);

		// light border
		ofSetColor(ofColor::white);
		ofDrawRectRounded(mRect.x - 2, mRect.y - 2, mRect.width + 4, mRect.height + 4, 14);
		
		ofSetColor(ofColor(245, 245, 245));
		ofDrawRectRounded(mRect.x, mRect.y, mRect.width, mRect.height, 14);

		for (auto i : dockButtons)
		{
			i->draw();
		}
		ofPopStyle();
	}

	void setPosition(int x, int y)
	{
		mRect.x = x;
		mRect.y = y;

		int spacing = 10;
		int offsetX = 5;
		int buttonWidth = dockButtons.front()->getWidth();
		for (int i = 0; i < dockButtons.size(); i++)
		{
			dockButtons[i]->setPosition(x + offsetX, y + (spacing * (i + 1)) + (i * buttonWidth));
		}
	}

private:
	ofRectangle mRect;
	const int xOffset = 20;

	vector<dockButton*> dockButtons;
};

