#include "panel.h"
#include "ofMain.h"
#include "mainTheme.h"

void drawPanel(int x, int y, int width, int height)
{
	ofPushStyle();
	ofFill();

	ofSetColor(mainTheme::panelBorderColor());
	ofDrawRectRounded(x - 2, y - 2, width + 4, height + 4, 8);

	ofSetColor(mainTheme::panelColor());
	ofDrawRectRounded(x, y, width, height, 6);

	ofPopStyle();
}

void drawPanel(ofRectangle& rect)
{
	drawPanel(rect.x, rect.y, rect.width, rect.height);
}
