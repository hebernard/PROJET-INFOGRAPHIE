#pragma once

#include <vector>
#include "components/component.h"
#include "glm/glm.hpp"

class object
{
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	object();

	void addComponent(component* comp);

	template<typename component>
	component getComponent();

	void drawComponents();

private:
	std::vector<component*> components;
};

