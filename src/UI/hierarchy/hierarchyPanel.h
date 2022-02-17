#pragma once

#include "ofMain.h"

class object;

class hierarchyPanel
{
public:
	hierarchyPanel();

	void setup();
	void draw(const vector<object*>& objects);
	void drawOpened(const vector<object*>& objects);
	void drawMinimized();

	void onMinimized(ofMouseEventArgs& mouse);
	bool getMinimized();

private:
	ofRectangle rect;
	ofImage icon;
	ofImage iconMinimize;

	bool minimized;
};
