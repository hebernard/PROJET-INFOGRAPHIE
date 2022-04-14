#include "groupProperty.h"
#include "label.h"
#include "utils/utils.h"

groupProperty::groupProperty(std::string label) : uiComponent(0, 34), label(label), arrowIcon(), toggled(false)
{
	toggle(false);
	textSize = label::getSize(label, 12);
}

void groupProperty::draw()
{
	ofPushStyle();
	bool active = isMouseOver || isToggled();

	if (active)
	{
		ofSetColor(isMouseOver && ofGetMousePressed() ? mainTheme::panelButtonHoverColor() : mainTheme::toolBarButtonHoverColor());
		ofDrawRectRounded(*rect, 8);
	}

	ofSetColor(active ? ofColor::white : ofColor(255, 100));
	arrowIcon.draw(getX() + 5, getY() + getHeight() / 2 - arrowIcon.getHeight() / 2);
	ofPopStyle();

	ofColor fontColor = active ? mainTheme::fontColor() : mainTheme::fontColorAlpha();
	drawTextCentered(getX() + arrowIcon.getWidth() + 15, getY(), getHeight(), label, 12, fontColor);

	if (isMouseOver && utils::mouseReleased)
	{
		toggle(!toggled);
	}

	if (isToggled() && drawOnToggled != 0)
	{
		drawOnToggled(getX(), getBottom() + 14);
	}
}

void groupProperty::toggle(bool active)
{
	toggled = active;

	arrowIcon.load(toggled ? "images/icons/down.png" : "images/icons/right.png");
	arrowIcon.resize(22, 22);
}

bool groupProperty::isToggled()
{
	return toggled;
}

void groupProperty::setFullHeight(float h)
{
	fullHeight = h;
}

float groupProperty::getRealHeight()
{
	return isToggled() ? getHeight() + fullHeight : getHeight();
}
