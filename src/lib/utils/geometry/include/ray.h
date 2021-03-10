//
// Created by Viktor on 5.3.2021 г..
//

#ifndef RAY_H
#define RAY_H


#include "vector3.h"

class Ray {
private:
	float m_yaw;
	float m_pitch;
	Vector3f m_startPoint;
	Vector3f m_endPoint;
public:
	Ray(float pitch, float yaw, const Vector3f& start);
	void shoot(float step);
	Vector3f getEndPoint();
	float getLength();

};


#endif //RAY_H
