#include "camera.h"
#include "ofMath.h"
#include "ofUtils.h"
#include "ofGraphicsBaseTypes.h"
#include <limits>
#include "glm/gtx/vector_angle.hpp"
#include "cursor.h"
#include "scene.h"

using namespace std;

// when a camera is moving due to momentum, this keeps it
// from moving forever by assuming small values are zero.
static const float minDifference = 0.1e-5f;

//----------------------------------------
camera::camera() {
	reset();
	sensitivityTranslate = { 1,1,1 };
	sensitivityRot = { 1,1,1 };

	addInteraction(TRANSFORM_ROTATE, OF_MOUSE_BUTTON_LEFT);
	addInteraction(TRANSFORM_TRANSLATE_XY, OF_MOUSE_BUTTON_RIGHT);

}

void camera::render(scene& s, int index)
{
	int cameraCount = s.cameraCount();
	if (cameraCount == 1)
	{
		begin();
	}
	else if (cameraCount == 2)
	{
		if (index == 0)
		{
			begin(ofRectangle(0, 0, ofGetWidth()/2, ofGetHeight()));
		}
		else
		{
			begin(ofRectangle(ofGetWidth() / 2, 0, ofGetWidth()/2, ofGetHeight()));
		}
	}
	else if (cameraCount == 3)
	{
		if (index == 0)
		{
			begin(ofRectangle(0, 0, ofGetWidth() / 2, ofGetHeight() / 2));
		}
		else if (index == 1)
		{
			begin(ofRectangle(ofGetWidth() / 2, 0, ofGetWidth() / 2, ofGetHeight() / 2));
		}
		else
		{
			begin(ofRectangle(0, ofGetHeight() / 2, ofGetWidth(), ofGetHeight() / 2));
		}
	}
	else if (cameraCount == 4)
	{
		if (index == 0)
		{
			begin(ofRectangle(0, 0, ofGetWidth() / 2, ofGetHeight() / 2));
		}
		else if (index == 1)
		{
			begin(ofRectangle(ofGetWidth() / 2, 0, ofGetWidth() / 2, ofGetHeight() / 2));
		}
		else if (index == 2)
		{
			begin(ofRectangle(0, ofGetHeight() / 2, ofGetWidth() / 2, ofGetHeight() / 2));
		}
		else
		{
			begin(ofRectangle(ofGetWidth() / 2, ofGetHeight() / 2, ofGetWidth() / 2, ofGetHeight() / 2));
		}
	}

	s.drawGrid();

	s.drawObjects();

	// debug target
	//ofSetColor(ofColor::red);
	//ofDrawSphere(target.getPosition(), 0.2f);

	end();
}

void camera::setOrtho()
{
	enableOrtho();
	setPosition(0, 1, 5);
	setTarget(glm::vec3(0, 1, 0));
	setScale(0.01);
	setNearClip(-100000);

	//removeAllInteractions();
	//addInteraction(TRANSFORM_TRANSLATE_XY, OF_MOUSE_BUTTON_RIGHT);
}

void camera::setPerpective()
{
	disableOrtho();
	setPosition(0, 1, 5);
	setTarget(glm::vec3(0, 1, 0));
	setScale(1);
	setNearClip(0.001f);

	//removeAllInteractions();
	//addInteraction(TRANSFORM_ROTATE, OF_MOUSE_BUTTON_LEFT);
	//addInteraction(TRANSFORM_TRANSLATE_XY, OF_MOUSE_BUTTON_RIGHT);
}

void camera::resetView()
{
	if (getOrtho())
	{
		setOrtho();
	}
	else
	{
		setPerpective();
	}
}

//----------------------------------------
void camera::update(ofEventArgs& args) {
	if (this->viewport.isZero()) {
		viewport = getViewport();
	}
	if (!bDistanceSet && bAutoDistance) {
		setDistance(getImagePlaneDistance(viewport), true);
	}
	if (bMouseInputEnabled && events) {
		if (events->getMousePressed()) {
			updateMouse(glm::vec2(events->getMouseX(), events->getMouseY()));
		}
		if (currentTransformType == TRANSFORM_ROTATE) {
			//cursor::setRotateCursor();
			updateRotation();
		}
		else if (currentTransformType == TRANSFORM_TRANSLATE_XY ||
			currentTransformType == TRANSFORM_TRANSLATE_Z ||
			currentTransformType == TRANSFORM_SCALE) {
			//cursor::setDragCursor();
			updateTranslation();
		}

		timer += ofGetLastFrameTime();
		if (timer > 0.5f && currentTransformType == TRANSFORM_NONE)
		{
			cursor::setDefaultCursor();
		}
	}
}

//----------------------------------------
void camera::begin(const ofRectangle& _viewport) {
	if (!bEventsSet) {
		setEvents(ofEvents());
	}
	viewport = _viewport;
	ofCamera::begin(viewport);
}

//----------------------------------------
void camera::reset() {
	target.resetTransform();

	target.setPosition(0, 0, 0);
	lookAt(target);

	resetTransform();
	setPosition(0, 0, lastDistance);

	rot = { 0,0,0 };
	translate = { 0,0,0 };

	if (bAutoDistance) {
		bDistanceSet = false;
	}
	bApplyInertia = false;
	currentTransformType = TRANSFORM_NONE;
}

//----------------------------------------
void camera::setTarget(const glm::vec3& targetPoint) {
	target.setPosition(targetPoint);
	lookAt(target);
}

//----------------------------------------
void camera::setTarget(ofNode& targetNode) {
	target = targetNode;
	lookAt(target);
}

//----------------------------------------
const ofNode& camera::getTarget() const {
	return target;
}

//----------------------------------------
void camera::setDistance(float distance) {
	setDistance(distance, true);
}

//----------------------------------------
void camera::setDistance(float distance, bool save) {//should this be the distance from the camera to the target?
	if (distance > 0.0f) {
		if (save) {
			this->lastDistance = distance;
		}
		setPosition(target.getPosition() + (distance * getZAxis()));
		bDistanceSet = true;
	}
}

//----------------------------------------
float camera::getDistance() const {
	return glm::distance(target.getPosition(), getPosition());
}

//----------------------------------------
void camera::setAutoDistance(bool bAutoDistance) {
	this->bAutoDistance = bAutoDistance;
	if (bAutoDistance) {
		bDistanceSet = false;
	}
}

//----------------------------------------
void camera::setDrag(float drag) {
	this->drag = drag;
}

//----------------------------------------
float camera::getDrag() const {
	return drag;
}

//----------------------------------------
void camera::setTranslationKey(char key) {
	doTranslationKey = key;
}

//----------------------------------------
char camera::getTranslationKey() const {
	return doTranslationKey;
}

//----------------------------------------
void camera::enableMouseInput() {
	if (!bMouseInputEnabled && events) {
		listeners.push(events->update.newListener(this, &camera::update));
		listeners.push(events->mousePressed.newListener(this, &camera::mousePressed));
		listeners.push(events->mouseReleased.newListener(this, &camera::mouseReleased));
		listeners.push(events->mouseScrolled.newListener(this, &camera::mouseScrolled));
	}
	// if enableMouseInput was called within ofApp::setup()
	// `events` will still carry a null pointer, and bad things
	// will happen. Therefore we only update the flag. 
	bMouseInputEnabled = true;
	// setEvents() is called upon first load, and will make sure 
	// to enable the mouse input once the camera is fully loaded.
}

//----------------------------------------
void camera::disableMouseInput() {
	if (bMouseInputEnabled && events) {
		listeners.unsubscribeAll();
	}
	// if disableMouseInput was called within ofApp::setup()
	// `events` will still carry a null pointer, and bad things
	// will happen. Therefore we only update the flag. 
	bMouseInputEnabled = false;
	// setEvents() is called upon first load, and will make sure 
	// to enable the mouse input once the camera is fully loaded.
}
//----------------------------------------
bool camera::getMouseInputEnabled() const {
	return bMouseInputEnabled;
}

//----------------------------------------
void camera::setEvents(ofCoreEvents& _events) {
	// If en/disableMouseInput were called within ofApp::setup(),
	// bMouseInputEnabled will tell us about whether the camera
	// mouse input needs to be initialised as enabled or disabled.
	// we will still set `events`, so that subsequent enabling
	// and disabling can work.

	// we need a temporary copy of bMouseInputEnabled, since it will 
	// get changed by disableMouseInput as a side-effect.
	bool wasMouseInputEnabled = bMouseInputEnabled;// || !events;
	disableMouseInput();
	events = &_events;
	if (wasMouseInputEnabled) {
		// note: this will set bMouseInputEnabled to true as a side-effect.
		enableMouseInput();
	}
	bEventsSet = true;
}

//----------------------------------------
void camera::setRotationSensitivity(const glm::vec3& sensitivity) {
	sensitivityRot = sensitivity;
}
//----------------------------------------
void camera::setRotationSensitivity(float x, float y, float z) {
	setRotationSensitivity({ x,y,z });
}
//----------------------------------------
void camera::setTranslationSensitivity(const glm::vec3& sensitivity) {
	sensitivityTranslate = sensitivity;
}
//----------------------------------------
void camera::setTranslationSensitivity(float x, float y, float z) {
	sensitivityTranslate = { x,y,z };
}

//----------------------------------------
void camera::enableMouseMiddleButton() {
	bEnableMouseMiddleButton = true;
}

//----------------------------------------
void camera::disableMouseMiddleButton() {
	bEnableMouseMiddleButton = false;
}

//----------------------------------------
bool camera::getMouseMiddleButtonEnabled() const {
	return bEnableMouseMiddleButton;
}

//----------------------------------------
glm::vec3 camera::up() const {
	if (bRelativeYAxis) {
		if (bApplyInertia) {
			return getYAxis();
		}
		else {
			return lastPressAxisY;
		}
	}
	else {
		return upAxis;
	}
}

//----------------------------------------
void camera::setRelativeYAxis(bool relative) {
	bRelativeYAxis = relative;
}

//----------------------------------------
bool camera::getRelativeYAxis() const {
	return bRelativeYAxis;
}

//----------------------------------------
void camera::setUpAxis(const glm::vec3& _up) {
	upAxis = _up;
}

//----------------------------------------
const glm::vec3& camera::getUpAxis() const {
	return upAxis;
}

//----------------------------------------
void camera::enableInertia() {
	doInertia = true;
}

//----------------------------------------
void camera::disableInertia() {
	doInertia = false;
}

//----------------------------------------
bool camera::getInertiaEnabled() const {
	return doInertia;
}

//----------------------------------------
void camera::updateTranslation() {
	if (bApplyInertia) {
		translate *= drag;
		if (std::abs(translate.x) <= minDifference && std::abs(translate.y) <= minDifference && std::abs(translate.z) <= minDifference) {
			translate = { 0,0,0 };
			bApplyInertia = false;
			currentTransformType = TRANSFORM_NONE;

			bIsScrolling = false;
			return;
		}
		auto offset = (getXAxis() * translate.x) + (getYAxis() * translate.y);
		move(offset + getZAxis() * translate.z);
		setTarget(target.getPosition() + offset);
	}
	if (currentTransformType == TRANSFORM_TRANSLATE_XY ||
		currentTransformType == TRANSFORM_TRANSLATE_Z ||
		currentTransformType == TRANSFORM_SCALE) {
		if (getOrtho()) {
			//In ortho mode moving along the z axis has no effect besides clipping.
			// Instead, scale is applied to achieve the effect of getting near or far from the target.
			glm::vec3 mousePre;
			bool bDoScale = (currentTransformType == TRANSFORM_SCALE || currentTransformType == TRANSFORM_TRANSLATE_Z);
			if (bDoScale) {
				mousePre = screenToWorld(glm::vec3((bIsScrolling ? mouseAtScroll : lastPressMouse), 0));
			}
			auto offset = glm::vec3(lastPressAxisX * translate.x) + (lastPressAxisY * translate.y);
			move(offset);
			setTarget(target.getPosition() + offset);
			if (bDoScale) {
				auto s = getScale() + translate.z;
				setScale(CLAMP(s.x, 0, 10), CLAMP(s.y, 0, 10), CLAMP(s.z, 0, 10));
				// this move call is to keep the scaling centered below the mouse.
				//move(mousePre - screenToWorld(glm::vec3((bIsScrolling ? mouseAtScroll : lastPressMouse), 0)));
			}
		}
		else {
			auto offset = glm::vec3(lastPressAxisX * translate.x) + (lastPressAxisY * translate.y);
			move(offset + (lastPressAxisZ * translate.z));
			setTarget(target.getPosition() + offset);
		}
	}
	if (bIsScrolling) {
		//this it to avoid the transformation to keep on after scrolling ended.
		currentTransformType = TRANSFORM_NONE;
		bIsScrolling = false;
	}
}

//----------------------------------------
void camera::updateRotation() {
	if (bApplyInertia) {
		rot *= drag;
		if (std::abs(rot.x) <= minDifference && std::abs(rot.y) <= minDifference && std::abs(rot.z) <= minDifference) {
			rot = { 0,0,0 };
			bApplyInertia = false;
			currentTransformType = TRANSFORM_NONE;
			return;
		}

	}
	if (bApplyInertia) {
		curRot = glm::angleAxis(rot.z, getZAxis()) * glm::angleAxis(rot.y, up()) * glm::angleAxis(rot.x, getXAxis());
		rotateAround(curRot, target.getGlobalPosition());
		rotate(curRot);
	}
	else {
		//ofRectangle area = getControlArea();
		//glm::vec3 center = screenToWorld(glm::vec3(area.getWidth() / 2, area.getHeight() / 2, 0));

		curRot = glm::angleAxis(rot.z, lastPressAxisZ) * glm::angleAxis(rot.y, up()) * glm::angleAxis(rot.x, lastPressAxisX);
		setOrientation(curRot * lastPressOrientation);
		setPosition(curRot * (lastPressPosition - target.getGlobalPosition()) + target.getGlobalPosition());
		//setPosition(curRot * (lastPressPosition - center) + center);
	}
}

//----------------------------------------
void camera::setControlArea(const ofRectangle& _controlArea) {
	controlArea = _controlArea;
}

//----------------------------------------
void camera::clearControlArea() {
	controlArea = ofRectangle();
}

//----------------------------------------
ofRectangle camera::getControlArea() const {
	if (controlArea.isZero()) {
		if (viewport.isZero()) {
			return getRenderer()->getCurrentViewport();
		}
		return viewport;
	}
	return controlArea;
}

//----------------------------------------
void camera::mousePressed(ofMouseEventArgs& mouse) {
	ofRectangle area = getControlArea();
	if (area.inside(mouse.x, mouse.y)) {
		lastPressMouse = mouse;
		prevMouse = mouse;
		lastPressAxisX = getXAxis();
		lastPressAxisY = getYAxis();
		lastPressAxisZ = getZAxis();
		lastPressPosition = ofCamera::getGlobalPosition();
		lastPressOrientation = ofCamera::getGlobalOrientation();
		currentTransformType = TRANSFORM_NONE;
		if (events) {
			for (const auto& i : interactions) {
				if (i.mouseButton == mouse.button && ((i.key == -1) || events->getKeyPressed(i.key))) {
					currentTransformType = i.transformType;
					break;
				}
			}
		}
		if (currentTransformType == TRANSFORM_ROTATE) {
			bInsideArcball = glm::length(mouse - glm::vec2(area.getCenter())) < std::min(area.width / 2, area.height / 2);
		}
		bApplyInertia = false;
	}
}

//----------------------------------------
void camera::mouseReleased(ofMouseEventArgs& mouse) {
	ofRectangle area = getControlArea();
	cursor::setDefaultCursor();
	if (doInertia) {
		bApplyInertia = true;
	}
	else {
		currentTransformType = TRANSFORM_NONE;
		rot = { 0,0,0 };
		translate = { 0,0,0 };
	}
}
//----------------------------------------
void camera::mouseScrolled(ofMouseEventArgs& mouse) {
	ofRectangle area = getControlArea();
	if (area.inside(mouse)) {
		mouseVel = mouse - prevMouse;
		prevMouse = mouse;
		if (doInertia) {
			bApplyInertia = true;
		}
		lastPressPosition = ofCamera::getGlobalPosition();
		lastPressAxisZ = getZAxis();
		if (getOrtho()) {
			translate.z = -sensitivityScroll * mouse.scrollY / viewport.height;
			mouseAtScroll = mouse;
		}
		else {
			translate.z = -mouse.scrollY * 30 * sensitivityTranslate.z * (getDistance() + std::numeric_limits<float>::epsilon()) / area.height;
		}

		if (translate.z > 0) {
			cursor::setZoomOutCursor();
			timer = 0;
		}
		if (translate.z < 0) {
			cursor::setZoomInCursor();
			timer = 0;
		}

		currentTransformType = TRANSFORM_SCALE;
		bIsScrolling = true;
	}
}

//----------------------------------------
void camera::updateMouse(const glm::vec2& mouse) {
	ofRectangle area = getControlArea();
	int vFlip = (isVFlipped() ? -1 : 1);

	rot = { 0,0,0 };
	translate = { 0,0,0 };
	switch (currentTransformType) {
	case TRANSFORM_ROTATE:
		cursor::setRotateCursor();
		mouseVel = mouse - lastPressMouse;
		//if (bInsideArcball) {
			rot.x = vFlip * -mouseVel.y * sensitivityRot.x * glm::pi<float>() / std::min(area.width, area.height);
			rot.y = -mouseVel.x * sensitivityRot.y * glm::pi<float>() / std::min(area.width, area.height);
		//}
		/*else {
			glm::vec2 center(area.getCenter());
			rot.z = sensitivityRot.z * -vFlip * glm::orientedAngle(glm::normalize(mouse - center),
				glm::normalize(lastPressMouse - center));
		}*/
		break;
	case TRANSFORM_TRANSLATE_XY:
		cursor::setDragCursor();
		mouseVel = mouse - prevMouse;
		if (getOrtho()) {
			translate.x = -mouseVel.x * getScale().z;
			translate.y = vFlip * mouseVel.y * getScale().z;
		}
		else {
			translate.x = -mouseVel.x * sensitivityTranslate.x * (getDistance() + std::numeric_limits<float>::epsilon()) / area.width;
			translate.y = vFlip * mouseVel.y * sensitivityTranslate.y * (getDistance() + std::numeric_limits<float>::epsilon()) / area.height;
		}
		break;
	case TRANSFORM_TRANSLATE_Z:
		mouseVel = mouse - prevMouse;
		if (getOrtho()) {
			translate.z = mouseVel.y * sensitivityScroll / area.height;
		}
		else {
			translate.z = mouseVel.y * (sensitivityTranslate.z * 0.7f) * (getDistance() + std::numeric_limits<float>::epsilon()) / area.height;
		}
		break;
	default:
		cursor::setDefaultCursor();
		break;
	}
	prevMouse = mouse;
}
//----------------------------------------
void camera::addInteraction(TransformType type, int mouseButton, int key) {
	if (!hasInteraction(mouseButton, key)) {
		interactions.push_back(interaction(type, mouseButton, key));
	}
	else {
		ofLogNotice("camera") << "Can not add interaction. It already exists";
	}
}
//----------------------------------------
void camera::removeInteraction(TransformType type, int mouseButton, int key) {
	ofRemove(interactions, [&](interaction& i) { return i.transformType == type && i.mouseButton == mouseButton && i.key == key; });
}
//----------------------------------------
bool camera::hasInteraction(int mouseButton, int key) {
	for (const auto& i : interactions) {
		if (i.mouseButton == mouseButton && i.key == key) {
			return true;
		}
	}
	return false;
}
//----------------------------------------
bool camera::hasInteraction(TransformType type, int mouseButton, int key) {
	for (const auto& i : interactions) {
		if (i.transformType == type && i.mouseButton == mouseButton && i.key == key) {
			return true;
		}
	}
	return false;
}
//----------------------------------------
void camera::removeAllInteractions() {
	interactions.clear();
}
//----------------------------------------
void camera::onPositionChanged() {
	if (!bDistanceSet && bAutoDistance) {
		bDistanceSet = true;
	}
}
