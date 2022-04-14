#include "uiComponent.h"
#include "ofRectangle.h"
#include "ofFbo.h"
#include "utils/utils.h"
#include "ofEvents.h"
#include "ofMath.h"
#include <graphics/ofGraphics.h>
#include "utils/cursor.h"

uiComponent::uiComponent(float width, float height) : rect(new ofRectangle(0, 0, width, height)), isMouseOver(false), isMouseDown(false)
{
}

uiComponent::~uiComponent()
{
	delete rect;
}

void uiComponent::update(int x, int y, int originX, int originY)
{
	rect->x = x;
	rect->y = y;

	if (utils::isDropdownOpened)
	{
		return;
	}

	int mX = ofGetMouseX() - originX;
	int mY = ofGetMouseY() - originY;

	isMouseOver = rect->inside(mX, mY);
	isMouseDown = isMouseOver && utils::mousePressed;

	if (isMouseOver && utils::mouseReleased && onClick != 0)
	{
		onClick();
	}
}

void uiComponent::setWidth(float w)
{
	rect->width = w;
}

void uiComponent::setHeight(float h)
{
	rect->height = h;
}

float uiComponent::getX()
{
	return rect->x;
}

float uiComponent::getY()
{
	return rect->y;
}

float uiComponent::getLeft()
{
	return rect->getLeft();
}

float uiComponent::getRight()
{
	return rect->getRight();
}

float uiComponent::getTop()
{
	return rect->getTop();
}

float uiComponent::getBottom()
{
	return rect->getBottom();
}

float uiComponent::getHeight()
{
	return rect->getHeight();
}

float uiComponent::getWidth()
{
	return rect->getWidth();
}
