#include "objectModel.h"

objectModel::objectModel(std::string path) : object(new hierarchyButton(*this, "images/icons/3Dobject1.png", "3D Object")), obj()
{
	obj.loadModel(path, true);
	obj.setScaleNormalization(true);

	cout << "3D object loaded" << endl;
}

void objectModel::customDraw()
{
	obj.drawFaces();
}

glm::vec3 objectModel::getCenter()
{
	// todo
	return getPosition();
}

glm::vec3 objectModel::getBBox()
{
	// todo
	return glm::vec3();
}
