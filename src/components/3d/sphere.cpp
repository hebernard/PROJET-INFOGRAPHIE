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

	ofDrawSphere(0, 0, 0, m_radius);

	ofPopStyle();
}

glm::vec3 sphere::getCenter()
{
	return getPosition();
}

glm::vec3 sphere::getBBox()
{
	return glm::vec3(m_radius*2, m_radius*2, m_radius*2);
}
