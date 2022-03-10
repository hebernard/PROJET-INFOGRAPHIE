#pragma once
#include "ofMain.h"
#include "object.h"

class hierarchySmallButton;

struct keyframe
{
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	float time;

	keyframe(glm::vec3 pos, glm::vec3 rot, glm::vec3 s, float t) : position(pos), rotation(rot), scale(s), time(t)
	{
	}
};

class animationPanel
{
public:
	animationPanel();
	~animationPanel();

	void draw(int endX);

	void mouseDragged(ofMouseEventArgs& args);

	void setObject(object& obj);
	void addKeyFrame(object& obj);

	void save();
	void load();

private:
	ofImage icon;
	ofRectangle rect, playerRect;

	float timer = 0;
	float maxSeconds = 10;

	hierarchySmallButton* playButton;
	hierarchySmallButton* recordButton;

	object* m_obj = nullptr;
	float cursorPos = 0;
	bool isRecording = false;
	bool isPlaying = false;

	std::vector<keyframe> keyframes;

	void drawPlayer();

	void animateObject();
};

