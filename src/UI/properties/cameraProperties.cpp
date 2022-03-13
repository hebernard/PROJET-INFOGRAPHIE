#include "cameraProperties.h"
#include "panel.h"
#include "label.h"
#include "hierarchySmallButton.h"
#include "utils.h"
#include "scene.h"
#include "mainTheme.h"


cameraProperties::cameraProperties() : 
	backButton(new hierarchySmallButton("images/icons/back.png")),
	perspective(cameraPropertiesButton("3D\nPerspective", "images/icons/projection.png", false, 0)),
	orthogonal(cameraPropertiesButton("2D\nOrthogonal", "images/icons/projection.png", false, 0)),
	exportImage(cameraPropertiesButton("Image\nExport", "images/icons/image.png", false, 0)),
	exportSeqImage(cameraPropertiesButton("Image seq.\nExport", "images/icons/gallery.png", false, 0)),
	backgroundDefault(cameraPropertiesButton("Default\nColor", "images/icons/image.png", true, 1)),
	backgroundCustom(cameraPropertiesButton("Custom\nColor", "images/icons/image.png", false, 1)),
	backgroundPicker(mainTheme::sceneCustomBackgroundColor),
	showGrid(cameraPropertiesButton("Show\nGrid", "images/icons/eye.png", false, 0)),
	hideGrid(cameraPropertiesButton("Hide\nGrid", "images/icons/no_eye.png", false, 0))
{
	rect.width = 300;
	rect.y = 100;

	perspective.setSelected();
	exportImage.setSelected();
	backgroundDefault.setSelected();
	showGrid.setSelected();

	buttonWidth = (rect.width - (offset * 3)) / 2;
}

void cameraProperties::draw()
{
	scene& s = s.getInstance();
	rect.height = ofGetHeight() - 125;
	rect.x = ofGetWidth() - rect.width - 20;

	drawPanel(rect);

	drawText(rect.x + 60, rect.y + 32, "Camera", 14);
	backButton->update(rect.x + 15, rect.y + 10);
	backButton->draw();


	//Export
	exportImage.draw(rect.x + offset, rect.y + 100, buttonWidth);
	exportSeqImage.draw(rect.x + offset + buttonWidth + offset, rect.y + 100, buttonWidth);

	if (exportImage.isInside() && utils::mouseReleased) {
		exportImage.setSelected();
		exportSeqImage.setUnselected();
	}
	if (exportSeqImage.isInside() && utils::mouseReleased) {
		exportSeqImage.setSelected();
		exportImage.setUnselected();
	}

	drawText(rect.x + offset, exportImage.getY() - 13, "Export", 12);

	//Projection
	perspective.draw(rect.x + offset, rect.y + 250, buttonWidth);
	orthogonal.draw(rect.x + offset + buttonWidth + offset, rect.y + 250, buttonWidth);

	if (perspective.isInside() && utils::mouseReleased) {
		perspective.setSelected();
		orthogonal.setUnselected();
		s.disableCamerasOrtho();
	}
	if (orthogonal.isInside() && utils::mouseReleased) {
		orthogonal.setSelected();
		perspective.setUnselected();
		s.enableCamerasOrtho();
	}

	drawText(rect.x + offset, perspective.getY() - 13, "Projection", 12);

	//Background Color
	backgroundDefault.draw(rect.x + offset, rect.y + 400, buttonWidth);
	backgroundCustom.draw(rect.x + offset + buttonWidth + offset, rect.y + 400, buttonWidth);

	if (backgroundDefault.isInside() && utils::mouseReleased) {
		backgroundDefault.setSelected();
		backgroundCustom.setUnselected();
		mainTheme::isDefaultBackground = true;
		ofSetBackgroundColor(mainTheme::sceneDefaultBackgroundColor());
		backgroundPicker.show = false;
	}
	if (backgroundCustom.isInside() && utils::mouseReleased) {
		backgroundCustom.setSelected();
		backgroundDefault.setUnselected();
		mainTheme::isDefaultBackground = false;
		backgroundPicker.show = true;
	}

	backgroundPicker.draw(rect.x + 80, backgroundCustom.getY());
	if (backgroundCustom.isSelected)
	{
		ofSetBackgroundColor(mainTheme::sceneCustomBackgroundColor);
	}

	drawText(rect.x + offset, backgroundDefault.getY() - 13, "Background Color", 12);

	//Grid Toggle
	showGrid.draw(rect.x + offset, rect.y + 550, buttonWidth);
	hideGrid.draw(rect.x + offset + buttonWidth + offset, rect.y + 550, buttonWidth);

	if (showGrid.isInside() && utils::mouseReleased) {
		showGrid.setSelected();
		hideGrid.setUnselected();
		s.gridIsVisible = true;
	}
	if (hideGrid.isInside() && utils::mouseReleased) {
		hideGrid.setSelected();
		showGrid.setUnselected();
		s.gridIsVisible = false;
	}

	drawText(rect.x + offset, showGrid.getY() - 13, "Grid (Hide/Show)", 12);
}
