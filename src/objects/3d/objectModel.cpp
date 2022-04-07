#include "objectModel.h"

objectModel::objectModel(std::string path) : object(new hierarchyButton(*this, "images/icons/3Dobject1.png", "3D Object")), obj()
{
	obj.loadModel(path, true);
	obj.setScaleNormalization(true);
	obj.setRotation(0, 180, 1, 0, 0);
	obj.setScale(0.1f, 0.1f, 0.1f);
	obj.disableMaterials();

	cout << "3D object loaded" << endl;
}

void objectModel::customDraw()
{
	obj.drawFaces();
}

void objectModel::drawProperties(int x, int y, int width)
{
	//bboxCheckBox->draw(x, y, width);
	//colorPicker->draw(x, y + bboxCheckBox->getHeight() + 10, width);
	//colorPicker->draw(x, y, width);
}

glm::vec3 objectModel::getBBox()
{
	/*ofMesh mesh = obj.getMesh(0);
	auto vertices = mesh.getVertices();
	float minX = sizeof(float);
	float minY = sizeof(float);
	float minZ = sizeof(float);

	float maxX = -sizeof(float);
	float maxY = -sizeof(float);
	float maxZ = -sizeof(float);

	for (size_t i = 0; i < vertices.size(); i++)
	{
		auto vertex = vertices.at(i);
		if (vertex.x < minX)
		{
			minX = vertex.x;
		}

		if (vertex.y < minY)
		{
			minY = vertex.y;
		}

		if (vertex.z < minZ)
		{
			minZ = vertex.z;
		}

		if (vertex.x > maxX)
		{
			maxX = vertex.x;
		}

		if (vertex.y > maxY)
		{
			maxY = vertex.y;
		}

		if (vertex.z > maxZ)
		{
			maxZ = vertex.z;
		}
	}

	return glm::vec3(maxX - minX, maxY - minY, maxZ - minZ);*/
	return glm::vec3(0, 0, 0);
}
