#pragma once

#include "objects/object.h"
#include "UI/properties/centeredSlider.h"
#include "UI/properties/sliders/sliderProperty.h"
#include "ui/menuBar/menuBarButton.h"
#include "ofVboMesh.h"

//--------------------------------------------------------------
//-------------------  Bezier Surface  -------------------------
//--------------------------------------------------------------

class bezierSurface : public object
{
public:

	bezierSurface();
	~bezierSurface();

	void customDraw();
	void drawOutlines();
	void drawProperties(int x, int y, int width, int originX = 0, int originY = 0);

	void reset();
	void random();
	void resetSurface();
	void findPoint(int mouseX, int mouseY);

	//---  Bezier  -------------------------------------------------

	void createSurface();
	vector< vector<ofVec3f> > calculateSurface(vector< vector<ofVec3f> > inp, vector< vector<ofVec3f> > outp, int dimensionx, int dimensiony, int resolutionx, int resolutiony);
	double bezierBlend(int k, double mu, int n);

	//---  Bezier Surface Parameters  ------------------------------

	float surfaceWidth = 2;
	float surfaceHeight = 2;
	int minDimension = 2;
	int maxDimension = 10;
	int surfaceResolution = 4;
	int surfaceDimension = surfaceResolution - 1;

	ofColor outlineColor = 150;
	ofColor surfaceColor = 255;
	ofColor selectedColor = ofColor(255, 100, 100);
	ofColor controlPointsColor = ofColor(0, 0, 200);

	ofVboMesh surface;
	vector< vector<ofVec3f> > inputs;
	vector< vector<ofVec3f> > outputs;
	float controlPointsRadius = 0.05;
	glm::vec3 trans;
	vector<ofPoint> selectedPoints;

	bool drawSurface = true;
	bool drawOutline = true;

	//---  Others  -----------------------------------------------

	ofImage image;
	ofTexture texture;

	//---  Properties  -------------------------------------------

	checkBoxProperty surfaceVisibilityCheckbox;
	sliderProperty surfaceWidthSlider;
	sliderProperty surfaceHeightSlider;
	colorProperty surfaceColorProperty;
	colorProperty outlineColorProperty;

	checkBoxProperty outlineVisibilityCheckbox;
	inputProperty ctrlPointsRadiusInput;

	centeredSlider selectedPointsSlider;

	menuBarButton resetButton, randomButton;

};

