#pragma once

#include "ofRectangle.h"

class dropdownButton;

class dropdownPanel
{
public:
	dropdownPanel();
	void update(int x, int y);
	void draw();

	void addButton(dropdownButton* button);

private:
	ofRectangle rect;
	std::vector<dropdownButton*> buttons;
};

