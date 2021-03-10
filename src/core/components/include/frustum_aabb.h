//
// Created by Viktor on 7.3.2021 г..
//

#ifndef FRUSTUM_AABB_H
#define FRUSTUM_AABB_H


#include "transform.h"
#include "../../../lib/entityx/entityx.h"

class FrustumAABB : public entityx::Component<FrustumAABB>{
private:
	Vector3f m_dimensions;
	Vector3f m_position;
public:
	FrustumAABB(Vector3f dimensions, Vector3f position);
	Vector3f getNegativeFarPoint(const Vector3f& normal);
	Vector3f getPositiveFarPoint(const Vector3f& normal);
};


#endif //FRUSTUM_AABB_H
