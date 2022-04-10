#pragma once
#include <iostream>
#include "glm/glm.hpp"
#include <functional>

class ofRectangle;
class ofFbo;

class uiComponent
{
public:
	std::function<void()> onClick;

	uiComponent(float width, float height);
	virtual ~uiComponent();

	virtual void update(int x, int y, int originX = 0, int originY = 0);
	virtual void draw() = 0;

	void setWidth(float w);
	void setHeight(float h);

	float getX();
	float getY();
	float getLeft();
	float getRight();
	float getTop();
	float getBottom();
	float getHeight();
	float getWidth();

protected:
	ofRectangle* rect;
	bool isMouseOver;
	bool isMouseDown;
};

