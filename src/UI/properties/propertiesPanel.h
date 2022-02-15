#pragma once

#include "ofMain.h"

class object;
class hierarchySmallButton;

class propertiesPanel
{
public:
	propertiesPanel();

	void draw(const object& obj);

private:
	ofRectangle rect;
	hierarchySmallButton* backButton;
};
