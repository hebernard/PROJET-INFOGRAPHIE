#pragma once
#include "ofMain.h"

class floatInputProperty
{
public:
	floatInputProperty(std::string label, float& ref);

	void draw(int x, int y, int width);
	int getHeight();

	void keyPressed(ofKeyEventArgs& args);
	void keyReleased(ofKeyEventArgs& args);

private:
	bool focused = false;
	bool hovered = false;
	ofRectangle rect;

	std::string m_label;
	glm::vec2 labelSize;

	std::string value;
	glm::vec2 valueSize;
	float& m_ref;
	const int maxCharacters = 10;

	// Lets make it blink cause we're that cool.
	float blinkTimer = 0;
	float blinkTime = 0.5f;

	float getValue();
};
