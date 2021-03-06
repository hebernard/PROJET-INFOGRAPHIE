#pragma once

#include "ofMain.h"
#include "object.h"
#include "ui/hierarchy/lightHierarchyButton.h"
#include "ui/properties/dropdownProperty.h"
#include "ui/properties/sliders/sliderProperty.h"
#include "ui/properties/groupProperty.h"

class light : public object
{
public:
	int id;
	ofLight li;

	light(int id);
	void customDraw();

	void drawProperties(int x, int y, int width, int originX = 0, int originY = 0);

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

	groupProperty spotlightGroup;
	float spotConcentration = 2;
	sliderProperty spotConcentrationProp;

	float spotlightCutOff = 30;
	sliderProperty spotlightCutOffProp;

	float constantAtt = 1.0f;
	sliderProperty constantAttProp;

	float linearAtt = 0.0f;
	sliderProperty linearAttProp;

	float quadraticAtt = 0.0f;
	sliderProperty quadraticAttProp;
};
