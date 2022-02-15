#pragma once

#include "ofMain.h"

class label;
class object;
class hierarchySmallButton;

class propertiesPanel
{
public:
	propertiesPanel();

	void draw(const object& obj);

private:

	ofRectangle rect;
	label* m_label;
	hierarchySmallButton* backButton;

};
