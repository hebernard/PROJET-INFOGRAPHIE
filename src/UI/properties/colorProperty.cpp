#include "colorProperty.h"
#include "label.h"
#include "panel.h"
#include "utils.h"

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

	ofPushStyle();
	bool mouseInside = colorRect.inside(mouseX, mouseY);
	ofSetColor(m_ref);
	ofDrawRectRounded(colorRect, 20);

	picker.draw(colorRect.x, colorRect.y);

	if (utils::mousePressed)
	{
		if (mouseInside)
		{
			picker.show = !picker.show;
		}
	}

	ofPopStyle();
}

int colorProperty::getHeight()
{
	return colorRect.getHeight();
}
