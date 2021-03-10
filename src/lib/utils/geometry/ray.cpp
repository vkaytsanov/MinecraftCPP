//
// Created by Viktor on 5.3.2021 г..
//

#include <cmath>
#include "include/ray.h"

Ray::Ray(float pitch, float yaw, const Vector3f& start) : m_yaw(yaw),
                                                          m_pitch(pitch),
                                                          m_startPoint(start),
                                                          m_endPoint(start) {
}

void Ray::shoot(float step) {
	m_endPoint.x -= std::cos (m_yaw)   * step;
	m_endPoint.z -= std::sin (m_yaw)   * step;
	m_endPoint.y -= std::tan (m_pitch) * step;
}

Vector3f Ray::getEndPoint() {
	return m_endPoint;
}

float Ray::getLength() {
	return m_startPoint.distance(m_endPoint);
}
