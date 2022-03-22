#pragma once

#include "ofMain.h"
#include "object.h"

enum class ShaderType { none, color_fill, lambert, gouraud, phong, blinn_phong };
enum class LightType { ambient, directional, point, spot };

class light : public object
{
public :

	ofLight li;

	light();
	void update();
	void customDraw();

	ShaderType getIlluminationModel();
	void setIlluminationModel(ShaderType model);

	LightType getType();
	void setType(LightType type);

	void hide();

	float oscillate(float time, float frequency, float amplitude);

private :

	bool isEnabled;
	bool hideLight;

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

};

