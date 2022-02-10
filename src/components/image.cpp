#include "image.h"

image::image(std::string path) : size(), im()
{
	im.load(path);
	size.x = im.getWidth() / 100;
	size.y = im.getHeight() / 100;

	cout << "Image loaded" << endl;
}

void image::customDraw()
{
	if (im.isAllocated())
	{
		im.draw(getPosition(), size.x * getScale().x, size.y * getScale().y);
	}
}

void image::drawHierarchy(int x, int y)
{
	ofDrawRectangle(x, y, 250, 40);
}
