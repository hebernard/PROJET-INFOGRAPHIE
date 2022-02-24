#include "colorProperty.h"
#include "label.h"
#include "panel.h"
#include "utils.h"

colorProperty::colorProperty(std::string label, ofColor& ref) : m_label(label), m_ref(ref)
{
	textSize = label::getSize(label, 12);
	colorRect.height = 20;
	gradientRect.height = 200;
	pickerRect.height = gradientRect.height + 100;

	rainbow.load("ofxbraitsch/ofxdatgui/picker-rainbow.png");
	rainbow.resize(10, gradientRect.height);
	rainbowRect.width = rainbow.getWidth();
	rainbowRect.height = gradientRect.height;

	// setup the vbo that draws the main gradient
	gPoints.push_back(ofVec2f(0, 0));
	gPoints.push_back(ofVec2f(0, 0));
	gPoints.push_back(ofVec2f(0, 0));
	gPoints.push_back(ofVec2f(0, 0));
	gPoints.push_back(ofVec2f(0, 0));
	gPoints.push_back(ofVec2f(0, 0));

	// center point of the gradient is 1/2 way between mColor & black
	ofColor center = ofColor(m_ref.r / 2, m_ref.g / 2, m_ref.b / 2);

	// draw main gradient as a six point triangle fan
	gColors.push_back(center);          // center
	gColors.push_back(ofColor::white);  // top-left
	gColors.push_back(m_ref);          // top-right
	gColors.push_back(ofColor::black);  // btm-right
	gColors.push_back(ofColor::black);  // btm-left
	gColors.push_back(ofColor::white);  // top-left
	vbo.setColorData(&gColors[0], 6, GL_DYNAMIC_DRAW);
}

void colorProperty::draw(int x, int y, int width)
{
	int mouseX = ofGetMouseX();
	int mouseY = ofGetMouseY();

	colorRect.x = x + textSize.x + 30;
	colorRect.y = y;
	colorRect.width = width - textSize.x - 30;

	drawText(x, y + textSize.y, m_label, 11);

	ofPushStyle();
	bool mouseInside = colorRect.inside(mouseX, mouseY);
	ofSetColor(m_ref);
	ofDrawRectRounded(colorRect, 20);

	if (utils::mousePressed)
	{
		if (mouseInside)
		{
			showPicker = !showPicker;
		}
		else if (!pickerRect.inside(mouseX, mouseY))
		{
			showPicker = false;
		}
	}

	if (showPicker)
	{
		utils::isMouseOverUI = true;

		drawPicker(colorRect.x, colorRect.y, colorRect.width);

		updateGradient(mouseX, mouseY);

		// Draw rainbow line
		ofSetColor(ofColor::white);
		ofDrawLine(rainbowRect.x, rainbowLine, rainbowRect.x + rainbowRect.width, rainbowLine);

		// Draw gradient circle
		ofPushStyle();
		ofNoFill();
		ofDrawCircle(gradientPos, 10);
		ofPopStyle();
	}

	ofPopStyle();
}

void colorProperty::updateGradient(int mouseX, int mouseY)
{
	if (pickerRect.inside(mouseX, mouseY))
	{
		unsigned char p[3];
		int y = (mouseY - ofGetHeight()) * -1;
		glReadPixels(mouseX, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &p);
		gColor.r = int(p[0]);
		gColor.g = int(p[1]);
		gColor.b = int(p[2]);

		if (ofGetMousePressed())
		{
			if (rainbowRect.inside(mouseX, mouseY))
			{
				rainbowLine = mouseY;
				gColors[2] = gColor;
				gColors[0] = ofColor(gColor.r / 2, gColor.g / 2, gColor.b / 2);
				vbo.setColorData(&gColors[0], 6, GL_DYNAMIC_DRAW);
			}
			else if (gradientRect.inside(mouseX, mouseY))
			{
				gradientPos = glm::vec2(mouseX, mouseY);
				m_ref = gColor;
			}
		}
	}
}

int colorProperty::getHeight()
{
	return colorRect.getHeight();
}

void colorProperty::drawPicker(int x, int y, int width)
{
	rainbowRect.x = x - 310;
	if (y + pickerRect.height + 100 > ofGetHeight())
	{
		rainbowRect.y = ofGetHeight() - pickerRect.height - 100;
	}
	else
	{
		rainbowRect.y = y;
	}

	gradientRect.x = rainbowRect.x + rainbowRect.width;
	gradientRect.y = rainbowRect.y;
	gradientRect.width = width;

	pickerRect.x = rainbowRect.x;
	pickerRect.y = rainbowRect.y;
	pickerRect.width = rainbowRect.width + gradientRect.width;
	drawPanel(pickerRect.x - 10, pickerRect.y - 10, pickerRect.width + 20, pickerRect.height + 20);
	ofSetColor(ofColor::white);
	rainbow.draw(rainbowRect.x, rainbowRect.y);

	gPoints[0] = ofVec2f(gradientRect.x + gradientRect.width / 2, gradientRect.y + gradientRect.height / 2);
	gPoints[1] = ofVec2f(gradientRect.x, gradientRect.y);
	gPoints[2] = ofVec2f(gradientRect.x + gradientRect.width, gradientRect.y);
	gPoints[3] = ofVec2f(gradientRect.x + gradientRect.width, gradientRect.y + gradientRect.height);
	gPoints[4] = ofVec2f(gradientRect.x, gradientRect.y + gradientRect.height);
	gPoints[5] = ofVec2f(gradientRect.x, gradientRect.y);
	vbo.setVertexData(&gPoints[0], 6, GL_DYNAMIC_DRAW);
	vbo.draw(GL_TRIANGLE_FAN, 0, 6);
}
