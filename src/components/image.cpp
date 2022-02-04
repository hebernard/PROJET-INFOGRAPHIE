#include "image.h"

image::image(std::string path) : ofNode(), size(0,0), im()
{
	im.load(path);
	size.x = im.getWidth();
	size.y = im.getHeight();
}

void image::drawUI()
{
}

void image::customDraw()
{
	if (im.isAllocated())
	{
		im.draw(getPosition(), size.x * getScale().x, size.y * getScale().y);
	}
}
