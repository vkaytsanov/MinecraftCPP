//
// Created by Viktor on 5.3.2021 г..
//

#include <cmath>
#include "include/ray.h"


Ray::Ray(const Vector3f& start, const Vector3f& direction) : m_startPoint(start),
                                                             m_endPoint(start),
                                                             m_direction(direction) {
}

void Ray::shoot(float step) {
	m_endPoint.x -= m_direction.x * step;
	m_endPoint.y -= m_direction.y * step;
	m_endPoint.z -= m_direction.z * step;
}

Vector3f Ray::getEndPoint() {
	return m_endPoint;
}


float Ray::getLength() {
	return m_startPoint.distance(m_endPoint);
}
