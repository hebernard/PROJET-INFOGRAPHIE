#pragma once
#include "ofMain.h"
#include "objects/3d/sphere.h"
#include "ui/hierarchy/hierarchySmallButton.h"
#include "ui/properties/propertiesPanel.h"

// Struct for doing PingPong quickly and easy
//
// Because on GPU you can't write over the texture that you are reading we are
// using to pair of ofFbo attached together on what we call pingPongBuffer
// Learn more about Ping-Pong at:
//
// http://www.seas.upenn.edu/~cis565/fbo.htm#setupgl4
//
struct pingPongBuffer {
public:
	void allocate(int _width, int _height, int _internalformat = GL_RGB32F) {

		vector<float> pos(_width * _height * 3);
		for (int x = 0; x < _width; x++) {
			for (int y = 0; y < _height; y++) {
				int i = _height * y + x;

				pos[i * 3 + 0] = 0.0f;
				pos[i * 3 + 1] = 0.0f;
				pos[i * 3 + 2] = 0.0f;
				//pos[i * 3 + 3] = 0.0f;
			}
		}

		// Allocate
		for (int i = 0; i < 2; i++) {
			FBOs[i].allocate(_width, _height, _internalformat);
			FBOs[i].getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
			FBOs[i].getTexture().loadData(pos.data(), _width, _height, _internalformat);
		}

		//Assign
		src = &FBOs[0];
		dst = &FBOs[1];

		// Clean
		clear();
	}

	void swap() {
		std::swap(src, dst);
	}

	void clear() {
		for (int i = 0; i < 2; i++) {
			FBOs[i].begin();
			ofClear(0, 255);
			FBOs[i].end();
		}
	}

	ofFbo& operator[](int n) { return FBOs[n]; }
	ofFbo* src;       // Source       ->  Ping
	ofFbo* dst;       // Destination  ->  Pong

private:
	ofFbo   FBOs[2];    // Real addresses of ping/pong FBO«s
};

class raytracingPanel
{
public:
	raytracingPanel();
	~raytracingPanel();
	void setup();

	void pause();

	void update();
	void draw();

	void addSphere(sphere* s);

private:
	bool isSetup = false;
	bool isPlaying = true;

	int max_depth = 4;

	pingPongBuffer pingPong;
	ofFbo renderFBO;

	ofShader multipass_shader, render_shader;

	float time = 0;
	int frameNum = 0;

	const int NUM_SPHERES = 64;
	std::vector<sphere*> spheres;

	void addSphereToShader(string name, sphere& s);

	int getNextAvailableIndex();

	// UI
	int width = 512;
	int height = 512;
	ofImage hierarchyIcon;
	ofRectangle renderRect, toolbarRect, hierarchyRect;
	hierarchySmallButton resetButton, playButton;
	propertiesPanel propPanel;

	void play();

	void drawToolbar();
	void drawHierarchy();
};
