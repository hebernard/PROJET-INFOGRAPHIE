#include "dropdownPanel.h"
#include "ofGraphics.h"
#include "dropdownButton.h"
#include "panel.h"

dropdownPanel::dropdownPanel() : rect(), buttons()
{
	rect.width = 250;
}

dropdownPanel::~dropdownPanel()
{
	for (auto i : buttons) delete i;
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
	drawPanel(rect);

	for (size_t i = 0; i < buttons.size(); i++)
	{
		buttons.at(i)->draw();
	}
}

void dropdownPanel::addButton(dropdownButton* button)
{
	buttons.push_back(button);

	int height = buttons.front()->getHeight();
	rect.height = 20 + height * buttons.size();
}
