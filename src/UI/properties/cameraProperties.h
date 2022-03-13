#pragma once
#include "ofMain.h"
#include "cameraPropertiesButton.h"

class hierarchySmallButton;

class cameraProperties
{
public:

	hierarchySmallButton* backButton;

	cameraProperties();
	void draw();

private:
	ofRectangle rect;

	int offset = 20;
	int buttonWidth;

	cameraPropertiesButton exportImage, exportSeqImage;
	cameraPropertiesButton perspective, orthogonal;
	cameraPropertiesButton backgroundDefault, backgroundCustom;
	cameraPropertiesButton showGrid, hideGrid;
};
