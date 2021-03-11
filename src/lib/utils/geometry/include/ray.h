//
// Created by Viktor on 5.3.2021 г..
//

#ifndef RAY_H
#define RAY_H


#include "vector3.h"

class Ray {
private:
	Vector3f m_startPoint;
	Vector3f m_endPoint;
	Vector3f m_direction;
public:
	Ray(const Vector3f& start, const Vector3f& direction);
	void shoot(float step);
	Vector3f getEndPoint();
	float getLength();

};


#endif //RAY_H
