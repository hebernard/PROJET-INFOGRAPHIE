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
	ofMaterial refMat;
	imageProperty imgProp;

	ofColor* ambientColor;
	ofColor* diffuseColor;
	ofColor* emissiveColor;
	ofColor* specularColor;
	float* shininess;

	colorProperty ambientColorProp{ "Ambient", *ambientColor };
	colorProperty diffuseColorProp{ "Diffuse", *diffuseColor };
	colorProperty emissiveColorProp{ "Emissive", *emissiveColor };
	colorProperty specularColorProp{ "Specular", *specularColor };
	inputProperty shininessProp{ "Shininess", *shininess };
};

