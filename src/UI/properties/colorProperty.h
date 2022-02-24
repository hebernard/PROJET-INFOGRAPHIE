#pragma once
#include "ofMain.h"

class colorProperty
{
public:
	colorProperty(std::string label, ofColor& ref);

	void draw(int x, int y, int width);

	void updateGradient(int mouseX, int mouseY);

	int getHeight();

private:
	ofColor& m_ref;
	std::string m_label;
	glm::vec2 textSize;

	ofRectangle colorRect, pickerRect, gradientRect, rainbowRect;
	ofImage rainbow;
	float rainbowLine;
	glm::vec2 gradientPos;
	bool showPicker = false;

	vector<ofVec2f> gPoints;
	vector<ofFloatColor> gColors;
	ofVbo vbo;
	ofColor gColor;

	void drawPicker(int x, int y, int width);
};

