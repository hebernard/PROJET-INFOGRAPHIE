#pragma once

#include "objects/object.h"
#include "UI/properties/centeredSlider.h"
#include "UI/properties/sliders/sliderProperty.h"

//--------------------------------------------------------------
//-------------------  Bezier Curve  ---------------------------
//--------------------------------------------------------------

class bezierCurve : public object
{
public:

	bezierCurve();
	~bezierCurve();

	void customDraw();
	void drawProperties(int x, int y, int width, int originX = 0, int originY = 0);

	void calculateBezier();
	int combinations(int n, int k);

	void setCurveResolution(int resolution);

	void addCtrlPoint();
	void deleteCtrlPoint();
	void resetCtrlPoints();

private :

	//Ref
	ofVec3f position;

	//Curve line
	bool curveIsVisible = true;
	float curveWidth = 1.0f;
	int curveResolution = 100;
	ofColor curveColor = ofColor(0, 255, 0);
	int curveDistance = 5;
	ofPolyline curveRenderer;

	inputProperty curveWidthInput;
	sliderProperty curveResolutionSlider;
	colorProperty curveColorProperty;

	//Curve outline & Properties
	bool outlineIsVisible = true;
	float outlineWidth = 0.5f;
	ofColor outlineColor = ofColor(50);

	checkBoxProperty outlineVisibilityCheckbox;
	inputProperty outlineWidthInput;
	colorProperty outlineColorProperty;

	//Control Points
	bool ctrlPointsAreVisible = true;
	float ctrlPointsRadius = 0.1;
	ofColor ctrlPointsColor = ofColor(255, 0, 0);

	inputProperty ctrlPointsRadiusInput;

	int nbCtrlPoints = 3;
	int maxControlPoints = 12;
	int selectedIndex = 1;

	centeredSlider selectedPointSlider;

	ofVec3f* selectedControlPoint;
	std::vector<ofVec3f> controlPoints;
};

