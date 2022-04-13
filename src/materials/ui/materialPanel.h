#pragma once
#include "ofMain.h"
#include "materials/defaultMaterial.h"

class hierarchySmallButton;

class materialPanel
{
public:
	hierarchySmallButton* backButton;

	materialPanel();
	~materialPanel();

	void draw();

	void setObject(object& obj);

private:
	ofRectangle rect;
	materialBase* mat;
};

