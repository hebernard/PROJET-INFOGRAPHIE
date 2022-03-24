#include "lightHierarchyButton.h"
#include "scene.h"

lightHierarchyButton::lightHierarchyButton(object& obj, std::string path, std::string label, bool isSecondary) : hierarchyButton(obj, path, label),
	addLightButton(new hierarchySmallButton("images/icons/add_camera.png")),
	secondary(isSecondary)
{
	// todo: visible button enables/disables light
	// todo: change text/icon based on light type?

	addLightButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		scene& s = s.getInstance();
		s.addLight(true);
	});

	deleteButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		obj.markedForDeletion = true;
		scene& s = s.getInstance();
		s.removeLight();
	});
}

lightHierarchyButton::~lightHierarchyButton()
{
	delete addLightButton;
}

void lightHierarchyButton::update(int x, int y)
{
	ofxDatGuiComponent::update();
	setPosition(x, y);

	int posX = x + getWidth() - (secondary ? deleteButton->getWidth() : propertiesButton->getWidth()) - 30;
	int posY = y + getHeight() / 2 - (secondary ? deleteButton->getWidth() : propertiesButton->getHeight()) / 2;

	if (secondary)
	{
		deleteButton->update(posX, posY);
		posX -= deleteButton->getWidth();
	}

	propertiesButton->update(posX, posY);
	posX -= propertiesButton->getWidth();

	if (!secondary)
	{
		addLightButton->update(posX, posY);
		posX -= addLightButton->getWidth();
	}

	visibleButton->update(posX, posY);
}

void lightHierarchyButton::draw()
{
	drawMain();

	visibleButton->draw();
	propertiesButton->draw();

	if (secondary)
	{
		deleteButton->draw();
	}
	else
	{
		addLightButton->draw();
	}
}
