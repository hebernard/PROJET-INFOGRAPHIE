#pragma once

#include "ofRectangle.h"

class dropdownButton;

class dropdownPanel
{
public:
	ofRectangle rect;

	dropdownPanel();
	void update(int x, int y);
	void draw();

	void addButton(dropdownButton* button);

private:
	std::vector<dropdownButton*> buttons;
};

