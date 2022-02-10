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
		im.draw(getPosition(), size.x * getScale().x, size.y * getScale().y);
	}
}

glm::vec3 image::getCenter()
{
	glm::vec3 pos = getPosition();
	return glm::vec3(pos.x + (size.x * getScale().x / 2), pos.y + (size.y * getScale().y / 2), pos.z);
}
