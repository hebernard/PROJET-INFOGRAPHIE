#include "animationPanel.h"
#include "keyframe.h"
#include "panel.h"
#include "label.h"
#include "hierarchySmallButton.h"
#include "utils.h"

animationPanel::animationPanel() : 
	playButton(new hierarchySmallButton("images/icons/play.png")),
	recordButton(new hierarchySmallButton("images/icons/rec.png"))
{
	icon.load("images/icons/animation.png");
	icon.resize(24, 24);

	recordButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		isPlaying = false;
		isRecording = !isRecording;
	});

	playButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		isRecording = false;
		isPlaying = !isPlaying;
		timer = 0;
	});
}

animationPanel::~animationPanel()
{
	delete playButton;
	delete recordButton;
}

void animationPanel::draw(int endX)
{
	if (rect.inside(ofGetMouseX(), ofGetMouseY()))
	{
		utils::isMouseOverUI = true;
	}

	rect.x = 10;
	rect.y = ofGetHeight() - 200;
	rect.width = endX - rect.x;
	rect.height = 175;

	drawPanel(rect);

	drawText(rect.x + 60, rect.y + 32, "Animation", 14);

	if (icon.isAllocated())
	{
		icon.draw(rect.x + 15, rect.y + icon.getHeight() / 2);
	}

	playButton->update(rect.x + 170, rect.y + 10);
	playButton->draw();

	recordButton->update(playButton->getX() + playButton->getWidth() + 5, rect.y + 10);
	recordButton->draw();

	drawPlayer();

	if (utils::rightMouseReleased)
	{
		for (size_t i = 0; i < keyframes.size(); i++)
		{
			//ofDrawCircle(midLineX + playerRect.width * keyframes.at(i).time, midLineY, 10);
			int x1 = playerRect.x + playerRect.width * keyframes.at(i).time - 10;
			int y1 = playerRect.y + playerRect.height / 2 - 10;
			int x2 = x1 + 20;
			int y2 = y1 + 20;
			if (ofRectangle(x1, y1, x2, y2).inside(ofGetMouseX(), ofGetMouseY()))
			{
				keyframes.erase(keyframes.begin() + i);
			}
		}
	}
}

void animationPanel::mouseDragged(ofMouseEventArgs& args)
{
	if (playerRect.inside(args.x, args.y) && !isPlaying)
	{
		cursorPos = (args.x - playerRect.x) / playerRect.width;

		animateObject();
	}
}

void animationPanel::setObject(object& obj)
{
	m_obj = &obj;
}

void animationPanel::addKeyFrame(object& obj)
{
	if (isRecording)
	{
		// Sort the keyframes by their time
		std::sort(keyframes.begin(), keyframes.end(),
			[](const keyframe& key1, const keyframe& key2)
			{
				return (key1.time < key2.time);
			}
		);

		for (size_t i = 0; i < keyframes.size(); i++)
		{
			if (abs(cursorPos - keyframes.at(i).time) <= 0.001f)
			{
				keyframes.at(i).position = glm::vec3(obj.getPosition());
				keyframes.at(i).rotation = glm::vec3(obj.getOrientationEuler());
				keyframes.at(i).scale = glm::vec3(obj.getScale());
				return;
			}
		}

		keyframes.push_back(keyframe(glm::vec3(obj.getPosition()), glm::vec3(obj.getOrientationEuler()), glm::vec3(obj.getScale()), cursorPos));
	}
}

void animationPanel::save()
{
	m_obj->keyframes = std::vector<keyframe>(keyframes);

	// Reset everything upon saving
	keyframes.clear();
	isPlaying = false;
	isRecording = false;
}

void animationPanel::load()
{
	keyframes = std::vector<keyframe>(m_obj->keyframes);
}

void animationPanel::drawPlayer()
{
	playerRect.x = rect.x + 15;
	playerRect.y = rect.y + 40;
	playerRect.width = rect.width - 30;
	playerRect.height = rect.height - 50;

	ofPushStyle();
	if (isRecording || isPlaying)
	{
		if (isRecording)
		{
			ofSetColor(ofColor(255, 0, 0, 50));
		}
		else if (isPlaying)
		{
			ofColor color = mainTheme::color3();
			color.a = 50;
			ofSetColor(color);
		}
		ofDrawRectRounded(playerRect.x - 10, playerRect.y + 20, playerRect.width + 20, playerRect.height - 30, 8);
	}

	ofSetLineWidth(2);
	ofSetColor(mainTheme::panelButtonHoverColor());

	// Mid line
	int midLineX = playerRect.x;
	int midLineY = playerRect.y + playerRect.height / 2;
	ofDrawLine(midLineX, midLineY, midLineX + playerRect.width, midLineY);

	float step = playerRect.width * 0.1;
	for (size_t i = 0; i <= maxSeconds; i++)
	{
		int height = 10;
		if (i % 5 == 0)
		{
			height = 20;
			drawText(midLineX + (i * step) - 5, midLineY + height + 12, ofToString(i), 10);
		}
		ofDrawLine(midLineX + (i * step), midLineY - height, midLineX + (i * step), midLineY + height);
	}

	if (isPlaying)
	{
		timer += ofGetLastFrameTime();
		cursorPos = timer / maxSeconds;

		if (cursorPos >= 1)
		{
			timer = 0;
		}
		else
		{
			animateObject();
		}
	}

	// Cursor
	ofSetColor(isRecording ? ofColor::red : mainTheme::color3());
	float cursorX = midLineX + playerRect.width * cursorPos;
	ofDrawLine(cursorX, midLineY - 20, cursorX, midLineY + 20);

	drawText(cursorX - 5, midLineY - 25, ofToString(cursorPos * maxSeconds).substr(0, 4), 10);

	// keyframes
	for (size_t i = 0; i < keyframes.size(); i++)
	{
		ofSetColor(ofColor::green);
		ofDrawCircle(midLineX + playerRect.width * keyframes.at(i).time, midLineY, 10);
	}

	ofPopStyle();
}

void animationPanel::animateObject()
{
	if (keyframes.size() <= 0)
	{
		return;
	}

	for (size_t i = 0; i < keyframes.size() - 1; i++)
	{
		if (cursorPos >= keyframes.at(i).time && cursorPos <= keyframes.at(i+1).time)
		{
			float max = keyframes.at(i + 1).time;
			float min = keyframes.at(i).time;
			float time = (cursorPos - min) / (max - min);
			time = CLAMP(time, 0, 1);

			glm::vec3 startPos = keyframes.at(i).position;
			glm::vec3 endPos = keyframes.at(i + 1).position;
			float px = ofLerp(startPos.x, endPos.x, time);
			float py = ofLerp(startPos.y, endPos.y, time);
			float pz = ofLerp(startPos.z, endPos.z, time);
			m_obj->setPosition(px, py, pz);

			glm::vec3 startRot = keyframes.at(i).rotation;
			glm::vec3 endRot = keyframes.at(i + 1).rotation;
			float rx = ofLerp(startRot.x, endRot.x, time);
			float ry = ofLerp(startRot.y, endRot.y, time);
			float rz = ofLerp(startRot.z, endRot.z, time);
			m_obj->setOrientation(glm::vec3(rx, ry, rz));

			glm::vec3 startScale = keyframes.at(i).scale;
			glm::vec3 endScale = keyframes.at(i + 1).scale;
			float sx = ofLerp(startScale.x, endScale.x, time);
			float sy = ofLerp(startScale.y, endScale.y, time);
			float sz = ofLerp(startScale.z, endScale.z, time);
			m_obj->setScale(sx, sy, sz);
		}
	}
}
