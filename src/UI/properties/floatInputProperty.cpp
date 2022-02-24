#include "floatInputProperty.h"
#include "panel.h"
#include "label.h"

floatInputProperty::floatInputProperty(std::string label, float& ref) : m_label(label), m_ref(ref)
{
	labelSize = label::getSize(label, 11);
	rect.height = 20;
	value = ofToString(ref);
	valueSize = label::getSize(value, 10);

	ofRegisterKeyEvents(this);
}

void floatInputProperty::draw(int x, int y, int width)
{
	rect.x = x + labelSize.x + 30;
	rect.y = y;
	rect.width = width - labelSize.x - 30;
	hovered = rect.inside(ofGetMouseX(), ofGetMouseY());

	drawText(x, y + labelSize.y, m_label, 11);

	if (hovered || focused)
	{
		drawPanel(rect, mainTheme::panelButtonHoverColor());
	}
	else
	{
		drawPanel(rect);
	}

	int offsetX = 12;
	int offsetY = 15;
	drawText(rect.x + offsetX, y + offsetY, value, 10);

	if (focused)
	{
		blinkTimer += ofGetLastFrameTime();
		if (blinkTimer <= blinkTime)
		{
			ofPushStyle();
			ofSetColor(mainTheme::fontColor());
			int padding = 2;
			ofDrawLine(rect.x + offsetX + valueSize.x, y + padding, rect.x + offsetX + valueSize.x, y + rect.height - padding);
			ofPopStyle();
		}
		else if (blinkTimer >= blinkTime * 2)
		{
			blinkTimer = 0;
		}
	}

	if (ofGetMousePressed())
	{
		focused = hovered;
		if (!focused)
		{
			m_ref = getValue();
		}
	}
}

int floatInputProperty::getHeight()
{
	return rect.height;
}

void floatInputProperty::keyPressed(ofKeyEventArgs& args)
{
	if (focused)
	{
		if (args.key == '0' || args.key == '1' || args.key == '2' || args.key == '3' ||
			args.key == '4' || args.key == '5' || args.key == '6' || args.key == '7' ||
			args.key == '8' || args.key == '9' || args.key == '.')
		{
			if (value.size() < maxCharacters)
			{
				value += args.key;
			}
		}
		else if (args.key == OF_KEY_BACKSPACE)
		{
			value = value.substr(0, value.size() - 1);
		}
		else if (args.key == OF_KEY_RETURN)
		{
			focused = false;
			m_ref = getValue();
		}

		valueSize = label::getSize(value, 10);
		blinkTimer = 0;
	}
}

void floatInputProperty::keyReleased(ofKeyEventArgs& args) {}

float floatInputProperty::getValue()
{
	if (value.size() <= 0)
	{
		value = "0";
		valueSize = label::getSize(value, 10);
	}

	return stof(value);
}
