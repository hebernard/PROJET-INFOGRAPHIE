#pragma once
#include "ofMain.h"
#include "floatInputProperty.h"

class colorProperty
{
public:
	colorProperty(std::string label, ofColor& ref);
	~colorProperty();

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
	ofRectangle rgbRect, hexRect, hsvRect;
	ColorMode currentMode = ColorMode::RGB;

	floatInputProperty* rInput, *gInput, *bInput;
	float R = 255, G = 255, B = 255;

	string hex;

	unsigned char p[3];

	vector<ofVec2f> gPoints;
	vector<ofFloatColor> gColors;
	ofVbo vbo;
	ofColor gColor;

	void drawPicker(int x, int y, int width);
};

enum ColorMode { RGB = 0, HEX = 1, HSV = 2 };