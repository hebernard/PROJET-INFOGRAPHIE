#pragma once

#include <vector>
#include "object.h"

class scene
{
public:
	static scene& getInstance()
	{
		static scene instance;
		return instance;
	}

	void addObject(object* obj)
	{
		objects.push_back(obj);
		std::cout << "Added object to scene" << std::endl;
	}

	void drawObjects()
	{
		for (size_t i = 0; i < objects.size(); i++)
		{
			objects[i]->drawComponents();
		}
	}

private:
	scene() {}
	~scene()
	{
		for (auto i : objects) delete i;
	}

	std::vector<object*> objects;
};

