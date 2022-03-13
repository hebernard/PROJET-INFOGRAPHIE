#pragma once
#include "ofMain.h"
#include "inputProperty.h"

enum class ColorMode { RGB, HEX, HSB };

class colorPicker
{
public:
	bool show = false;

	colorPicker(ofColor& ref);
	~colorPicker();

	void draw(int x, int y, int width);

private:
	ofColor& m_ref;
	ofRectangle pickerRect, gradientRect, rainbowRect;
	ofImage rainbow;
	float rainbowLine;
	glm::vec2 gradientPos;
	ofRectangle rgbRect, hexRect, hsbRect;
	ColorMode currentMode = ColorMode::RGB;

	inputProperty* rInput, * gInput, * bInput;
	float R = 255, G = 255, B = 255;

	inputProperty* hInput, * sInput, * brInput;
	float H = 255, S = 255, Br = 255;

	//string hex;

	unsigned char p[3];

	vector<ofVec2f> gPoints;
	vector<ofFloatColor> gColors;
	ofVbo vbo;
	ofColor gColor;

	void updateGradient();
};

