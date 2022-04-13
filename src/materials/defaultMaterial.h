#pragma once
#include "materialBase.h"
#include "ui/properties/imageProperty.h"
#include "ui/properties/dropdownProperty.h"

class defaultMaterial : public materialBase
{
public:
	defaultMaterial();
	~defaultMaterial();

	void setObject(object& obj);

	void draw(int x, int y, int width);

private:
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
