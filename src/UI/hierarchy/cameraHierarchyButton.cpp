#include "cameraHierarchyButton.h"
#include "hierarchyButton.h"
#include "UI/label.h"
#include "hierarchySmallButton.h"

cameraHierarchyButton::cameraHierarchyButton(std::string iconPath, std::string text) :
	ofxDatGuiButton("cameraHierarchyButton"),
	m_text(text),
	icon(),
	propertiesButton(new hierarchySmallButton("images/icons/properties.png"))
{
	icon.load(iconPath);
	icon.resize(24, 24);
	setTheme(new hierarchyButtonTheme());

	textSize = label::getSize(text, 11, mainTheme::fontRegularPath);

	propertiesButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{

	});
}

void cameraHierarchyButton::setTheme(const ofxDatGuiTheme* theme)
{
	setComponentStyle(theme);
	ofxDatGuiComponent::setWidth(theme->layout.width, theme->layout.labelWidth);
}

void cameraHierarchyButton::draw()
{
	ofPushStyle();
	ofFill();

	ofSetColor(mainTheme::panelColor());
	ofDrawRectangle(x - 2, y, getWidth() + 4, getHeight());

	if (icon.isAllocated())
	{
		ofSetColor(ofColor::white);
		icon.draw(x + 30, y + getHeight() / 2 - icon.getHeight() / 2);
	}

	drawText(x + icon.getWidth() + 25 * 2, y + getHeight() / 2 + textSize.y / 2, m_text, 11, mainTheme::fontColor(), mainTheme::fontRegularPath);

	propertiesButton->draw();
	ofPopStyle();
}

void cameraHierarchyButton::update(int x, int y)
{
	ofxDatGuiComponent::update();
	setPosition(x, y);

	int posX = x + getWidth() - propertiesButton->getWidth() - 30;
	int posY = y + getHeight() / 2 - propertiesButton->getHeight() / 2;
	propertiesButton->update(posX, posY);
}

std::string cameraHierarchyButton::getLabel()
{
	return m_text;
}
