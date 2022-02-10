#pragma once

#include "ofMain.h"

class label;
class object;

class hierarchyPanel
{
public:
	hierarchyPanel();

	void draw(const vector<object*>& objects);

private:
	ofRectangle rect;
	label* m_label;
};

