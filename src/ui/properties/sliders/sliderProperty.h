#pragma once
#include "ofRectangle.h"
#include <iostream>
#include "intSliderProperty.h"
#include "floatSliderProperty.h"

class sliderProperty
{
public:
	sliderProperty(std::string label, float& ref, float min, float max);
	sliderProperty(std::string label, int& ref, int min, int max);
	~sliderProperty();

	void draw(int x, int y, int width);

	float getHeight();

private:
	sliderBase* slider;
};
