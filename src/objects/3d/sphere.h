#pragma once

#include "objects/object.h"
#include "ui/properties/dropdownProperty.h"
#include "ui/properties/sliders/sliderProperty.h"

class sphere : public object
{
public:
	sphere(float radius);
	sphere(float radius, glm::vec3 p, glm::vec3 e, glm::vec3 c, int refl);

	void customDraw();
	void drawProperties(int x, int y, int width, int originX = 0, int originY = 0);
	glm::vec3 getBBox();

	float getRadius();
	glm::vec3 getEmission();
	int getReflection();

private:
	float m_radius;
	glm::vec3 m_emission;
	int m_reflection;
	bool m_raytracing;
	int m_resolution = 20;
	float m_contourThickness = 1;
	inputProperty radiusInput;
	sliderProperty resolutionInput;
	inputProperty contourThicknessInput;

	dropdownProperty raytracingTypeProp;
};

