#pragma once
#include "ofMain.h"

class hierarchySmallButton;

class imageProperty
{
public:
	function<void(string)> onImageImport;
	function<void()> onImageCleared;

	imageProperty(std::string label);

	~imageProperty();

	void draw(int x, int y, int width);
	int getHeight();

	void setPreview(ofPixels& pixels);

	void resetPreview();

private:
	std::string m_label;

	ofImage preview;
	ofRectangle importBox;
	hierarchySmallButton* closeButton;

	void importImage();
};
