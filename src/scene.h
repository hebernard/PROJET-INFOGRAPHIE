#pragma once

#include <vector>
#include "ofNode.h"

class scene
{
public:
	static scene& getInstance()
	{
		static scene instance;
		return instance;
	}

	void addObject(ofNode* obj)
	{
		objects.push_back(obj);
		std::cout << "Added object to scene" << std::endl;
	}

	void drawObjects()
	{
		for (size_t i = 0; i < objects.size(); i++)
		{
			objects[i]->customDraw();
		}
	}

private:
	scene() {}
	~scene()
	{
		for (auto i : objects) delete i;
	}

	std::vector<ofNode*> objects;
};

