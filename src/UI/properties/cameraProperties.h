#pragma once
#include "ofMain.h"

class hierarchySmallButton;

class cameraProperties
{
public:
	hierarchySmallButton* backButton;

	cameraProperties();
	void draw();

private:
	ofRectangle rect;
};

