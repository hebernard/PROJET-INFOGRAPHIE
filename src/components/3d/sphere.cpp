#include "sphere.h"

sphere::sphere(float radius) : object(new hierarchyButton(*this, "images/icons/sphere.png", "Sphere")), m_radius(radius), noFill(false)
{
	cout << "Sphere added with " << radius << " radius" << endl;
}

void sphere::customDraw()
{
	ofPushStyle();
	if (noFill)
	{
		ofNoFill();
	}
	else
	{
		ofFill();
	}
	ofDrawSphere(getPosition(), m_radius);
	ofPopStyle();
}

glm::vec3 sphere::getCenter()
{
	return getPosition();
}
