#include "image.h"

image::image(std::string path) : object(new hierarchyButton(*this, "images/icons/image.png", "Image")), size(), im()
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
		auto scale = getScale();
		float width = size.x * scale.x;
		float height = size.y * scale.y;
		im.draw(-width / 2, -height / 2, 0, width, height);
	}
}

void image::drawProperties(int x, int y, int width)
{
	// Dont call base class to not set filled property
	// todo
}

glm::vec3 image::getBBox()
{
	auto scale = getScale();
	return glm::vec3(size.x * scale.x, size.y * scale.y, 0);
}
