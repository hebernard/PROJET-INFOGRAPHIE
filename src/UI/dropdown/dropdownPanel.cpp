#include "dropdownPanel.h"
#include "ofGraphics.h"
#include "dropdownButton.h"
#include "mainTheme.h"

dropdownPanel::dropdownPanel() : rect(), buttons()
{
	rect.width = 250;
}

void dropdownPanel::update(int x, int y)
{
	rect.setPosition(x, y);

	if (buttons.size() > 0)
	{
		int height = buttons.front()->getHeight();
		for (size_t i = 0; i < buttons.size(); i++)
		{
			buttons.at(i)->update(rect.x, 10 + rect.y + (i * height));
		}
	}
}

void dropdownPanel::draw()
{
	ofPushStyle();
	ofFill();

	ofSetColor(mainTheme::panelBorderColor());
	ofDrawRectRounded(rect.x - 2, rect.y - 2, rect.width + 4, rect.height + 4, 8);

	ofSetColor(mainTheme::panelColor());
	ofDrawRectRounded(rect, 6);

	for (size_t i = 0; i < buttons.size(); i++)
	{
		buttons.at(i)->draw();
	}

	ofPopStyle();
}

void dropdownPanel::addButton(dropdownButton* button)
{
	buttons.push_back(button);

	int height = buttons.front()->getHeight();
	rect.height = 20 + height * buttons.size();
}
