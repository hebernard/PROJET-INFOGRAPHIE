#include "hierarchyButton.h"
#include "UI/label.h"
#include "components/object.h"
#include "scene.h"
#include "hierarchySmallButton.h"

hierarchyButton::hierarchyButton(object& obj, std::string iconPath, std::string text) : 
	ofxDatGuiButton("hierarchyButton"), 
	m_label(new label(text, t.fontRegularPath, 11, t.fontColor)), 
	icon(), m_obj(obj), 
	deleteButton(new hierarchySmallButton("images/icons/delete.png")),
	propertiesButton(new hierarchySmallButton("images/icons/properties.png")),
	visibleButton(new hierarchySmallButton("images/icons/eye.png"))
{
	icon.load(iconPath);
	icon.resize(24, 24);
	setTheme(new hierarchyButtonTheme());

	onButtonEvent(this, &hierarchyButton::onClick);

	deleteButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		obj.markedForDeletion = true;
		scene& s = s.getInstance();
		s.deleteObjects();
	});

	propertiesButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		obj.propertiesOpened = true;
	});

	visibleButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		obj.isVisible = !obj.isVisible;
		visibleButton->changeIcon(obj.isVisible ? "images/icons/eye.png" : "images/icons/no_eye.png");
	});
}

void hierarchyButton::setTheme(const ofxDatGuiTheme* theme)
{
	setComponentStyle(theme);
	ofxDatGuiComponent::setWidth(theme->layout.width, theme->layout.labelWidth);
}

void hierarchyButton::onClick(ofxDatGuiButtonEvent e)
{
	scene& s = s.getInstance();
	s.focusObject(m_obj);
}

void hierarchyButton::draw()
{
	ofPushStyle();
	ofFill();

	if (mMouseOver || m_obj.isSelected)
	{
		ofSetColor(t.panelButtonHoverColor);
		ofDrawRectangle(x - 2, y, getWidth() + 4, getHeight());
	}

	if (icon.isAllocated())
	{
		ofSetColor(ofColor::white);
		icon.draw(x + 30, y + getHeight() / 2 - icon.getHeight() / 2);
	}

	m_label->setColor(t.fontColor);
	m_label->draw();

	deleteButton->draw();
	propertiesButton->draw();
	visibleButton->draw();
	ofPopStyle();
}

void hierarchyButton::update(int x, int y)
{
	ofxDatGuiComponent::update();
	setPosition(x, y);
	m_label->setPosition(x + icon.getWidth() + 25 * 2, y + getHeight() / 2 + m_label->getHeight() / 2);

	int posX = x + getWidth() - deleteButton->getWidth() - 30;
	int posY = y + getHeight() / 2 - deleteButton->getHeight() / 2;
	deleteButton->update(posX, posY);

	posX -= deleteButton->getWidth();
	propertiesButton->update(posX, posY);

	posX -= propertiesButton->getWidth();
	visibleButton->update(posX, posY);
}

std::string hierarchyButton::getLabel()
{
	return m_label->getLabel();
}
