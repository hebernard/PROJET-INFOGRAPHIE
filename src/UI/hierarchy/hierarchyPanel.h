#pragma once

#include "ofMain.h"
#include "ui/properties/cameraProperties.h"

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

private:
	cameraHierarchyButton* cameraButton;
	ofRectangle rect;
	ofImage icon;

	bool isDrawingCameraProp = false;
	cameraProperties camProp;
};
