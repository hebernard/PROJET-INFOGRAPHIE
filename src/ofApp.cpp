#include "ofApp.h"

void ofApp::setup()
{
	/*csl = new console("Console");

	ofxDatGui* import = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
	ofxDatGuiFolder* importFolder = import->addFolder("Importer", ofColor::yellow);
	ofxDatGuiButton* importButton = importFolder->addButton("Importer une image");
	importButton->onButtonEvent(this, &ofApp::onImportButtonClicked);*/

	d = new dock();
}

void ofApp::onImportButtonClicked(ofxDatGuiButtonEvent e)
{
	ofFileDialogResult openFileResult = ofSystemLoadDialog("Choisir une image JPG ou PNG");

	if (openFileResult.bSuccess)
	{
		processOpenFileSelection(openFileResult);
	}
	else
	{
		//csl->log("Une erreur est survenue, veillez reessayer", ofLogLevel::OF_LOG_ERROR);
	}
}

void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult)
{
	ofFile file(openFileResult.getPath());

	if (file.exists())
	{
		string fileExtension = ofToUpper(file.getExtension());

		if (fileExtension == "JPG" || fileExtension == "PNG")
		{
			image.load(openFileResult.getPath());
			//csl->log("Load " + file.getFileName());
			if (image.getWidth() > ofGetWidth() || image.getHeight() > ofGetHeight())
			{
				image.resize(image.getWidth() / 2, image.getHeight() / 2);
			}
		}
		else
		{
			//csl->log("Mauvais format, veillez choisir JPG ou PNG", ofLogLevel::OF_LOG_ERROR);
		}
	}

}

//--------------------------------------------------------------
void ofApp::update()
{
	d->update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	if (image.isAllocated())
	{
		image.draw(0, 0);
	}

	d->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
