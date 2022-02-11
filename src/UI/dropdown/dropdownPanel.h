#pragma once

#include "ofRectangle.h"
#include "mainTheme.h"

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
	mainTheme& t = t.getInstance();
	std::vector<dropdownButton*> buttons;
};

