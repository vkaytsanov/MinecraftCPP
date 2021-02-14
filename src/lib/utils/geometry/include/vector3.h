//
// Created by Viktor on 21.12.2020 г..
//

#ifndef VECTOR3_H
#define VECTOR3_H


#include "quaternion.h"

template<typename T>
class Matrix4;

template<typename T>
class Vector3{
public:
	T x;
	T y;
	T z;

	Vector3() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	Vector3(T x, T y, T z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3<T> operator+(const Vector3<T> &vec) {
		return Vector3<T>(this->x + vec.x, this->y + vec.y, this->z + vec.z);
	}

	Vector3<T> operator-(const Vector3<T> &vec) {
		return Vector3<T>(this->x - vec.x, this->y - vec.y, this->z - vec.z);
	}

	Vector3<T> operator*(const Vector3<T> &vec) {
		return Vector3<T>(this->x * vec.x, this->y * vec.y, this->z * vec.z);
	}

	Vector3<T> operator*(const T &scale) {
		return Vector3<T>(this->x * scale, this->y * scale, this->z * scale);
	}

	Vector3<T> operator/(const Vector3<T> &vec) {
		return Vector3<T>(this->x / vec.x, this->y / vec.y, this->z / vec.z);
	}

	Vector3<T> operator=(const Vector3<T> &vec) {
		this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;
		return *this;
	}

	Vector3<T>& operator/=(const Vector3<T> &vec) {
		this->x /= vec.x;
		this->y /= vec.y;
		this->z /= vec.z;
		return *this;
	}

	Vector3<T>& operator+=(const Vector3<T> &vec) {
		this->x += vec.x;
		this->y += vec.y;
		this->z += vec.z;
		return *this;
	}

	Vector3<T>& operator-=(const Vector3<T> &vec) {
		this->x -= vec.x;
		this->y -= vec.y;
		this->z -= vec.z;
		return *this;
	}

	Vector3<T>& operator*=(const Vector3<T> &vec) {
		this->x *= vec.x;
		this->y *= vec.y;
		this->z *= vec.z;
		return *this;
	}

	Vector3<T> operator*(const Matrix4<T>& mat) {
		return Vector3<T>(
				x * mat.a[0] + y * mat.a[1] + z * mat.a[2] + mat.a[3],
				x * mat.a[4] + y * mat.a[5] + z * mat.a[6] + mat.a[7],
				x * mat.a[8] + y * mat.a[9] + z * mat.a[10] + mat.a[11]
		);
	}

	T operator[](const int idx){
		// TODO
		if(idx == 0) return x;
		if(idx == 1) return y;
		if(idx == 2) return z;
		return -1;
	}


	/** Euclidean length */
	T length(){
		return std::sqrt(x * x + y * y + z * z);
	}

	/** Squared Euclidean length */
	T length2(){
		return x * x + y * y + z * z;
	}

	/** returns normalized vector */
	Vector3<T> normalize() {
		const float magnitude = length2();
		if(magnitude == 0.0f || magnitude == 1.0f) return *this;

		return *this * (1.0f / std::sqrt(magnitude));
	}

	/** returns the dot product |a . b| between two vectors */
	float dot(const Vector3<T>& vec){
		return (this->x * vec.x + this->y * vec.y + this->z * vec.z);
	}

	/** returns the cross product |a x b| between two vectors,
	 * using the right hand rule where:
	 * @param this - middle finger pointing at us
	 * @param vec - the pointer finger pointing away
	 * @return the vector, which is the thumb
	 * */
	Vector3<T> cross(const Vector3<T>& vec){
		return Vector3<T>(
				(y * vec.z) - (z * vec.y),
				(z * vec.x) - (x * vec.z),
				(x * vec.y) - (y * vec.x)
		);
	}

	Vector3<T> rotate(const Vector3<T> axis, const float degrees){
		Matrix4<T> tmpMat(Quaternion<T>().setFromAxis(axis, degrees).normalize());
		return *this * tmpMat;
	}

};

typedef Vector3<float> Vector3f;
typedef Vector3<int> Vector3i;

#endif //VECTOR3_H
