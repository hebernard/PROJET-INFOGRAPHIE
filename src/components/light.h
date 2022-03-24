#pragma once

#include "ofMain.h"
#include "object.h"
#include "dropdownProperty.h"

enum class ShaderType { none, color_fill, lambert, gouraud, phong, blinn_phong };
enum class LightType { ambient, directional, point, spot };

class light : public object
{
public:
	ofLight li;

	light(bool isSecondary);
	void update();
	void customDraw();

	void drawProperties(int x, int y, int width);

	ShaderType getIlluminationModel();
	void setIlluminationModel(ShaderType model);

	LightType getType();
	void setType(LightType type);

	float oscillate(float time, float frequency, float amplitude);

private:

	float oscillation;
	float oscillationFrequency;
	float oscillationAmplitude;

	//Illumination Model
	bool isActiveShader;
	ShaderType activeShader;

	ofShader* shader;
	string shaderName;

	ofShader shaderColorFill;
	ofShader shaderLambert;
	ofShader shaderGouraud;
	ofShader shaderPhong;
	ofShader shaderBlinnPhong;

	glm::vec3 color;
	glm::vec3 colorAmbient;
	glm::vec3 colorDiffuse;
	glm::vec3 colorSpecular;

	//Light Type
	LightType activeType;

	ofColor ambientColor;
	ofColor diffuseColor;
	ofColor specularColor;

	bool smoothLighting;

	// Properties
	dropdownProperty lightTypeProp;
};
