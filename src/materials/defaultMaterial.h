#pragma once
#include "materialBase.h"
#include "ui/properties/colorProperty.h"
#include "ui/properties/inputProperty.h"
#include "ui/properties/imageProperty.h"
#include "ui/properties/dropdownProperty.h"

class defaultMaterial : public materialBase
{
public:
	defaultMaterial();
	~defaultMaterial();

	void draw(int x, int y, int width);

	void begin();

	void end();

private:
	ofMaterial material;
	ofTexture originalTexture, filteredTexture;
	int currentFilterIndex = 0;

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
