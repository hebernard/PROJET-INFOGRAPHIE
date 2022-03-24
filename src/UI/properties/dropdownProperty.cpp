#include "dropdownProperty.h"
#include "utils.h"
#include "panel.h"

dropdownProperty::dropdownProperty(string label) : m_label(label)
{
	labelSize = label::getSize(label, 11);
	rect.height = 20;
}

void dropdownProperty::setElements(vector<string> el)
{
	int offset = 10;
	int elementHeight = 20;
	elements.clear();

	for (auto& e : el)
	{
		elements.push_back(element(e, elementHeight));
	}

	dropdownRect.height = (elements.size() * elementHeight) + offset * 2;

	current = elements.front().label;
}

void dropdownProperty::draw(int x, int y, int w)
{
	bool hovered = rect.inside(ofGetMouseX(), ofGetMouseY());
	if (hovered && utils::mousePressed)
	{
		focused = !focused;
	}
	
	rect.x = x + labelSize.x + 30;
	rect.y = y;
	rect.width = w - labelSize.x - 30;

	dropdownRect.x = rect.x;
	dropdownRect.y = y + rect.height + 5;
	dropdownRect.width = rect.width;

	drawText(x, y + labelSize.y, m_label, 11);

	drawInputPanel(rect, hovered, focused);

	if (focused)
	{
		ofSetColor(mainTheme::toolBarButtonHoverColor());
		utils::drawOnTopQueue.push([this]() -> void
		{
			ofDrawRectRounded(dropdownRect, 8);
			int y = dropdownRect.y + 10;
			for (int i = 0; i < elements.size(); i++)
			{
				y += elements[i].height * i;
				elements[i].draw(dropdownRect.x, y, dropdownRect.width);

				if (elements[i].hovered && utils::mousePressed)
				{
					current = elements[i].label;
					elements[i].selected = true;
					for (int j = 0; j < elements.size(); j++)
					{
						if (i != j)
						{
							elements[j].selected = false;
						}
					}

					focused = false;
				}
			}
		});
	}

	auto size = label::getSize(current, 11);
	drawText(rect.x + rect.width / 2 - size.x / 2, rect.y + size.y + 5, current, 11);
}
