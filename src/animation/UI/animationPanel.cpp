#include "animationPanel.h"
#include "animation/keyframe.h"
#include "ui/panel.h"
#include "ui/label.h"
#include "ui/hierarchy/hierarchySmallButton.h"
#include "utils/utils.h"
#include "ui/properties/inputProperty.h"

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
		if (keyframes.size() > 0)
		{
			isRecording = false;
			isPlaying = !isPlaying;
			timer = keyframes.front().time * maxSeconds;
		}
	});

	maxSecondsInput = new inputProperty("Max time", maxSeconds);
	maxSecondsInput->maxCharacters = 3;
}

animationPanel::~animationPanel()
{
	delete playButton;
	delete recordButton;
	delete maxSecondsInput;
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

	//maxSecondsInput->draw(rect.x + rect.width - 150, rect.y + 10, 140, 15);

	drawPlayer();

	if (utils::rightMouseReleased && !isPlaying)
	{
		for (size_t i = 0; i < keyframes.size(); i++)
		{
			int x1 = playerRect.x + playerRect.width * (keyframes.at(i).time / maxSeconds) - 10;
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
		cursorPos = (args.x - playerRect.x) / playerRect.width * maxSeconds;

		animateObject();
	}
}

void animationPanel::mouseScrolled(ofMouseEventArgs& args)
{
	if (playerRect.inside(args.x, args.y))
	{
		maxSeconds -= args.scrollY;
		if (keyframes.size() >= 1)
		{
			maxSeconds = CLAMP(maxSeconds, ceil(keyframes.at(keyframes.size() - 1).time), 100);
		}
		else
		{
			maxSeconds = CLAMP(maxSeconds, 1, 100);
		}

		if (cursorPos > maxSeconds)
		{
			cursorPos = maxSeconds;
		}

		maxSecondsInput->forceUpdateValue(999);
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
		for (size_t i = 0; i < keyframes.size(); i++)
		{
			// Update when modifying multiple values on the same keyframe
			if (abs(cursorPos - keyframes.at(i).time) <= 0.001f)
			{
				keyframes.at(i).position = glm::vec3(obj.getPosition());
				keyframes.at(i).rotation = glm::vec3(obj.getOrientationEuler());
				keyframes.at(i).scale = glm::vec3(obj.getScale());
				return;
			}
		}

		keyframes.push_back(keyframe(glm::vec3(obj.getPosition()), glm::vec3(obj.getOrientationEuler()), glm::vec3(obj.getScale()), cursorPos));

		// Sort the keyframes by their time
		std::sort(keyframes.begin(), keyframes.end(),
			[](const keyframe& key1, const keyframe& key2)
			{
				return (key1.time < key2.time);
			}
		);
	}
}

void animationPanel::save()
{
	m_obj->keyframes = std::vector<keyframe>(keyframes);
	m_obj->animationMaxTime = maxSeconds;

	// Reset everything upon saving
	keyframes.clear();
	isPlaying = false;
	isRecording = false;
}

void animationPanel::load()
{
	keyframes = std::vector<keyframe>(m_obj->keyframes);
	if (m_obj->animationMaxTime != 0)
	{
		maxSeconds = m_obj->animationMaxTime;
	}
	else
	{
		// just set to default value
		maxSeconds = 10;
	}

	maxSecondsInput->forceUpdateValue(999);
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

	float step = playerRect.width * (1 / maxSeconds);
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
		cursorPos = timer;

		if (cursorPos >= maxSeconds || cursorPos > keyframes.at(keyframes.size() - 1).time)
		{
			timer = keyframes.front().time;
		}
		else
		{
			animateObject();
		}
	}

	// Cursor
	ofSetColor(isRecording ? ofColor::red : mainTheme::color3());
	float cursorX = midLineX + playerRect.width * (cursorPos / maxSeconds);
	ofDrawLine(cursorX, midLineY - 20, cursorX, midLineY + 20);

	drawText(cursorX - 5, midLineY - 25, ofToString(cursorPos).substr(0, 4), 10);

	// keyframes
	for (size_t i = 0; i < keyframes.size(); i++)
	{
		ofSetColor(ofColor::green);
		float x = midLineX + playerRect.width * (keyframes.at(i).time / maxSeconds);
		ofDrawCircle(x, midLineY, 10);

		drawText(x - 5, midLineY + 25, ofToString(i + 1), 10);
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

void animationPanel::setMaxTime(float max)
{

}
