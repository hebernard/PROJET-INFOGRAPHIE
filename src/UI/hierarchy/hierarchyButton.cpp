#include "hierarchyButton.h"
#include "UI/label.h"
#include "components/object.h"
#include "scene.h"

hierarchyButton::hierarchyButton(object& obj, std::string iconPath, std::string text) : ofxDatGuiButton("hierarchyButton"), m_label(new label(text, "fonts/inter_regular.ttf", 11, t.ofFontColor)), icon(), m_obj(obj)
{
	icon.load(iconPath);
	icon.resize(24, 24);
	setTheme(new hierarchyButtonTheme());

	onButtonEvent(this, &hierarchyButton::onClick);
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
		ofSetColor(t.ofFontColor);
		icon.draw(x + 30, y + getHeight() / 2 - icon.getHeight() / 2);
	}

	m_label->draw();
	ofPopStyle();
}

void hierarchyButton::update(int x, int y)
{
	ofxDatGuiComponent::update();
	setPosition(x, y);
	m_label->setPosition(x + icon.getWidth() + 25 * 2, y + getHeight() / 2 + m_label->getHeight() / 2);
}
