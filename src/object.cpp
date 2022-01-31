#include "object.h"
#include <typeinfo>
#include <iostream>

object::object() : position(0,0,0), rotation(0,0,0), scale(1,1,1), components()
{
}

void object::addComponent(component* comp)
{
	components.push_back(comp);
	std::cout << "Added new component of type " << typeid(*comp).name() << std::endl;
}

template<typename component>
component object::getComponent()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		if (typeid(components.at(i)) == component)
		{
			return component;
		}
	}

	return NULL;
}

void object::drawComponents()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		components[i]->draw();
	}
}
