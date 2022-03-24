#include "cameraPropertiesButton.h"
#include "label.h"
#include "panel.h"

cameraPropertiesButton::cameraPropertiesButton(std::string text, std::string iconPath, bool isDefault, int type) : m_text(text), m_buttonType(type)
{
	if (type == 0) {
		icon.load(iconPath);
		icon.resize(20, 20);
	}
	if (type == 1) {
		m_isDefault = isDefault;
	}
}

void cameraPropertiesButton::draw(int x, int y, int width)
{
	rect.width = width;
	rect.height = rect.width / 1.15;
	rect.x = x;
	rect.y = y;

	ofPushStyle();
	bool inside = rect.inside(ofGetMouseX(), ofGetMouseY());

	drawInputPanel(rect, inside, isSelected);

	drawText(rect.x + 15, rect.y + rect.height / 2 + 10, m_text, 10);

	switch (m_buttonType) {
		case 0:
			if (icon.isAllocated())
			{
				ofSetColor(255);
				icon.draw(rect.x + 15, rect.y + 15);
			}
			break;
		case 1:
			ofPushStyle();
			ofSetColor(m_isDefault ? mainTheme::fontColor() : mainTheme::sceneCustomBackgroundColor);
			ofDrawCircle(rect.x + 20, rect.y + 20, 10);
			ofPopStyle();
			break;
	}
	ofPopStyle();
}

int cameraPropertiesButton::getY()
{
	return rect.y;
}

void cameraPropertiesButton::setSelected()
{
	isSelected = true;
}

void cameraPropertiesButton::setUnselected()
{
	isSelected = false;
}

bool cameraPropertiesButton::isInside()
{
	return rect.inside(ofGetMouseX(), ofGetMouseY());
}

ofRectangle cameraPropertiesButton::getArea()
{
	return rect;
}


