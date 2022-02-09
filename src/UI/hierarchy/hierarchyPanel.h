#pragma once

#include "ofMain.h"

class label;

class hierarchyPanel
{
public:
	hierarchyPanel();

	void draw(const vector<ofNode*>& objects);

private:
	ofRectangle rect;
	label* m_label;
};

