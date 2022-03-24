#pragma once
#include "ofMain.h"
#include "object.h"
#include "imageProperty.h"
#include "colorProperty.h"
#include "inputProperty.h"

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

	ofColor* ambientColor = new ofColor(255);
	ofColor* diffuseColor = new ofColor(255);
	ofColor* emissiveColor = new ofColor(255);
	ofColor* specularColor = new ofColor(255);
	float* shininess = new float(0);

	colorProperty ambientColorProp{ "Ambient", *ambientColor };
	colorProperty diffuseColorProp{ "Diffuse", *diffuseColor };
	colorProperty emissiveColorProp{ "Emissive", *emissiveColor };
	colorProperty specularColorProp{ "Specular", *specularColor };
	inputProperty shininessProp{ "Shininess", *shininess };
};

