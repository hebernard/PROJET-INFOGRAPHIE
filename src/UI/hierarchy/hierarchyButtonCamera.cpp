#include "hierarchyButtonCamera.h"
#include "UI/label.h"
#include "camera.h"
#include "scene.h"
#include "hierarchySmallButton.h"
#include "cursor.h"

hierarchyButtonCamera::hierarchyButtonCamera(camera& cam, std::string iconPath, std::string text) :
	ofxDatGuiButton("hierarchyButtonCamera"),
	m_text(text),
	icon(),
	m_cam(cam),
	propertiesButton(new hierarchySmallButton("images/icons/properties.png"))
{
	icon.load(iconPath);
	icon.resize(24, 24);
	setTheme(new hierarchyButtonCameraTheme());

	textSize = label::getSize(text, 11, mainTheme::fontRegularPath);

	onButtonEvent(this, &hierarchyButtonCamera::onClick);

	propertiesButton->onButtonEvent([&](ofxDatGuiButtonEvent e)
		{
			//cam.propertiesOpened = true;
		});
}

void hierarchyButtonCamera::setTheme(const ofxDatGuiTheme* theme)
{
	setComponentStyle(theme);
	ofxDatGuiComponent::setWidth(theme->layout.width, theme->layout.labelWidth);
}

void hierarchyButtonCamera::onClick(ofxDatGuiButtonEvent e)
{
	m_cam.reset();
}

void hierarchyButtonCamera::draw()
{
	ofPushStyle();
	ofFill();

	if (mMouseOver)
	{
		cursor::setResetCursor();
		ofSetColor(mainTheme::panelButtonHoverColor());
		ofDrawRectangle(x - 2, y, getWidth() + 4, getHeight());
	}

	if (icon.isAllocated())
	{
		ofSetColor(ofColor::white);
		icon.draw(x + 30, y + getHeight() / 2 - icon.getHeight() / 2);
	}

	drawText(x + icon.getWidth() + 25 * 2, y + getHeight() / 2 + textSize.y / 2, m_text, 11, mainTheme::fontColor(), mainTheme::fontRegularPath);

	propertiesButton->draw();
	ofPopStyle();
}

void hierarchyButtonCamera::update(int x, int y)
{
	ofxDatGuiComponent::update();
	setPosition(x, y);

	int posX = x + getWidth() - deleteButton->getWidth() - 30;
	int posY = y + getHeight() / 2 - deleteButton->getHeight() / 2;
	deleteButton->update(posX, posY);

	posX -= deleteButton->getWidth();
	propertiesButton->update(posX, posY);

	posX -= propertiesButton->getWidth();
	visibleButton->update(posX, posY);
}

std::string hierarchyButtonCamera::getLabel()
{
	return m_text;
}
