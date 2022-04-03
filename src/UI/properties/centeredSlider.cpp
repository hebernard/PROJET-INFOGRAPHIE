#include "centeredSlider.h"
#include "label.h"
#include "panel.h"
#include "object.h"
#include "hierarchySmallButton.h"
#include "cursor.h"
#include "utils.h"

centeredSlider::centeredSlider(std::string text, bool drawLockedButton) : 
	m_text(text),
	drawLocked(drawLockedButton),
	resetButton(new hierarchySmallButton("images/icons/reset.png")),
	lockedButton(new hierarchySmallButton("images/icons/unlock.png"))
{
	xyzRect.width = 78;
	xyzRect.height = 20;

	textSize = label::getSize(m_text, 12);
}

centeredSlider::~centeredSlider()
{
	delete resetButton;
	delete lockedButton;
}

void centeredSlider::update()
{
	int mouseX = ofGetMouseX();
	int mouseY = ofGetMouseY();

	if (utils::mousePressed)
	{
		if (ofRectangle(slider.x, slider.y - thumbRadius, slider.width, thumbRadius * 2).inside(mouseX, mouseY))
		{
			dragStarted = true;
		}
	}
	else if (utils::mouseReleased)
	{
		if (isLocked)
		{
			value = 0;
			dragStarted = false;
			return;
		}

		if (mouseX >= xyzRect.x &&
			mouseX <= xyzRect.x + 25 &&
			mouseY >= xyzRect.y &&
			mouseY <= xyzRect.y + xyzRect.height)
		{
			current = 0;
			axisColor = ofColor::red;
			axis = glm::vec3(1, 0, 0);
		}

		if (mouseX >= xyzRect.x + 26 &&
			mouseX <= xyzRect.x + 50 &&
			mouseY >= xyzRect.y &&
			mouseY <= xyzRect.y + xyzRect.height)
		{
			current = 1;
			axisColor = ofColor::green;
			axis = glm::vec3(0, 1, 0);
		}

		if (mouseX >= xyzRect.x + 51 &&
			mouseX <= xyzRect.x + xyzRect.width &&
			mouseY >= xyzRect.y &&
			mouseY <= xyzRect.y + xyzRect.height)
		{
			current = 2;
			axisColor = ofColor::blue;
			axis = glm::vec3(0, 0, 1);
		}

		value = 0;
		dragStarted = false;
	}

	if (dragStarted)
	{
		float min = slider.x;
		float max = slider.x + slider.width;

		thumbX = mouseX;
		if (thumbX <= min)
		{
			thumbX = min;
		}
		if (thumbX >= max)
		{
			thumbX = max;
		}

		// Normalize between -1 and 1
		value = (float)2 * (thumbX - min) / (max - min) - 1;

		if (onUpdate != 0)
		{
			onUpdate(axis, value);
		}
	}
}

void centeredSlider::draw(int x, int y, int width, glm::vec3 xyz)
{
	ofPushStyle();

	drawResetButton(x, y - 10);

	int labelX = x + resetButton->getWidth() + 5;
	if (drawLocked)
	{
		drawLockedButton(x + resetButton->getWidth(), y - 10);
		labelX += lockedButton->getWidth();
	}

	cursor::setDragged(dragStarted);
	if (dragStarted) {
		cursor::setHandGrabCursor();
	}

	// Main label
	drawText(labelX, y + textSize.y, m_text, 12);

	drawValue(x + width - 50, y, xyz);

	drawXYZRect(x + width - xyzRect.width - 60, y);

	drawSlider(x, y + 50, width);

	ofPopStyle();
}

void centeredSlider::setLocked(bool locked)
{
	isLocked = locked;
	lockedButton->changeIcon(locked ? "images/icons/lock.png" : "images/icons/unlock.png");
}

bool centeredSlider::getLocked()
{
	return isLocked;
}

int centeredSlider::getHeight()
{
	return 80;
}

void centeredSlider::drawXYZRect(int x, int y)
{
	xyzRect.x = x;
	xyzRect.y = y;

	// Background
	ofSetColor(mainTheme::toolBarButtonHoverColor());
	ofDrawRectRounded(x, y, xyzRect.width, xyzRect.height, 8);

	int offsetY = y + 15;
	if (isLocked)
	{
		auto size = label::getSize("xyz", 11);
		drawText(xyzRect.x + xyzRect.width / 2 - size.x / 2, offsetY, "xyz", 11);
	}
	else
	{
		int offsetX = x + 9;
		int offsetInBetween = xyzRect.width / 3;

		// Selection thumb
		ofSetColor(axisColor);
		ofDrawCircle(x + offsetInBetween / 2 + (current * offsetInBetween), offsetY - 4, 14);

		// Always draw the text last
		drawText(offsetX, offsetY, "x", 11);
		offsetX += offsetInBetween;
		drawText(offsetX, offsetY, "y", 11);
		offsetX += offsetInBetween;
		drawText(offsetX, offsetY, "z", 11);
	}
}

void centeredSlider::drawSlider(int x, int y, int width)
{
	slider.x = x;
	slider.y = y;
	slider.width = width;
	slider.height = 4;

	int center = slider.x + slider.width / 2;

	ofSetColor(mainTheme::toolBarButtonHoverColor());
	ofDrawRectRounded(slider, 8);

	if (!dragStarted)
	{
		thumbX = center;
	}

	ofSetColor(!isLocked ? axisColor : mainTheme::color3());
	ofDrawRectRounded(center, slider.y, thumbX - center, 4, 8);
	ofDrawCircle(thumbX, slider.y, thumbRadius);
}

void centeredSlider::drawResetButton(int x, int y)
{
	resetButton->update(x, y);
	resetButton->draw();
}

void centeredSlider::drawLockedButton(int x, int y)
{
	lockedButton->update(x, y);
	lockedButton->draw();
}

void centeredSlider::drawValue(int x, int y, glm::vec3 xyz)
{
	// Background
	drawPanel(x, y, 50, 20);

	std::string val = getDrawedValue(xyz);
	auto size = label::getSize(val, 10);
	int offsetX = x + 25 - size.x / 2;
	drawText(offsetX, y + size.y + 5, getDrawedValue(xyz), 10);
}

std::string centeredSlider::getDrawedValue(glm::vec3 xyz)
{
	std::string drawedValue;
	if (axis == glm::vec3(1, 0, 0))
	{
		drawedValue = std::to_string(xyz.x);
	}
	else if (axis == glm::vec3(0, 1, 0))
	{
		drawedValue = std::to_string(xyz.y);
	}
	else
	{
		drawedValue = std::to_string(xyz.z);
	}
	return drawedValue.substr(0, drawedValue.find(".") + 2);
}