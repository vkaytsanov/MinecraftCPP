//
// Created by Viktor on 7.3.2021 г..
//

#include "include/frustum_aabb.h"

FrustumAABB::FrustumAABB(Vector3f dimensions, Vector3f position) : m_dimensions(dimensions), m_position(position) {

}

Vector3f FrustumAABB::getNegativeFarPoint(const Vector3f& normal) {
	Vector3f result = m_position;
	if (normal.x < 0) {
		result.x += m_dimensions.x;
	}
	if (normal.y < 0) {
		result.y += m_dimensions.y;
	}
	if (normal.z < 0) {
		result.z += m_dimensions.z;
	}
	return result;
}

Vector3f FrustumAABB::getPositiveFarPoint(const Vector3f& normal) {
	Vector3f result = m_position;
	if (normal.x > 0) {
		result.x += m_dimensions.x;
	}
	if (normal.y > 0) {
		result.y += m_dimensions.y;
	}
	if (normal.z > 0) {
		result.z += m_dimensions.z;
	}
	return result;
}