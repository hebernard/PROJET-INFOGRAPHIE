#pragma once

#include "object.h"
#include "inputProperty.h"
#include "checkBoxProperty.h"
#include "dropdownProperty.h"

class sphere : public object
{
public:
	sphere(float radius);
	sphere(float radius, glm::vec3 p, glm::vec3 e, glm::vec3 c, int refl);

	void customDraw();
	void drawProperties(int x, int y, int width);
	glm::vec3 getBBox();

	float getRadius();
	glm::vec3 getEmission();
	int getReflection();

private:
	float m_radius;
	glm::vec3 m_emission;
	int m_reflection;
	bool m_raytracing;
	float m_resolution = 20;
	float m_contourThickness = 1;
	inputProperty radiusInput;
	inputProperty resolutionInput;
	inputProperty contourThicknessInput;

	dropdownProperty raytracingTypeProp;
};

