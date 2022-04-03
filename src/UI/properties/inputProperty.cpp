#include "inputProperty.h"
#include "panel.h"
#include "label.h"
#include "utils.h"

inputProperty::inputProperty(std::string label, float& ref) : m_label(label), m_ref(ref)
{
	labelSize = label::getSize(label, 11);
	rect.height = 20;
	value = ofToString(ref);
	valueSize = label::getSize(value, 10);
}

void inputProperty::draw(int x, int y, int width, int textOffset)
{
	rect.x = x + labelSize.x + textOffset;
	rect.y = y;
	rect.width = width - labelSize.x - 30;
	hovered = rect.inside(ofGetMouseX(), ofGetMouseY());

	drawText(x, y + labelSize.y + 5, m_label, 11);

	drawInputPanel(rect, hovered, focused);

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

		if (utils::keyPressed != 0)
		{
			int key = utils::keyPressed;
			if (key == '0' || key == '1' || key == '2' || key == '3' ||
				key == '4' || key == '5' || key == '6' || key == '7' ||
				key == '8' || key == '9' || key == '.')
			{
				if (value.size() < maxCharacters)
				{
					value += key;
				}
			}
			else if (key == OF_KEY_BACKSPACE)
			{
				value = value.substr(0, value.size() - 1);
			}
			else if (key == OF_KEY_RETURN)
			{
				focused = false;
				m_ref = getValue();
			}

			valueSize = label::getSize(value, 10);
			blinkTimer = 0;
		}
	}

	if (utils::mousePressed)
	{
		focused = hovered;
		if (!focused)
		{
			m_ref = getValue();
		}
	}
}

int inputProperty::getHeight()
{
	return rect.height;
}

void inputProperty::forceUpdateValue(float maxValue)
{
	value = ofToString(CLAMP(m_ref, 0, maxValue)).substr(0, maxCharacters);
	valueSize = label::getSize(value, 10);
}

float inputProperty::getValue()
{
	if (value.size() <= 0 || value[0] == '.')
	{
		value = "0";
		valueSize = label::getSize(value, 10);
	}

	return stof(value);
}
