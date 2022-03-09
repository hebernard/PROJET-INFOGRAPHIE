#include "centeredSlider.h"
#include "label.h"
#include "panel.h"
#include "object.h"
#include "hierarchySmallButton.h"
#include "cursor.h"

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

void centeredSlider::mouseDragged(ofMouseEventArgs& args)
{
	if (args.y >= xyzRect.y + 49 - thumbRadius && args.y <= xyzRect.y + 49 + thumbRadius &&
		args.x >= xyzRect.x - 100 && args.x <= xyzRect.x - 100 + 240)
	{
		dragStarted = true;
	}

	if (dragStarted)
	{
		thumbX = args.x;
		if (thumbX <= minX)
		{
			thumbX = minX;
		}
		if (thumbX >= maxX)
		{
			thumbX = maxX;
		}

		// Normalize between -1 and 1
		value = (float) 2 * (thumbX - minX) / (maxX - minX) - 1;
	}
}

void centeredSlider::mouseReleased(ofMouseEventArgs& args)
{
	if (isLocked)
	{
		value = 0;
		dragStarted = false;
		return;
	}

	if (args.x >= xyzRect.x &&
		args.x <= xyzRect.x + 25 &&
		args.y >= xyzRect.y &&
		args.y <= xyzRect.y + xyzRect.height)
	{
		current = 0;
		axisColor = ofColor::red;
		axis = glm::vec3(1, 0, 0);
	}

	if (args.x >= xyzRect.x + 26 &&
		args.x <= xyzRect.x + 50 &&
		args.y >= xyzRect.y &&
		args.y <= xyzRect.y + xyzRect.height)
	{
		current = 1;
		axisColor = ofColor::green;
		axis = glm::vec3(0, 1, 0);
	}

	if (args.x >= xyzRect.x + 51 &&
		args.x <= xyzRect.x + xyzRect.width &&
		args.y >= xyzRect.y &&
		args.y <= xyzRect.y + xyzRect.height)
	{
		current = 2;
		axisColor = ofColor::blue;
		axis = glm::vec3(0, 0, 1);
	}

	value = 0;
	dragStarted = false;
}

centeredSlider::~centeredSlider()
{
	delete resetButton;
	delete lockedButton;
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
	minX = x;
	maxX = x + width;
	int center = minX + width / 2;

	ofSetColor(mainTheme::toolBarButtonHoverColor());
	ofDrawRectRounded(minX, y, width, 4, 8);

	if (!dragStarted)
	{
		thumbX = center;
	}

	ofSetColor(!isLocked ? axisColor : mainTheme::color3());
	ofDrawRectRounded(center, y, thumbX - center, 4, 8);
	ofDrawCircle(thumbX, y, thumbRadius);
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