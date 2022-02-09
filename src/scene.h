#pragma once

#include <vector>
#include "ofNode.h"
#include "UI/hierarchy/hierarchyPanel.h"

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

	void drawGrid()
	{
		ofPushMatrix();
		ofPushStyle();
		ofRotateX(90);

		ofSetLineWidth(2);
		ofSetColor(150);
		ofDrawRectangle(-100, -100, 200, 200);

		for (int x = -100; x < 100; x++)
		{
			ofSetColor(x == 0 ? ofColor(255, 0, 0, 50) : 50);
			ofDrawLine(-100, x, 100, x);
		}

		for (int z = -100; z < 100; z++)
		{
			ofSetColor(z == 0 ? ofColor(0, 0, 255, 50) : 50);
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
		hierarchy.draw(objects);
	}

private:
	scene() {}
	~scene()
	{
		for (auto i : objects) delete i;
	}

	std::vector<ofNode*> objects;

	hierarchyPanel hierarchy;
};

