//
// Created by Viktor on 29.12.2020 г..
//

#ifndef QUATERNION_H
#define QUATERNION_H

#include "../../math/include/math_utils.h"

template<typename T>
class Vector3;

/** aka Vector4 */
template<typename T>
class Quaternion {
public:
	T x;
	T y;
	T z;
	T w;

	Quaternion() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 1;
	}

	Quaternion(const T x, const T y, const T z) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = 1;
	}

	Quaternion(const T x, const T y, const T z, const T w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Quaternion<T> operator+(const Quaternion<T>& vec) {
		return Quaternion<T>(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
	}

	Quaternion<T> operator-(const Quaternion<T>& vec) {
		return Quaternion<T>(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
	}

	Quaternion<T> operator*(const Quaternion<T>& vec) {
		return Quaternion<T>(x * vec.x, y * vec.y, z * vec.z, w * vec.w);
	}

	Quaternion<T> operator*(const T& scale) {
		return Quaternion<T>(x * scale, y * scale, z * scale, w + scale);
	}

	Quaternion<T> operator/(const Quaternion<T>& vec) {
		return Quaternion<T>(x / vec.x, y / vec.y, z / vec.z, w / vec.w);
	}

	Quaternion<T>& operator/=(const Quaternion<T>& vec) {
		return Quaternion<T>(x / vec.x, y / vec.y, z / vec.z, w / vec.w);
	}

	Quaternion<T> identity() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 1;
		return *this;
	}

	/** Euclidean length */
	T length() {
		return std::sqrt(x * x + y * y + z * z + w * w);
	}

	/** Squared Euclidean length */
	T length2() {
		return x * x + y * y + z * z + w * w;
	}

	/** returns normalized vector */
	Quaternion<T> normalize() {
		float magnitude = length2();
		if (magnitude == 0.0f || magnitude == 1.0f) return *this;
		magnitude = std::sqrt(magnitude);
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
		w /= magnitude;
		return *this;
	}

	/** returns the dot product |a . b| between two vectors */
	float dot(const Quaternion<T>& vec) {
		return (x * vec.x + y * vec.y + z * vec.z + w * vec.w);
	}

	/** https://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/index.htm */
	Quaternion<T> setFromAxis(Vector3<T> axis, float degree) {
		float d = axis.length();
		if (d == 0) return identity();
		float radians = MathUtils::toRadians(degree);
		float sine = std::sin(radians / 2);
		float cosine = std::cos(radians / 2);

		return Quaternion<T>(axis.x * sine, axis.y * sine, axis.z * sine, cosine);
	}

};

typedef Quaternion<float> Quaternionf;
typedef Quaternion<int> Quaternioni;


#endif //QUATERNION_H
