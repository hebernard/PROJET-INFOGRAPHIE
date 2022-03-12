#include "cameraProperties.h"
#include "panel.h"
#include "label.h"
#include "hierarchySmallButton.h"

cameraProperties::cameraProperties() : backButton(new hierarchySmallButton("images/icons/back.png"))
{
	rect.width = 300;
	rect.y = 100;
}

void cameraProperties::draw()
{
	rect.height = ofGetHeight() - 125;
	rect.x = ofGetWidth() - rect.width - 20;

	drawPanel(rect);

	drawText(rect.x + 60, rect.y + 32, "Camera", 14);

	backButton->update(rect.x + 15, rect.y + 10);
	backButton->draw();
}
