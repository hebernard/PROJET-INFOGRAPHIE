#include "pbrMaterial.h"

pbrMaterial::pbrMaterial() : materialBase("PBR"), shader()
{
}

pbrMaterial::~pbrMaterial()
{
}

void pbrMaterial::draw(int x, int y, int width)
{
}

void pbrMaterial::begin()
{
	shader.begin();
}

void pbrMaterial::end()
{
	shader.end();
}
