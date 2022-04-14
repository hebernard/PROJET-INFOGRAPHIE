#pragma once
#include "ui/uiComponent.h"
#include "ofImage.h"

class groupProperty : public uiComponent
{
public:
	std::function<void(int x, int y)> drawOnToggled;

	groupProperty(std::string label);

	void draw();

	void toggle(bool active);

	bool isToggled();

	void setFullHeight(float h);
	float getRealHeight();

private:
	glm::vec2 textSize;
	std::string label;
	bool toggled;
	float fullHeight = 0;

	ofImage arrowIcon;
};

