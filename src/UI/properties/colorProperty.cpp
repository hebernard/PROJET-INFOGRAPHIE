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
	rgbRect.width = 50;
	rgbRect.height = 25;
	hexRect.width = rgbRect.width;
	hexRect.height = rgbRect.height;
	hsbRect.width = rgbRect.width;
	hsbRect.height = rgbRect.height;

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

	// RGB
	rInput = new inputProperty("R", R);
	gInput = new inputProperty("G", G);
	bInput = new inputProperty("B", B);

	rInput->maxCharacters = 5;
	gInput->maxCharacters = 5;
	bInput->maxCharacters = 5;

	// HSV
	hInput = new inputProperty("H", H);
	sInput = new inputProperty("S", S);
	brInput = new inputProperty("B", Br);

	hInput->maxCharacters = 5;
	sInput->maxCharacters = 5;
	brInput->maxCharacters = 5;
}

colorProperty::~colorProperty()
{
	delete rInput;
	delete gInput;
	delete bInput;
	delete hInput;
	delete sInput;
	delete brInput;
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

				switch (currentMode)
				{
				case RGB:
					R = gColor.r;
					G = gColor.g;
					B = gColor.b;

					rInput->forceUpdateValue(255);
					gInput->forceUpdateValue(255);
					bInput->forceUpdateValue(255);
					break;
				/*case HEX:
					hex = gColor.getHex();
					break;*/
				case HSB:
					H = gColor.getHue();
					S = gColor.getSaturation();
					Br = gColor.getBrightness();

					hInput->forceUpdateValue(255);
					sInput->forceUpdateValue(255);
					brInput->forceUpdateValue(255);
					break;
				}
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

	rgbRect.x = pickerRect.x + pickerRect.width / 4 - rgbRect.width / 2;
	rgbRect.y = pickerRect.y + pickerRect.height - 30;
	hexRect.x = pickerRect.x + pickerRect.width / 2 - hexRect.width / 2;
	hexRect.y = rgbRect.y;
	hsbRect.x = pickerRect.x + pickerRect.width / 2 + hsbRect.width / 2;
	hsbRect.y = rgbRect.y;

	int mouseX = ofGetMouseX();
	int mouseY = ofGetMouseY();

	ofSetColor(mainTheme::toolBarButtonHoverColor());
	if (rgbRect.inside(mouseX, mouseY) || currentMode == 0)
	{
		ofDrawRectRounded(rgbRect, 20);
		if (utils::mousePressed)
		{
			currentMode = ColorMode::RGB;
		}
	}

	/*if (hexRect.inside(mouseX, mouseY) || currentMode == 1)
	{
		ofDrawRectRounded(hexRect, 20);
		if (utils::mousePressed)
		{
			currentMode = ColorMode::HEX;
		}
	}*/

	if (hsbRect.inside(mouseX, mouseY) || currentMode == 2)
	{
		ofDrawRectRounded(hsbRect, 20);
		if (utils::mousePressed)
		{
			currentMode = ColorMode::HSB;
			H = m_ref.getHue();
			S = m_ref.getSaturation();
			Br = m_ref.getBrightness();

			hInput->forceUpdateValue(255);
			sInput->forceUpdateValue(255);
			brInput->forceUpdateValue(255);
		}
	}

	drawText(rgbRect.x + rgbRect.width / 2 - 12, rgbRect.y + rgbRect.height / 2 + 5, "RGB", 10);
	//drawText(hexRect.x + hexRect.width / 2 - 12, hexRect.y + hexRect.height / 2 + 5, "HEX", 10);
	drawText(hsbRect.x + hsbRect.width / 2 - 12, hsbRect.y + hsbRect.height / 2 + 5, "HSB", 10);

	switch (currentMode)
	{
	case RGB:
		m_ref.r = R;
		m_ref.g = G;
		m_ref.b = B;

		rInput->draw(pickerRect.x, gradientRect.y + gradientRect.height + 20, 90, 5);
		gInput->draw(pickerRect.x + 72, gradientRect.y + gradientRect.height + 20, 90, 5);
		bInput->draw(pickerRect.x + 144, gradientRect.y + gradientRect.height + 20, 90, 5);
		break;
	/*case HEX:
		m_ref = ofColor::fromHex(stoi("0x" + hex.substr(0, 4) + "00"));
		break;*/
	case HSB:
		m_ref.setHsb(H, S, Br);

		hInput->draw(pickerRect.x, gradientRect.y + gradientRect.height + 20, 90, 5);
		sInput->draw(pickerRect.x + 72, gradientRect.y + gradientRect.height + 20, 90, 5);
		brInput->draw(pickerRect.x + 144, gradientRect.y + gradientRect.height + 20, 90, 5);
		break;
	}
}
