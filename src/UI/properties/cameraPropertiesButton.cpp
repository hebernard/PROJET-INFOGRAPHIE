#include "cameraPropertiesButton.h"
#include "label.h"
#include "utils.h"

cameraPropertiesButton::cameraPropertiesButton(std::string text, std::string iconPath) : m_text(text)
{
	icon.load(iconPath);
	icon.resize(20, 20);
}

void cameraPropertiesButton::draw(int x, int y, int width)
{
	rect.width = width;
	rect.height = rect.width / 1.15;
	rect.x = x;
	rect.y = y;

	ofPushStyle();
	bool inside = rect.inside(ofGetMouseX(), ofGetMouseY());
	if (inside && utils::mouseReleased)
	{
		isSelected = !isSelected;
	}

	if (isSelected)
	{
		ofSetColor(mainTheme::fontColor());
		ofDrawRectRounded(rect.x - 1, rect.y - 1, rect.width + 2, rect.height + 2, 14);
	}

	ofSetColor(inside ? mainTheme::panelButtonHoverColor() : mainTheme::toolBarButtonHoverColor());
	ofDrawRectRounded(rect, 14);

	ofPopStyle();

	drawText(rect.x + 15, rect.y + rect.height / 2 + 10, m_text, 10);

	if (icon.isAllocated())
	{
		icon.draw(rect.x + 15, rect.y + 15);
	}
}

int cameraPropertiesButton::getY()
{
	return rect.y;
}
