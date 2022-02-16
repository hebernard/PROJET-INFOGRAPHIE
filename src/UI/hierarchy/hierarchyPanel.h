#pragma once

#include "ofMain.h"

class object;

class hierarchyPanel
{
public:
	hierarchyPanel();

	void draw(const vector<object*>& objects);
	void drawFull(const vector<object*>& objects);
	void drawMinimized();

	void setMinimized();
	bool getMinimized();

private:
	ofRectangle rect;
	ofImage icon;
	ofImage iconMinimize;

	bool minimized;
};
