#pragma once

#include "ofMain.h"

class object;

class hierarchyPanel
{
public:
	hierarchyPanel();

	void draw(const vector<object*>& objects);

private:
	ofRectangle rect;
	ofImage icon;
};
