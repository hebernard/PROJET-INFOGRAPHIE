#include "menuBarButton.h"
#include "ui/label.h"
#include "ui/mainTheme.h"
#include "utils/cursor.h"

menuBarButton::menuBarButton(std::string text, int textOffset) : uiComponent(80, 38), m_text(text), textOff(textOffset)
{
	textSize = label::getSize(text, 11);
}

void menuBarButton::draw()
{
	if (isMouseDown)
	{
		cursor::setHandCursor();
		ofSetColor(mainTheme::color3());
	}
	else if (isMouseOver)
	{
		cursor::setHandCursor();
		ofSetColor(mainTheme::color2());
	}
	else
	{
		ofSetColor(mainTheme::color1());
	}
	ofDrawRectRounded(*rect, 6);

	drawText(getX() + getWidth() / 2 - textSize.x / 2, getY() + textSize.y + textOff, m_text, 11);
}

void menuBarButton::setLabel(std::string text)
{
	m_text = text;
	textSize = label::getSize(m_text, 11);
}
