#include "colorPicker.h"
#include "ui/label.h"
#include "ui/panel.h"
#include "utils/utils.h"

colorPicker::colorPicker(ofColor& ref) : m_ref(ref)
{
	gradientRect.height = 200;
	pickerRect.height = gradientRect.height + 100;
	rgbRect.width = 50;
	rgbRect.height = 25;
	hexRect.width = rgbRect.width;
	hexRect.height = rgbRect.height;
	hsbRect.width = rgbRect.width;
	hsbRect.height = rgbRect.height;
	gradientRect.width = 198;

	rainbow.load("ofxbraitsch/ofxdatgui/picker-rainbow.png");
	rainbow.resize(10, gradientRect.height);
	rainbowRect.width = rainbow.getWidth();
	rainbowRect.height = gradientRect.height;

	pickerRect.width = rainbowRect.width + gradientRect.width;

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

	rInput = new inputProperty("R", R);
	gInput = new inputProperty("G", G);
	bInput = new inputProperty("B", B);

	rInput->maxCharacters = 5;
	rInput->setMax(255);
	gInput->maxCharacters = 5;
	gInput->setMax(255);
	bInput->maxCharacters = 5;
	bInput->setMax(255);

	hInput = new inputProperty("H", H);
	sInput = new inputProperty("S", S);
	brInput = new inputProperty("B", Br);

	hInput->maxCharacters = 5;
	hInput->setMax(255);
	sInput->maxCharacters = 5;
	sInput->setMax(255);
	brInput->maxCharacters = 5;
	brInput->setMax(255);

	forceUpdate();
}

colorPicker::~colorPicker()
{
	delete rInput;
	delete gInput;
	delete bInput;
	delete hInput;
	delete sInput;
	delete brInput;
}

void colorPicker::draw(int x, int y)
{
	if (!show)
	{
		return;
	}

	int offset = 10;

	rainbowRect.x = x - pickerRect.width - offset * 2 - 10;
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

	pickerRect.x = rainbowRect.x;
	pickerRect.y = rainbowRect.y;
	drawPanel(pickerRect.x - offset, pickerRect.y - offset, pickerRect.width + offset * 2, pickerRect.height + offset * 2);
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

	if (pickerRect.inside(mouseX, mouseY))
	{
		utils::isMouseOverUI = true;
	}
	else if (utils::mousePressed)
	{
		show = false;
	}

	ofSetColor(mainTheme::toolBarButtonHoverColor());
	if (rgbRect.inside(mouseX, mouseY) || currentMode == ColorMode::RGB)
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

	if (hsbRect.inside(mouseX, mouseY) || currentMode == ColorMode::HSB)
	{
		ofDrawRectRounded(hsbRect, 20);
		if (utils::mousePressed)
		{
			currentMode = ColorMode::HSB;
			H = m_ref.getHue();
			S = m_ref.getSaturation();
			Br = m_ref.getBrightness();

			hInput->forceUpdateValue();
			sInput->forceUpdateValue();
			brInput->forceUpdateValue();
		}
	}

	drawText(rgbRect.x + rgbRect.width / 2 - 12, rgbRect.y + rgbRect.height / 2 + 5, "RGB", 10);
	//drawText(hexRect.x + hexRect.width / 2 - 12, hexRect.y + hexRect.height / 2 + 5, "HEX", 10);
	drawText(hsbRect.x + hsbRect.width / 2 - 12, hsbRect.y + hsbRect.height / 2 + 5, "HSB", 10);

	switch (currentMode)
	{
	case ColorMode::RGB:
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
	case ColorMode::HSB:
		m_ref.setHsb(H, S, Br);

		hInput->draw(pickerRect.x, gradientRect.y + gradientRect.height + 20, 90, 5);
		sInput->draw(pickerRect.x + 72, gradientRect.y + gradientRect.height + 20, 90, 5);
		brInput->draw(pickerRect.x + 144, gradientRect.y + gradientRect.height + 20, 90, 5);
		break;
	}

	updateGradient();

	ofPushStyle();
	ofSetColor(ofColor::white);
	if (rainbowRect.inside(rainbowRect.x + 1, rainbowLine))
	{
		// Draw rainbow line
		ofDrawLine(rainbowRect.x, rainbowLine, rainbowRect.x + rainbowRect.width, rainbowLine);
	}

	if (gradientRect.inside(gradientPos))
	{
		// Draw gradient circle
		ofNoFill();
		ofDrawCircle(gradientPos, 10);
	}
	ofPopStyle();
}

void colorPicker::forceUpdate()
{
	// RGB
	R = m_ref.r;
	G = m_ref.g;
	B = m_ref.b;

	rInput->forceUpdateValue();
	gInput->forceUpdateValue();
	bInput->forceUpdateValue();

	rInput->maxCharacters = 5;
	gInput->maxCharacters = 5;
	bInput->maxCharacters = 5;

	// HSB
	H = m_ref.getHue();
	S = m_ref.getSaturation();
	B = m_ref.getBrightness();

	hInput->forceUpdateValue();
	sInput->forceUpdateValue();
	brInput->forceUpdateValue();
}

void colorPicker::updateGradient()
{
	int mouseX = ofGetMouseX();
	int mouseY = ofGetMouseY();

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
				case ColorMode::RGB:
					R = gColor.r;
					G = gColor.g;
					B = gColor.b;

					rInput->forceUpdateValue();
					gInput->forceUpdateValue();
					bInput->forceUpdateValue();
					break;
					/*case HEX:
						hex = gColor.getHex();
						break;*/
				case ColorMode::HSB:
					H = gColor.getHue();
					S = gColor.getSaturation();
					Br = gColor.getBrightness();

					hInput->forceUpdateValue();
					sInput->forceUpdateValue();
					brInput->forceUpdateValue();
					break;
				}
			}
		}
	}
}
