#pragma once

#include "ofMain.h"
#include "cameraProperties.h"

class object;
class cameraHierarchyButton;

class hierarchyPanel
{
public:
	hierarchyPanel();
	~hierarchyPanel();

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

	bool isDrawingCameraProp = false;
	cameraProperties camProp;

	bool minimized;
};
