#pragma once
#include "ofMain.h"

class inputProperty
{
public:
	int maxCharacters = 10;
	bool focused = false;
	inputProperty(std::string label, float& ref);

	void draw(int x, int y, int width, int textOffset = 30);
	int getHeight();

	void forceUpdateValue();
	void setMax(float max);
	void setMin(float min);

private:
	bool hovered = false;
	ofRectangle rect;

	std::string m_label;
	glm::vec2 labelSize;

	std::string value;
	glm::vec2 valueSize;
	float& m_ref;
	float max = 100000;
	float min = 0;

	// Lets make it blink cause we're that cool.
	float blinkTimer = 0;
	float blinkTime = 0.5f;

	float getValue();
	void setValue(float val);
};
