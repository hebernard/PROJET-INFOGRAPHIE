#include "colorProperty.h"
#include "ui/label.h"
#include "ui/panel.h"
#include "utils/utils.h"

colorProperty::colorProperty(std::string label, ofColor& ref) : m_label(label), m_ref(ref), picker(ref)
{
	textSize = label::getSize(label, 12);
	colorRect.height = 20;
}

void colorProperty::draw(int x, int y, int width)
{
	int mouseX = ofGetMouseX();
	int mouseY = ofGetMouseY();

	colorRect.x = x + textSize.x + 30;
	colorRect.y = y;
	colorRect.width = width - textSize.x - 30;

	drawText(x, y + textSize.y, m_label, 11);

	picker.draw(x, colorRect.y);

	bool mouseInside = colorRect.inside(mouseX, mouseY);
	if (interactable && utils::mousePressed)
	{
		if (mouseInside)
		{
			picker.show = !picker.show;
		}
	}

	ofPushStyle();
	ofSetColor(m_ref);
	ofDrawRectRounded(colorRect, 20);
	ofPopStyle();
}

int colorProperty::getHeight()
{
	return colorRect.getHeight();
}

void colorProperty::forceUpdate()
{
	picker.forceUpdate();
}
