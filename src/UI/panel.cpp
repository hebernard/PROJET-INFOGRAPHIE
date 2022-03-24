#include "panel.h"
#include "ofMain.h"

void drawPanel(int x, int y, int width, int height, ofColor backgroundColor)
{
	ofPushStyle();
	ofFill();

	//ofSetColor(mainTheme::panelBorderColor());
	//ofDrawRectRounded(x - 2, y - 2, width + 4, height + 4, 8);

	ofSetColor(backgroundColor);
	ofDrawRectRounded(x, y, width, height, 8);

	ofPopStyle();
}

void drawPanel(ofRectangle& rect, ofColor backgroundColor)
{
	drawPanel(rect.x, rect.y, rect.width, rect.height, backgroundColor);
}

void drawInputPanel(int x, int y, int width, int height, bool hovered, bool focused)
{
	ofPushStyle();
	ofFill();

	if (focused)
	{
		ofSetColor(mainTheme::fontColor());
		ofDrawRectRounded(x - 1, y - 1, width + 2, height + 2, 14);
	}

	ofSetColor(hovered ? mainTheme::panelButtonHoverColor() : mainTheme::toolBarButtonHoverColor());
	ofDrawRectRounded(x, y, width, height, 14);
	ofPopStyle();
}

void drawInputPanel(const ofRectangle& rect, bool hovered, bool focused)
{
	drawInputPanel(rect.x, rect.y, rect.width, rect.height, hovered, focused);
}
