#pragma once

#include "ofMain.h"
#include "mainTheme.h"

class label;
class object;
class hierarchySmallButton;

class propertiesPanel
{
public:
	propertiesPanel();

	void draw(const object& obj);

private:
	mainTheme& t = t.getInstance();

	ofRectangle rect;
	label* m_label;
	hierarchySmallButton* backButton;
};
