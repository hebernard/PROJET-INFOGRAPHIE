#pragma once

#include "ofMain.h"

class object : public ofNode
{
public:
	object() {}
	virtual ~object() {}

	virtual void customDraw() {}
	virtual void drawHierarchy(int x, int y) {}
};

