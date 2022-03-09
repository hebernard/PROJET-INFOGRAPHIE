#pragma once

#include "ofMain.h"

class object;
class cameraHierarchyButton;

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
	cameraHierarchyButton* cameraButton;
	ofRectangle rect;
	ofImage icon;
	ofImage iconMinimize;

	bool minimized;
};
