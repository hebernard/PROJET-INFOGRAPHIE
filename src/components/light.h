#pragma once

#include "ofMain.h"
#include "object.h"
#include "dropdownProperty.h"
#include "colorProperty.h"
#include "lightHierarchyButton.h"
#include "inputProperty.h"

class light : public object
{
public:
	int id;
	ofLight li;

	light(int id);
	void customDraw();

	void drawProperties(int x, int y, int width);

	void setType(ofLightType type);

private:
	lightHierarchyButton& lightButton;

	ofColor ambientColor = ofColor::white;
	ofColor diffuseColor = ofColor::white;
	ofColor specularColor = ofColor::white;

	// Properties
	dropdownProperty lightTypeProp;
	colorProperty ambientColorProp;
	colorProperty diffuseColorProp;
	colorProperty specularColorProp;

	float spotConcentration = 2;
	inputProperty spotConcentrationProp;

	float spotlightCutOff = 30;
	inputProperty spotlightCutOffProp;
};
