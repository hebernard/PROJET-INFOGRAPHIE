#include "sphere.h"

sphere::sphere(float radius) : object(new hierarchyButton(*this, "images/icons/3d.png", "Sphere")), m_radius(radius)
{
	cout << "Sphere added with " << radius << " radius" << endl;
}

void sphere::customDraw()
{
	ofPushStyle();
	ofFill();
	ofDrawSphere(getPosition(), m_radius);
	ofPopStyle();
}

glm::vec3 sphere::getCenter()
{
	return getPosition();
}
