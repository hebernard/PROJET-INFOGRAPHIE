#include "sliderBase.h"
#include "ui/label.h"
#include "utils/utils.h"

sliderBase::sliderBase(std::string label, bool manualUpdate) : m_label(label), manualUpdate(manualUpdate)
{
	textSize = label::getSize(label, FONT_SIZE);
	rect.height = 4;
}

sliderBase::~sliderBase()
{
}

void sliderBase::draw(int x, int y, int width)
{
	updateThumb();

	rect.x = x + 4;
	rect.width = width - 8;

	// Main label
	float offsetY = y + textSize.y + 5;
	drawText(x, offsetY, m_label, FONT_SIZE);
	offsetY += 35;

	// Slider background
	rect.y = offsetY;
	ofPushStyle();
	ofSetColor(mainTheme::toolBarButtonHoverColor());
	ofDrawRectRounded(rect, 8);

	// Slider fill
	ofSetColor(mainTheme::color1());
	ofDrawRectRounded(rect.x, rect.y, rect.width * thumbPos, rect.height, 8);

	// Value text
	auto valueTextSize = label::getSize(value, 9);
	drawText(rect.x + (rect.width * thumbPos - valueTextSize.x / 2), rect.y - thumbRadius - 5, value, 9);

	// Thumb
	ofDrawCircle(rect.x + (rect.width * thumbPos), rect.y, thumbRadius);
	ofPopStyle();
	offsetY += thumbRadius + 15;

	// Min-max texts
	drawText(x, offsetY, minS, 9);
	auto maxSSize = label::getSize(maxS, 9);
	drawText(x + width - maxSSize.x, offsetY, maxS, 9);
}

void sliderBase::onValueUpdate()
{
}

float sliderBase::getHeight()
{
	return 80;
}

void sliderBase::updateThumb()
{
	if (utils::mousePressed)
	{
		int x = ofGetMouseX();
		int y = ofGetMouseY();
		if (ofRectangle(rect.x, rect.y - thumbRadius, rect.width, thumbRadius*2).inside(x, y))
		{
			dragStarted = true;
		}
	}
	else if (utils::mouseReleased)
	{
		dragStarted = false;
	}

	if (dragStarted)
	{
		int x = ofGetMouseX();
		thumbPos = ofMap(x, rect.x, rect.x + rect.width, 0, 1, true);
		onValueUpdate();
	}
}
