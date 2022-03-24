#pragma once
#include "ofMain.h"
#include "label.h"

class element
{
public:
	string label;
	glm::vec2 labelSize;
	ofRectangle rect;
	int height;
	bool hovered = false;
	bool selected = false;

	element(string l, int h) : label(l), rect(), height(h)
	{
		rect.height = height;
		labelSize = label::getSize(l, 10);
	}

	void draw(int x, int y, int width)
	{
		rect.x = x;
		rect.y = y;
		rect.width = width;

		hovered = rect.inside(ofGetMouseX(), ofGetMouseY());

		ofPushStyle();
		if (hovered || selected)
		{
			ofSetColor(mainTheme::panelButtonHoverColor());
		}
		ofDrawRectangle(rect);
		ofPopStyle();

		drawText(rect.x + rect.width/2 - labelSize.x / 2, rect.y + labelSize.y + 5, label, 10);
	}
};

class dropdownProperty
{
public:
	dropdownProperty(string label);

	void setElements(vector<string> el);

	void draw(int x, int y, int w);

private:
	vector<element> elements;

	string m_label;
	glm::vec2 labelSize;
	ofRectangle rect, dropdownRect;

	string current;

	bool focused = false;
};
