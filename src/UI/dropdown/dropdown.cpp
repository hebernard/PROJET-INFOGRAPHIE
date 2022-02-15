#include "dropdown.h"
#include "../label.h"
#include "../menuBar.h"
#include "dropdownButton.h"
#include "mainTheme.h"

dropdown::dropdown(int i, std::string text, menuBar& menu) : ofxDatGuiToggle("dropdown"), index(i), opened(false), m_text(text), downArrow(), panel(), m_menu(menu)
{
	downArrow.load("images/icons/down_arrow.png");
	downArrow.resize(20, 20);
	setTheme(new dropdownTheme());

	onToggleEvent(this, &dropdown::onToggled);
	textSize = label::getSize(text, 13);
}

void dropdown::onToggled(ofxDatGuiToggleEvent e)
{
	m_menu.notifyDropdownClicked(index);
}

void dropdown::setTheme(const ofxDatGuiTheme* theme)
{
	setComponentStyle(theme);
	int width = textSize.x + 70;
	ofxDatGuiComponent::setWidth(width, theme->layout.labelWidth);
}

void dropdown::draw()
{
	ofPushStyle();
	ofFill();

	if (mMouseOver || getChecked())
	{
		ofSetColor(mainTheme::toolBarButtonHoverColor());
		ofDrawRectRounded(x, y, getWidth(), getHeight(), 6);

		if (downArrow.isAllocated())
		{
			ofSetColor(mainTheme::fontColor());
			downArrow.draw(x + textSize.x + 20, y + getHeight() / 2 - 10);
		}

		drawText(x + 15, y + textSize.y + 14, m_text, 13);

		if (getChecked())
		{
			panel.draw();
		}
	}
	else 
	{
		drawText(x + 15, y + textSize.y + 14, m_text, 13, mainTheme::fontColorAlpha());
	}

	ofPopStyle();
}

void dropdown::update()
{
	ofxDatGuiComponent::update();
	if (getChecked())
	{
		panel.update(x - 25, y + 50);
		if (ofGetMouseX() < panel.rect.getX() || ofGetMouseX() > panel.rect.getX() + panel.rect.getWidth() ||
			ofGetMouseY() < y || ofGetMouseY() > panel.rect.getY() + panel.rect.getHeight())
		{
			m_menu.notifyDropdownClicked(-1);
		}
	}
}

void dropdown::addButton(dropdownButton* button)
{
	panel.addButton(button);
}
