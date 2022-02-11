#include "label.h"

label::label(std::string text, std::string fontPath, int fontSize, ofColor c) : ofxDatGuiLabel(text), font(), color(c)
{
	mType = ofxDatGuiType::LABEL;
	font.load(fontPath, fontSize);
}

void label::draw()
{
	ofSetColor(t.ofFontColor);
	font.drawString(getLabel(), x, y);
}

int label::getWidth()
{
	return (int) font.stringWidth(getLabel());
}

int label::getHeight()
{
	return (int) font.stringHeight(getLabel());
}

void label::setColor(ofColor color)
{
	this->color = color;
}
