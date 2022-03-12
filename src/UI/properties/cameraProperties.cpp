#include "cameraProperties.h"
#include "panel.h"
#include "label.h"
#include "hierarchySmallButton.h"

cameraProperties::cameraProperties() : 
	backButton(new hierarchySmallButton("images/icons/back.png")),
	perspective(cameraPropertiesButton("3D\nPerspective", "images/icons/projection.png")),
	orthogonal(cameraPropertiesButton("2D\nOrthogonal", "images/icons/projection.png"))
{
	rect.width = 300;
	rect.y = 100;

	buttonWidth = (rect.width - (offset * 3)) / 2;
}

void cameraProperties::draw()
{
	rect.height = ofGetHeight() - 125;
	rect.x = ofGetWidth() - rect.width - 20;

	drawPanel(rect);

	drawText(rect.x + 60, rect.y + 32, "Camera", 14);

	backButton->update(rect.x + 15, rect.y + 10);
	backButton->draw();

	perspective.draw(rect.x + offset, rect.y + 100, buttonWidth);
	orthogonal.draw(rect.x + offset + buttonWidth + offset, rect.y + 100, buttonWidth);
	drawText(rect.x + offset, perspective.getY() - 13, "Projection", 12);
}
