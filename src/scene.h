#pragma once

#include <vector>
#include "objects/object.h"
#include "objects/3d/sphere.h"
#include "objects/2d/circle.h"
#include "objects/light.h"
#include "ui/hierarchy/hierarchyPanel.h"
#include "ui/mainTheme.h"
#include "ui/properties/propertiesPanel.h"
#include "raytracing/ui/raytracingPanel.h"
#include "camera.h"

class scene
{
public:
	object* currentSelected;
	bool gridIsVisible = true;

	bool showRaytracingPanel = false;
	raytracingPanel raytracing;

	static scene& getInstance()
	{
		static scene instance;
		return instance;
	}

	void setupObjects()
	{
		// Add the necessary light
		addLight();

		sphere* sp = new sphere(1);
		sp->setPosition(glm::vec3(0, 1, 0));
		addObject(sp);

		circle* circ = new circle(1.2f);
		circ->setPosition(glm::vec3(0, 1, 0));
		circ->filled = false;
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
			if (currentSelected->propertiesOpened)
			{
				properties.animationPanelVisible = false;
				properties.materialPanelVisible = false;
				currentSelected->propertiesOpened = false;
			}
			currentSelected->isSelected = false;
		}

		if (!showRaytracingPanel)
		{
			for (size_t i = 0; i < cameras.size(); i++)
			{
				cameras.at(i)->setTarget(obj.getCenter());
			}
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
		ofEnableLighting();
		ofEnableDepthTest();

		for (auto& l : lights)
		{
			if (l->li.getType() != ofLightType::OF_LIGHT_AREA && l->isVisible)
			{
				l->li.enable();
			}
		}

		for (size_t i = 0; i < objects.size(); i++)
		{
			auto obj = objects.at(i);
			if (obj->isVisible)
			{
				obj->drawWithTransformations();
			}
		}

		for (auto& l : lights)
		{
			if (l->li.getType() != ofLightType::OF_LIGHT_AREA && l->isVisible)
			{
				l->li.disable();
			}
		}

		ofDisableDepthTest();
		ofDisableLighting();
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
		if (showRaytracingPanel)
		{
			return;
		}

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

	void addLight()
	{
		light* li = new light(lights.size());
		if (li->id == 0)
		{
			// Setup for initial light
			li->setPosition(5, 5, 5);
			li->lookAt(glm::vec3(0, 0, 0));
		}

		// Add right after the last light
		addObject(li, lights.size());

		lights.push_back(li);
	}

	void removeLight(int id)
	{
		for (int i = 0; i < lights.size(); i++)
		{
			if (lights[i]->id == id)
			{
				lights.erase(lights.begin() + i);
			}
		}

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

	light& getFirstLight()
	{
		return *lights.at(0);
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
	std::vector<light*> lights;

	hierarchyPanel hierarchy;
	propertiesPanel properties;

	bool isOrtho = false;
};

