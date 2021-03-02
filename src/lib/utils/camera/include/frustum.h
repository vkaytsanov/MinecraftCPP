//
// Created by Viktor on 2.3.2021 г..
//

#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <array>
#include "../../geometry/include/vector3.h"
#include "../../geometry/include/matrix4.h"

enum PlaneType{
	FarPlane,
	NearPlane,
	TopPlane,
	BottomPlane,
	LeftPlane,
	RightPlane
};

class FrustumAABB{
private:
	Vector3f m_dimensions;
	Vector3f m_position;
public:
	FrustumAABB(Vector3f dimensions, Vector3f position);
	Vector3f getNegativeFarPoint(const Vector3f& normal);
	Vector3f getPositiveFarPoint(const Vector3f& normal);
};

class Plane{
public:
	Vector3f m_normal;
	float m_distanceToOrigin;
	float distanceToPoint(Vector3f point);

};

class Frustum {
private:
	std::array<Plane, 6> m_planes;
public:
	void update(Matrix4f* combined);
	bool boxInFrustum(FrustumAABB& box);
};


#endif //FRUSTUM_H
