#pragma once
#include "ofMain.h"

class sliderBase
{
public:
	bool manualUpdate = false;

	sliderBase(std::string label);
	virtual ~sliderBase();

	virtual void draw(int x, int y, int width);

	float getHeight();

protected:
	float thumbPos = 0.f;

	std::string value = "0";
	std::string minS = "0";
	std::string maxS = "0";

	virtual void onValueUpdate();

private:
	std::string m_label;
	glm::vec2 textSize;

	ofRectangle rect;

	int thumbRadius = 10.f;

	const int FONT_SIZE = 11;

	bool dragStarted = false;

	void updateThumb();
};

