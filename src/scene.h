#pragma once

#include <vector>
#include "components/object.h"
#include "UI/hierarchy/hierarchyPanel.h"
#include "camera.h"
#include "mainTheme.h"
#include "UI/properties/propertiesPanel.h"
#include "components/3d/sphere.h"
#include "components/2d/circle.h"

class scene
{
public:
	camera* camera;
	object* currentSelected;

	static scene& getInstance()
	{
		static scene instance;
		return instance;
	}

	void setupObjects() {
		sphere* sp = new sphere(1);
		sp->noFill = true;
		sp->setPosition(glm::vec3(0, 1, 0));
		addObject(sp);

		circle* circ = new circle(1.2f);
		circ->noFill = true;
		circ->setPosition(glm::vec3(0, 1, 0));
		addObject(circ);
	}

	void focusObject(object& obj)
	{
		if (currentSelected != nullptr)
		{
			currentSelected->isSelected = false;
		}

		camera->setTarget(obj.getCenter());

		obj.isSelected = true;

		currentSelected = &obj;
	}

	void addObject(object* obj)
	{
		objects.push_back(obj);
		std::cout << "Added object to scene" << std::endl;
	}

	void deleteObjects()
	{
		for (size_t i = 0; i < objects.size(); i++)
		{
			if (objects.at(i)->markedForDeletion)
			{
				objects.erase(objects.begin() + i);
			}
		}
	}

	void drawObjects()
	{
		for (size_t i = 0; i < objects.size(); i++)
		{
			auto obj = objects.at(i);
			if (obj->isVisible)
			{
				if (obj->isSelected)
				{
					ofPushStyle();
					ofNoFill();
					ofSetColor(mainTheme::color1());
					auto bbox = obj->getBBox();
					ofDrawBox(obj->getCenter(), bbox.x, bbox.y, bbox.z);
					ofPopStyle();
				}

				obj->customDraw();
			}
		}
	}

	void drawGrid()
	{
		ofPushMatrix();
		ofPushStyle();
		ofNoFill();
		ofRotateX(90);

		ofSetLineWidth(2);
		ofSetColor(mainTheme::gridColor2());
		ofDrawRectangle(-100, -100, 200, 200);

		for (int x = -100; x < 100; x++)
		{
			ofSetColor(x == 0 ? ofColor(255, 0, 0, 50) : mainTheme::gridColor1());
			ofDrawLine(-100, x, 100, x);
		}

		for (int z = -100; z < 100; z++)
		{
			ofSetColor(z == 0 ? ofColor(0, 0, 255, 50) : mainTheme::gridColor1());
			ofDrawLine(z, -100, z, 100);
		}

		ofRotateX(-90);
		ofSetColor(ofColor(0, 255, 0, 50));
		ofDrawLine(0, -100, 0, 100);

		ofPopMatrix();
		ofPopStyle();
	}

	void drawHierarchyUI()
	{
		if (currentSelected != nullptr && currentSelected->propertiesOpened)
		{
			properties.draw(*currentSelected);
		}
		else
		{
			hierarchy.draw(objects);
		}
	}

private:
	scene() : camera() {}
	~scene()
	{
		for (auto i : objects) delete i;
	}

	std::vector<object*> objects;

	hierarchyPanel hierarchy;
	propertiesPanel properties;
};

