#include "bezierCurve.h"
#include "camera.h"
#include "scene.h"
#include "utils/utils.h"

//-------------------------------------------------------------=
//-------------------  Bezier Curve ---------------------------=
//-------------------------------------------------------------=

bezierCurve::bezierCurve() 
	: object(new hierarchyButton(*this, "images/icons/curve.png", "Curve")),
	curveWidthInput("Curve Thickness", curveWidth),
	curveResolutionSlider("Curve Resolution", curveResolution, 3, 50, true),
	curveColorProperty("Curve Color", curveColor),
	outlineVisibilityCheckbox("Outline & Control Points", outlineIsVisible),
	outlineWidthInput("Outline Size", outlineWidth),
	outlineColorProperty("Outline Color", outlineColor),
	ctrlPointsRadiusInput("Control Points Size", ctrlPointsRadius),
	selectedPointSlider("Selected", false)
{

	canHaveMaterial = false;

	// curve vertices init
	for (int index = 0; index <= curveResolution; ++index)
		curveRenderer.addVertex(ofPoint());

	// control points init
	resetCtrlPoints();

	selectedPointSlider.onUpdate = [&](auto axis, float value) {
		selectedControlPoint->set(*selectedControlPoint + axis * value * ofGetLastFrameTime() * 2.0);
		calculateBezier();
	};

	selectedPointSlider.resetButton->buttonEventCallback = [&](auto e) {
		resetCtrlPoints();
	};

	curveResolutionSlider.onUpdate = [&](float value) {
		setCurveResolution(value);
		cout << "LOG" + ofToString(value) << endl;
	};
}

bezierCurve::~bezierCurve()
{
	controlPoints.clear();
	curveRenderer.clear();
}

void bezierCurve::customDraw()
{
	if (isSelected) {
		ofDisableDepthTest();
	}

	if (utils::keyPressed == OF_KEY_LEFT && isSelected && selectedIndex > 0) {
		selectedIndex--;
	}
	if (utils::keyPressed == OF_KEY_RIGHT && isSelected && selectedIndex < nbCtrlPoints - 1) {
		selectedIndex++;
	}
	if (utils::keyPressed == OF_KEY_UP && isSelected) {
		addCtrlPoint();
	}
	if (utils::keyPressed == OF_KEY_DOWN && isSelected) {
		deleteCtrlPoint();
	}

	selectedControlPoint = &controlPoints[selectedIndex];

	// draw outline
	if (outlineIsVisible && isSelected) {

		ofSetColor(outlineColor);
		ofSetLineWidth(outlineWidth);
		for (int index = 0; index < nbCtrlPoints - 1; ++index) {
			ofDrawLine(controlPoints.at(index), controlPoints.at(index + 1));
		}

	}

	// draw curve
	if (curveIsVisible) {

		ofSetColor(curveColor);
		ofSetLineWidth(curveWidth);
		curveRenderer.draw();

	}

	// draw control point
	if (outlineIsVisible && isSelected) {

		ofSetColor(ctrlPointsColor);
		for (int index = 0; index < nbCtrlPoints; ++index) {
			if (index == nbCtrlPoints - 1 || index == 0) {
				ofDrawSphere(controlPoints.at(index), ctrlPointsRadius * 1.3);
			}
			else {
				ofDrawSphere(controlPoints.at(index), ctrlPointsRadius);
			}
		}
	}

	// draw selected point
	if (isSelected && outlineIsVisible) {
		ofSetColor(255, 155, 155);
		ofDrawSphere(selectedControlPoint->x, selectedControlPoint->y, selectedControlPoint->z, ctrlPointsRadius * 1.5);
	}


	if (isSelected) {
		ofEnableDepthTest();
	}

}

void bezierCurve::drawProperties(int x, int y, int width, int originX, int originY)
{

	int offset = y;
	curveColorProperty.draw(x, offset, width);
	offset += 10 + curveColorProperty.getHeight();
	curveWidthInput.draw(x, offset, width);
	offset += 10 + curveWidthInput.getHeight();
	curveResolutionSlider.draw(x, offset, width);

	offset += 10 + curveResolutionSlider.getHeight();
	outlineVisibilityCheckbox.draw(x, offset, width);
	offset += 10 + outlineVisibilityCheckbox.getHeight();
	outlineWidthInput.draw(x, offset, width);
	offset += 10 + outlineWidthInput.getHeight();
	outlineColorProperty.draw(x, offset, width);

	offset += 10 + outlineColorProperty.getHeight();
	ctrlPointsRadiusInput.draw(x, offset, width);

	selectedPointSlider.update();
	offset += 20 + ctrlPointsRadiusInput.getHeight();
	selectedPointSlider.draw(x, offset, width, *selectedControlPoint);
}

void bezierCurve::addCtrlPoint()
{
	if (nbCtrlPoints < maxControlPoints) {

		nbCtrlPoints++;
		resetCtrlPoints();
	}
}

void bezierCurve::deleteCtrlPoint()
{
	if (nbCtrlPoints > 3) {

		if (selectedIndex == nbCtrlPoints - 1) 
			selectedIndex--;
		
		nbCtrlPoints--;
		resetCtrlPoints();
	}
}

void bezierCurve::resetCtrlPoints()
{
	float distanceRatio = (float)curveDistance / (nbCtrlPoints - 1);
	float distance = 0.f - curveDistance / 2;

	controlPoints.clear();

	// initialisation des points de contrôles
	for (int index = 0; index < nbCtrlPoints; ++index) {

		if (index == 0 || index == nbCtrlPoints - 1) {
			controlPoints.push_back(ofPoint(distance, 0, 0));
		}
		else {
			controlPoints.push_back(ofPoint(distance, 1, 0));
		}

		distance += distanceRatio;
	}

	calculateBezier();
}

void bezierCurve::calculateBezier()
{
	for (int index = 0; index <= curveResolution; ++index) {

		float t = (index / (float)curveResolution);
		int n = controlPoints.size() - 1;

		ofVec3f position = ofVec3f(0);

		for (int k = 0; k <= n; k++)
		{
			position += combinations(n, k) * std::powf(t, k) * std::powf(1 - t, n - k) * controlPoints.at(k);
		}

		curveRenderer[index] = position;
	}
}

int bezierCurve::combinations(int n, int k)
{
	// From https://stackoverflow.com/questions/9330915/number-of-combinations-n-choose-r-in-c?noredirect=1&lq=1

	if (k == 0) return 1;
	if (k > n) return 0;
	if (k > n / 2) k = n - k;

	int result = 1;

	for (int r = 1; r <= k; r++)
	{
		result *= n - r + 1;
		result /= r;
	}

	return result;
}

void bezierCurve::setCurveResolution(int resolution)
{
	curveResolution = resolution;
	curveRenderer.clear();
	for (int index = 0; index <= curveResolution; ++index)
		curveRenderer.addVertex(ofPoint());
	calculateBezier();
}