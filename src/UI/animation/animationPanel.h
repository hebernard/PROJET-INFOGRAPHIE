#pragma once
#include "ofMain.h"
#include "object.h"

class hierarchySmallButton;
class keyframe;

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

