#include "panel.h"
#include "ofMain.h"

void drawPanel(int x, int y, int width, int height, ofColor backgroundColor)
{
	ofPushStyle();
	ofFill();

	ofSetColor(mainTheme::panelBorderColor());
	ofDrawRectRounded(x - 2, y - 2, width + 4, height + 4, 8);

	ofSetColor(backgroundColor);
	ofDrawRectRounded(x, y, width, height, 6);

	ofPopStyle();
}

void drawPanel(ofRectangle& rect, ofColor backgroundColor)
{
	drawPanel(rect.x, rect.y, rect.width, rect.height, backgroundColor);
}
