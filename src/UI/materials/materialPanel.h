#pragma once
#include "ofMain.h"
#include "object.h"
#include "imageProperty.h"

class hierarchySmallButton;

class materialPanel
{
public:
	hierarchySmallButton* backButton;

	materialPanel();
	~materialPanel();

	void draw(object& obj);

private:
	ofRectangle rect;

	imageProperty imgProp;
};

