#pragma once
#include "materialBase.h"
#include "ofShader.h"
#include "ui/properties/imageProperty.h"
#include "ui/properties/colorProperty.h"
#include "ui/properties/sliders/sliderProperty.h"
#include "ui/properties/groupProperty.h"
#include "objects/light.h"

class pbrMaterial : public materialBase
{
public:
	pbrMaterial();
	~pbrMaterial();

	void draw(int x, int y, int width);

	void begin();

	void end();

private:
	bool began = false;
	ofShader shader;

	groupProperty textureGroup;
	imageProperty diffuseProp, metallicProp, roughnessProp, occlusionProp;
	ofImage diffuseTex, metallicTex, roughnessTex, occlusionTex;

	colorProperty ambientColorProp, diffuseColorProp, specularColorProp;
	ofColor ambientColor = ofColor(255); 
	ofColor diffuseColor = ofColor(255);
	ofColor specularColor = ofColor(255);

	float brightness = 0.5f;
	float metallic = 0.5f;
	float roughness = 0.5f;
	float occlusion = 1.f;
	sliderProperty brightnessSlider, metallicSlider, roughnessSlider, occlusionSlider;

	light* firstLight;

	float gamma = 3.5f;
	sliderProperty gammaSlider;
};

