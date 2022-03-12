#pragma once
#include "glm/glm.hpp"

struct keyframe
{
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	float time;

	keyframe(glm::vec3 pos, glm::vec3 rot, glm::vec3 s, float t);
};

