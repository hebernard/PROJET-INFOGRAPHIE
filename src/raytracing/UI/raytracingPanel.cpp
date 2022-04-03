#include "raytracingPanel.h"
#include "panel.h"
#include "label.h"
#include "utils.h"
#include "scene.h"

raytracingPanel::raytracingPanel() : resetButton("images/icons/resume.png"), playButton("images/icons/pause.png"), spheres()
{
}

raytracingPanel::~raytracingPanel()
{
	for (auto s : spheres) delete s;
}

void raytracingPanel::setup()
{
	if (isSetup)
	{
		return;
	}
	isSetup = true;

	renderRect.width = width;
	renderRect.height = height;

	toolbarRect.width = renderRect.width;
	toolbarRect.height = 30;

	hierarchyRect.width = 300;
	hierarchyRect.height = renderRect.height;

	hierarchyIcon.load("images/icons/hierarchy.png");
	hierarchyIcon.resize(24, 24);

	propPanel.anchoredRight = false;
	propPanel.enableScaling = false;
	propPanel.enableRotation = false;
	propPanel.onUpdate = [&]()
	{
		time = 0;
		frameNum = 0;
	};

	multipass_shader.load("shaders/passthrough.vert", "shaders/raytracer_multipass.frag");

	multipass_shader.begin();
	// Add the walls & light
	sphere w1 = sphere(1e5f, { -1e5f + 1.f, 40.8f, 81.6f }, { 0.f, 0.f, 0.f }, { .75f, .25f, .25f }, 0);
	addSphereToShader("spheres[0]", w1);
	sphere w2 = sphere(1e5f, { 1e5f + 99.f, 40.8f, 81.6f }, { 0.f, 0.f, 0.f }, { .25f, .25f, .75f }, 0);
	addSphereToShader("spheres[1]", w2);
	sphere w3 = sphere(1e5f, { 50.f, 40.8f, -1e5f }, { 0.f, 0.f, 0.f }, { .75f, .75f, .75f }, 0);
	addSphereToShader("spheres[2]", w3);
	sphere w4 = sphere(1e5f, { 50.f, 40.8f, 1e5f + 170.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, 0);
	addSphereToShader("spheres[3]", w4);
	sphere w5 = sphere(1e5f, { 50.f, -1e5f, 81.6f }, { 0.f, 0.f, 0.f }, { .75f, .75f, .75f }, 0);
	addSphereToShader("spheres[4]", w5);
	sphere w6 = sphere(1e5f, { 50.f, 1e5f + 81.6f, 81.6f }, { 0.f, 0.f, 0.f }, { .75f, .75f, .75f }, 0);
	addSphereToShader("spheres[5]", w6);
	sphere w7 = sphere(600.f, { 50.f, 681.33f, 81.6f }, { 12.f, 12.f, 12.f }, { 0.f, 0.f, 0.f }, 0);
	addSphereToShader("spheres[6]", w7);

	sphere light = sphere(20.f, { 50.f, 81.6f, 81.6f }, { 12.f, 12.f, 12.f }, { 0.f, 0.f, 0.f }, 0);
	addSphereToShader("lightSourceVolume", light);
	multipass_shader.end();

	pingPong.allocate(renderRect.width, renderRect.height);

	render_shader.load("shaders/passthrough.vert", "shaders/raytracer_render.frag");

	renderFBO.allocate(renderRect.width, renderRect.height);

	// Add a default sphere
	sphere* s = new sphere(16.5f, { 27.f, 16.5f, 47.f }, { 0.f, 0.f, 0.f }, { 1.f, 1.f, 1.f }, 1);
	addSphere(s);

	// UI
	resetButton.onButtonEvent([&](auto e)
	{
		time = 0;
		frameNum = 0;

		play();
	});

	playButton.onButtonEvent([&](auto e)
	{
		if (isPlaying)
		{
			pause();
		}
		else
		{
			play();
		}
	});
}

void raytracingPanel::update()
{
	renderRect.x = ofGetWidth() / 2 - renderRect.width / 2 - 150;
	renderRect.y = ofGetHeight() / 2 - renderRect.height / 2;

	toolbarRect.x = renderRect.x;
	toolbarRect.y = renderRect.y + renderRect.height;

	hierarchyRect.x = renderRect.x + renderRect.width;
	hierarchyRect.y = renderRect.y;

	propPanel.setPosition(hierarchyRect.x, hierarchyRect.y);
	propPanel.setHeight(hierarchyRect.height);

	if (isPlaying)
	{
		time += ofGetLastFrameTime();
		frameNum++;

		pingPong.dst->begin();
		multipass_shader.begin();
		multipass_shader.setUniform2f("resolution", renderRect.width, renderRect.height);
		multipass_shader.setUniformTexture("channel0", pingPong.src->getTexture(), 0);
		multipass_shader.setUniform1f("time", time);
		multipass_shader.setUniform1i("frame", frameNum);
		multipass_shader.setUniform1i("MAXDEPTH", max_depth);
		for (int i = 0; i < NUM_SPHERES; i++)
		{
			if (i < spheres.size())
			{
				addSphereToShader("spheres[" + ofToString(i + 7) + "]", *spheres[i]);
			}
		}

		if (renderRect.inside(ofGetMouseX(), ofGetMouseY()) && ofGetMousePressed() && !utils::isMouseOverUI)
		{
			int x = ofGetMouseX() - renderRect.x;
			int y = ofGetMouseY() - renderRect.y;

			multipass_shader.setUniform2f("mouse", x, y);
			time = 0;
			frameNum = 0;
		}

		pingPong.src->draw(0, 0);

		multipass_shader.end();
		pingPong.dst->end();

		pingPong.swap();

		// Render
		renderFBO.begin();

		render_shader.begin();
		render_shader.setUniformTexture("channel0", pingPong.dst->getTexture(), 0);

		pingPong.src->draw(0, 0);

		render_shader.end();

		renderFBO.end();
	}

	// UI
	resetButton.update(toolbarRect.x, toolbarRect.y);
	playButton.update(toolbarRect.x + resetButton.getWidth() + 5, toolbarRect.y);
}

void raytracingPanel::draw()
{
	renderFBO.draw(renderRect.x, renderRect.y);

	// UI
	scene& s = s.getInstance();
	if (s.currentSelected != nullptr && s.currentSelected->propertiesOpened)
	{
		propPanel.draw(*s.currentSelected);
	}
	else
	{
		drawHierarchy();
	}
	drawToolbar();
}

void raytracingPanel::addSphere(sphere* s)
{
	s->canBeAnimated = false;
	s->canHaveMaterial = false;

	if (spheres.size() < NUM_SPHERES)
	{
		spheres.push_back(s);
	}
	else
	{
		spheres[getNextAvailableIndex()] = s;
	}

	time = 0;
	frameNum = 0;
}

void raytracingPanel::addSphereToShader(string name, sphere& s)
{
	multipass_shader.setUniform1f(name + ".radius", s.getRadius());
	multipass_shader.setUniform3f(name + ".position", s.getPosition());
	multipass_shader.setUniform3f(name + ".e", s.getEmission());
	multipass_shader.setUniform3f(name + ".color", s.color.r / 255.f, s.color.g / 255.f, s.color.b / 255.f);
	multipass_shader.setUniform1i(name + ".reflection", s.getReflection());
	multipass_shader.setUniform1i(name + ".visible", s.markedForDeletion ? false : s.isVisible);
}

int raytracingPanel::getNextAvailableIndex()
{
	for (int i = 0; i < spheres.size(); i++)
	{
		if (spheres[i]->markedForDeletion)
		{
			return i;
		}
	}

	return spheres.size() - 1;
}

void raytracingPanel::play()
{
	isPlaying = true;
	playButton.changeIcon("images/icons/pause.png");
}

void raytracingPanel::pause()
{
	isPlaying = false;
	playButton.changeIcon("images/icons/play.png");
}

void raytracingPanel::drawToolbar()
{
	ofPushStyle();
	ofSetColor(mainTheme::panelColor());
	ofDrawRectRounded(toolbarRect, 0, 0, 8, 8);
	ofPopStyle();

	resetButton.draw();
	playButton.draw();

	std::string num_text = std::to_string(time);
	std::string rounded = num_text.substr(0, num_text.find(".") + 3);

	std::string label = "Time: " + rounded + "    Frame: " + ofToString(frameNum);
	auto size = label::getSize(label, 10);
	drawText(toolbarRect.x + resetButton.getWidth() + playButton.getWidth() + 10, toolbarRect.y + toolbarRect.height / 2 + size.y / 2, label, 10);

	std::string fps = "Size: " + ofToString(renderRect.width) + "x" + ofToString(renderRect.height) + "    FPS: " + ofToString((int)ofGetFrameRate());
	size = label::getSize(fps, 10);
	drawText(toolbarRect.x + toolbarRect.width - size.x - 10, toolbarRect.y + toolbarRect.height / 2 + size.y / 2, fps, 10);
}

void raytracingPanel::drawHierarchy()
{
	ofPushStyle();
	ofSetColor(mainTheme::panelColor());
	ofDrawRectRounded(hierarchyRect, 0, 8, 8, 0);

	drawText(hierarchyRect.x + 60, hierarchyRect.y + 32, "Hierarchy", 14);

	ofSetColor(255);
	hierarchyIcon.draw(hierarchyRect.x + 15, hierarchyRect.y + 10);
	ofPopStyle();

	for (int i = 0, j = 0; i < NUM_SPHERES; i++)
	{
		if (i < spheres.size() && !spheres[i]->markedForDeletion)
		{
			spheres[i]->drawHierarchy(hierarchyRect.x, hierarchyRect.y + 56 + (j * 30));

			j++;
		}
	}
}
