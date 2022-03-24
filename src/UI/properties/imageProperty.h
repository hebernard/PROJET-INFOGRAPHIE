#pragma once
#include "ofMain.h"

class imageProperty
{
public:
	imageProperty(std::string label);

	void draw(ofTexture& tex, int x, int y, int width);
	int getHeight();

private:
	std::string m_label;

	ofImage preview;
	ofRectangle importBox;

	void importImage(ofTexture& tex);
};

