#pragma once

#include <vector>
#include "components/object.h"
#include "UI/hierarchy/hierarchyPanel.h"
#include "camera.h"
#include "light.h"
#include "mainTheme.h"
#include "UI/properties/propertiesPanel.h"
#include "components/3d/sphere.h"
#include "components/2d/circle.h"
#include "components/light.h"

class scene
{
public:
	object* currentSelected;
	bool gridIsVisible = true;

	static scene& getInstance()
	{
		static scene instance;
		return instance;
	}

	void setupObjects()
	{
		// Add the necessary light
		addLight(false);

		sphere* sp = new sphere(1);
		sp->setPosition(glm::vec3(0, 1, 0));
		addObject(sp);

		circle* circ = new circle(1.2f);
		circ->setPosition(glm::vec3(0, 1, 0));
		addObject(circ);
	}

	void focusObject(object& obj)
	{
		if (!&obj)
		{
			return;
		}

		if (currentSelected != nullptr)
		{
			currentSelected->isSelected = false;
		}

		for (size_t i = 0; i < cameras.size(); i++)
		{
			cameras.at(i)->setTarget(obj.getCenter());
		}

		//camera->setDistance(5);

		obj.isSelected = true;

		currentSelected = &obj;
	}

	void addObject(object* obj, int index = -1)
	{
		if (index == -1)
		{
			objects.push_back(obj);
		}
		else
		{
			objects.insert(objects.begin() + index, obj);
		}
		focusObject(*obj);
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
				obj->drawWithTransformations();
			}
		}
	}

	void drawGrid()
	{
		if (gridIsVisible) {
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

	void addCamera()
	{
		if (cameraCount() >= 4)
		{
			return;
		}

		camera* cam = new camera();
		cam->setAutoDistance(false);
		cam->setFarClip(100000);
		if (isOrtho)
		{
			cam->setOrtho();
		}
		else 
		{
			cam->setPerpective();
		}

		cameras.push_back(cam);
	}

	void addLight(bool isSecondary)
	{
		light* li = new light(isSecondary);
		li->canHaveMaterial = false;

		// Add right after the last light
		addObject(li, lightCount);

		lightCount++;
	}

	void removeLight()
	{
		lightCount--;
		deleteObjects();
	}

	void removeCamera()
	{
		if (cameraCount() > 1)
		{
			cameras.erase(cameras.begin() + cameraCount() - 1);
		}
	}

	std::vector<camera*>& getCameras()
	{
		return cameras;
	}

	int cameraCount()
	{
		return cameras.size();
	}

	void enableMouseInputs()
	{
		for (size_t i = 0; i < cameras.size(); i++)
		{
			cameras.at(i)->enableMouseInput();
		}
	}

	void disableMouseInputs()
	{
		for (size_t i = 0; i < cameras.size(); i++)
		{
			cameras.at(i)->disableMouseInput();
		}
	}

	void enableCamerasOrtho()
	{
		for (size_t i = 0; i < cameras.size(); i++)
		{
			cameras.at(i)->setOrtho();
		}
		isOrtho = true;
	}

	void disableCamerasOrtho()
	{
		for (size_t i = 0; i < cameras.size(); i++)
		{
			cameras.at(i)->setPerpective();
		}
		isOrtho = false;
	}

	void resetViews()
	{
		for (size_t i = 0; i < cameras.size(); i++)
		{
			cameras.at(i)->resetView();
		}
	}

private:
	scene() {}
	~scene()
	{
		for (auto i : objects) delete i;
		for (auto c : cameras) delete c;
	}

	std::vector<object*> objects;
	std::vector<camera*> cameras;
	int lightCount = 0;

	hierarchyPanel hierarchy;
	propertiesPanel properties;

	bool isOrtho = false;
};

