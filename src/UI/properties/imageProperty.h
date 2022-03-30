#pragma once
#include "ofMain.h"

class imageProperty
{
public:
	function<void(string)> onImageImport;

	imageProperty(std::string label);

	void draw(int x, int y, int width);
	int getHeight();

	void setPreview(ofPixels& pixels);

	void resetPreview();

private:
	std::string m_label;

	ofImage preview;
	ofRectangle importBox;

	void importImage();
};
