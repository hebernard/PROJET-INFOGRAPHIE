#include "centeredSlider.h"
#include "label.h"
#include "panel.h"
#include "object.h"

centeredSlider::centeredSlider(std::string text) : m_text(text)
{
	xyzRect.width = 80;
	xyzRect.height = 20;
}

void centeredSlider::draw(int x, int y, glm::vec3 xyz)
{
	int firstX = 100;
	int circleRadius = 14;
	xyzRect.x = x + firstX;
	xyzRect.y = y - circleRadius;

	drawText(x, y, m_text, 12);

	ofPushStyle();
	ofSetColor(mainTheme::toolBarButtonHoverColor());
	ofDrawRectRounded(xyzRect.x, xyzRect.y, 80, 20, 8);
	ofDrawRectRounded(x, y + 35, 240, 4, 8);

	int posX = xyzRect.x + 11;
	if (current == 0)
	{
		ofSetColor(ofColor::red);
	}
	else if (current == 1)
	{
		ofSetColor(ofColor::green);
	}
	else
	{
		ofSetColor(ofColor::blue);
	}
	ofDrawCircle(posX + (current * 25) + 5, y - 4, circleRadius);
	ofDrawCircle(thumbX, y + 35, circleRadius - 4);
	ofDrawRectRounded(1110, y + 35, thumbX - 1110, 4, 8);

	drawText(posX, y, "x", 11);
	posX += 25;
	drawText(posX, y, "y", 11);
	posX += 25;
	drawText(posX, y, "z", 11);

	posX += 30;
	drawPanel(posX, xyzRect.y, 50, 20);

	std::string val = getDrawedValue(xyz);
	int s = label::getSize(val, 10).x;
	posX += 25 - s / 2;
	drawText(posX, y, getDrawedValue(xyz), 10);

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

		value = (float) 2 * (thumbX - minX) / (maxX - minX) - 1;
	}
}

void centeredSlider::mouseReleased(ofMouseEventArgs& args)
{
	if (args.x >= xyzRect.x &&
		args.x <= xyzRect.x + 25 &&
		args.y >= xyzRect.y &&
		args.y <= xyzRect.y + xyzRect.height)
	{
		current = 0;
		axis = glm::vec3(1, 0, 0);
	}

	if (args.x >= xyzRect.x + 26 &&
		args.x <= xyzRect.x + 50 &&
		args.y >= xyzRect.y &&
		args.y <= xyzRect.y + xyzRect.height)
	{
		current = 1;
		axis = glm::vec3(0, 1, 0);
	}

	if (args.x >= xyzRect.x + 51 &&
		args.x <= xyzRect.x + xyzRect.width &&
		args.y >= xyzRect.y &&
		args.y <= xyzRect.y + xyzRect.height)
	{
		current = 2;
		axis = glm::vec3(0, 0, 1);
	}

	thumbX = 1110;
	value = 0;
	dragStarted = false;
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