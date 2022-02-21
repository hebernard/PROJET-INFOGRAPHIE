#pragma once
#include "object.h"
#include "ofxAssimpModelLoader.h"

class objectModel : public object
{
public:
	objectModel(std::string path);

	void customDraw();
	glm::vec3 getCenter();
	glm::vec3 getBBox();

private:
	ofxAssimpModelLoader obj;
};