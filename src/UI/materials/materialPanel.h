#pragma once
#include "ofMain.h"
#include "object.h"
#include "imageProperty.h"
#include "colorProperty.h"
#include "inputProperty.h"
#include "dropdownProperty.h"

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
	object* ref;

	ofRectangle rect;
	ofMaterial refMat;
	imageProperty imgProp;
	dropdownProperty filterProp;

	ofColor* ambientColor;
	ofColor* diffuseColor;
	ofColor* emissiveColor;
	ofColor* specularColor;
	float* shininess;

	colorProperty ambientColorProp;
	colorProperty diffuseColorProp;
	colorProperty emissiveColorProp;
	colorProperty specularColorProp;
	inputProperty shininessProp;

	void setFilter(int index);
};

