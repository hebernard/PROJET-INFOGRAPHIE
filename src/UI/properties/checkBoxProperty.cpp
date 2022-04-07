#include "checkBoxProperty.h"
#include "ui/label.h"
#include "utils/utils.h"

checkBoxProperty::checkBoxProperty(std::string label, bool& ref) : m_label(label), m_ref(ref)
{
	rect.height = 50;
	labelSize = label::getSize(label, 11);

	previousState = ref;
	setIcon();

	checkBox.width = icon.getWidth();
	checkBox.height = icon.getHeight();
}

void checkBoxProperty::draw(int x, int y, int width)
{
	if (checkBox.inside(ofGetMouseX(), ofGetMouseY()) && utils::mouseReleased)
	{
		m_ref = !m_ref;
	}

	rect.x = x;
	rect.y = y;
	rect.width = width;

	checkBox.x = x + width - checkBox.width;
	checkBox.y = y;

	drawText(x, y + labelSize.y, m_label, 11);

	if (icon.isAllocated())
	{
		icon.draw(checkBox.x, checkBox.y);
	}

	if (previousState != m_ref)
	{
		setIcon();
		previousState = m_ref;
	}
}

int checkBoxProperty::getHeight()
{
	return checkBox.height;
}

void checkBoxProperty::setIcon()
{
	icon.load(m_ref ? "images/icons/checked.png" : "images/icons/unchecked.png");
	icon.resize(40, 25);
}
