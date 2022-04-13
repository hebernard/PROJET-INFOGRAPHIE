#pragma once
#include "materialBase.h"
#include "ofShader.h"

class pbrMaterial : public materialBase
{
public:
	pbrMaterial();
	~pbrMaterial();

	void draw(int x, int y, int width);

	void begin();

	void end();

private:
	ofShader shader;
};

