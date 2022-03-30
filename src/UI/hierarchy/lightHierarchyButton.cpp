#include "lightHierarchyButton.h"
#include "scene.h"
#include "light.h"

lightHierarchyButton::lightHierarchyButton(object& obj, std::string path, std::string label, bool isSecondary) : hierarchyButton(obj, path, label),
	addLightButton(new hierarchySmallButton("images/icons/add_camera.png")),
	secondary(isSecondary)
{
	addLightButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		scene& s = s.getInstance();
		s.addLight();
	});

	deleteButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
	{
		obj.markedForDeletion = true;
		scene& s = s.getInstance();
		light& l = dynamic_cast<light&>(obj);
		s.removeLight(l.id);
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

void lightHierarchyButton::setIcon(string path)
{
	int w = icon.getWidth();
	int h = icon.getHeight();
	icon.clear();
	icon.load(path);
	icon.resize(w, h);
}

void lightHierarchyButton::setLabel(string label)
{
	m_text = label;
}
