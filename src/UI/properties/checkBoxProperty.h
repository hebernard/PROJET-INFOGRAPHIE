#pragma once
#include "ofMain.h"

class checkBoxProperty
{
public:
	checkBoxProperty(std::string label, bool& ref);

	void draw(int x, int y, int width);
	int getHeight();

private:
	ofRectangle rect;

	bool hovered = false;
	bool previousState;
	bool& m_ref;
	std::string m_label;
	glm::vec2 labelSize;

	ofImage icon;
	ofRectangle checkBox;

	void setIcon();
};

