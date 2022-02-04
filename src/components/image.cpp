#include "image.h"

image::image(std::string path) : size(), im()
{
	im.load(path);
	size.x = im.getWidth();
	size.y = im.getHeight();

	cout << "Image loaded" << endl;
}

void image::customDraw()
{
	if (im.isAllocated())
	{
		cout << "draw" << endl;
		im.draw(getPosition(), size.x * getScale().x, size.y * getScale().y);
	}
}
