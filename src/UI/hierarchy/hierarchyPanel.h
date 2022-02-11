#pragma once

#include "ofMain.h"
#include "mainTheme.h"

class label;
class object;

class hierarchyPanel
{
public:
	hierarchyPanel();

	void draw(const vector<object*>& objects);

private:

	mainTheme& t = t.getInstance();

	ofRectangle rect;
	label* m_label;
	ofImage icon;
};

