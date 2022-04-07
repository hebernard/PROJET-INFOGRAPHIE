#pragma once

#include "objects/object.h"

//--------------------------------------------------------------
//-------------------  Bezier Curve  ---------------------------
//--------------------------------------------------------------

class bezierCurve : public object
{
public:

	bezierCurve();
	~bezierCurve();

	void customDraw();
	//glm::vec3 getBBox();
	void drawProperties(int x, int y, int width);

	void calculateBezier();
	int combinations(int n, int k);

	void setCurveResolution(int resolution);

	void addCtrlPoint();
	void deleteCtrlPoint();
	void resetCtrlPoints();

	void setSelected(int index);

private :

	//Ref
	int index;
	ofVec3f position;

	//Curve line
	bool curveIsVisible = true;
	float curveWidth = 1.0f;
	float curveResolution = 100;
	ofColor curveColor = ofColor(0, 255, 0);
	int curveDistance = 5;
	ofPolyline curveRenderer;

	inputProperty curveWidthInput;
	inputProperty curveResolutionInput;
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

	ofVec3f* selectedControlPoint;
	std::vector<ofVec3f> controlPoints;
};

