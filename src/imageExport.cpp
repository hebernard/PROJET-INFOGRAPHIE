#include "imageExport.h"

void imageExport::exportImages()
{
	ofFileDialogResult openFileResult = ofSystemSaveDialog("Image", "Choisir un répertoire pour exporter");

	if (openFileResult.bSuccess) {
		ofSaveScreen(openFileResult.getPath());
	}
}

void imageExport::exportSeqImages()
{
	openFileResult = ofSystemLoadDialog("Choisir un répertoire pour exporter", true);
	isRunning = true;
}

void imageExport::updateTimer() {

	if (isRunning) {
		timer += ofGetLastFrameTime();
		index += 1;
		if (openFileResult.bSuccess) {
			ofImage img;
			img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
			std::string path = openFileResult.getPath();
			path.append("/" + ofToString(index) + ".jpg");
			std::cout << path << std::endl;
			img.save(path);
			//ofSaveScreen(path);
		}
		if (timer >= 10) {
			isRunning = false;
			timer = 0;
			index = 0;
		}
	}
}