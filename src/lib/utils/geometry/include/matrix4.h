//
// Created by Viktor on 21.12.2020 г..
//

#ifndef MATRIX4_H
#define MATRIX4_H

#include <iostream>
#include "GL/glew.h"
#include "vector3.h"
#include "quaternion.h"

#define A00 0
#define A01 1
#define A02 2
#define A03 3
#define A10 4
#define A11 5
#define A12 6
#define A13 7
#define A20 8
#define A21 9
#define A22 10
#define A23 11
#define A30 12
#define A31 13
#define A32 14
#define A33 15

/**
 *    x        y       z       w      Vectors
 *  [ A00 ] [ A01 ] [ A02 ] [ A03 ]     R
 *  [ A10 ] [ A11 ] [ A12 ] [ A13 ]     F
 *  [ A20 ] [ A21 ] [ A22 ] [ A23 ]     W
 *  [ A30 ] [ A31 ] [ A32 ] [ A33 ]
 *
 *  A00, A01, A02 - Right Vector
 *  A10, A11, A12 - Up Vector
 *  A20, A21, A22 - Forward Vector
 *
 *  @param a - 4x4 array instead of matrix for memory reducement
 *
 */

template<typename T>
class Matrix4 {
public:
	T a[16];

	Matrix4() {
		identity();
	}

	/** sets the matrix from quaternion
	 * https://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm */
	Matrix4(const Quaternion<T>& q) {
		a[A00] = 1 - 2 * q.y * q.y - 2 * q.z * q.z;
		a[A01] = 2 * q.x * q.y - 2 * q.z * q.w;
		a[A02] = 2 * q.x * q.z + 2 * q.y * q.w;
		a[A03] = 0;
		a[A10] = 2 * q.x * q.y - 2 * q.z * q.w;
		a[A11] = 1 - 2 * q.x * q.x - 2 * q.z * q.z;
		a[A12] = 2 * q.y * q.z - 2 * q.x * q.w;
		a[A13] = 0;
		a[A20] = 2 * q.x * q.z - 2 * q.y * q.w;
		a[A21] = 2 * q.y * q.z + 2 * q.x * q.w;
		a[A22] = 1 - 2 * q.x * q.x - 2 * q.y * q.y;
		a[A23] = 0;
		a[A30] = 0;
		a[A31] = 0;
		a[A32] = 0;
		a[A33] = 1;
	}

	void setToOrthogonal2D(T x, T y, T width, T height) {
		// in 2D we dont use the z coordinate, instead we use 0 for near clipping
		// plane that is at the start of the camera and 1 for far clipping plane
		setToOrthogonal(x, x + width, y, y + height, 0, 1);
	}

	/**  @link https://docs.microsoft.com/en-us/windows/win32/opengl/glortho */
	void setToOrthogonal(T left, T right, T bottom, T top, T near, T far) {
		// following the picture and formulas on the Microsoft's OpenGL page - glOrtho() function
		identity();
		a[A00] = 2 / (right - left);
		a[A11] = 2 / (top - bottom);
		a[A22] = -2 / (far - near);

		a[A03] = -(right + left) / (right - left);
		a[A13] = -(top + bottom) / (top - bottom);
		a[A23] = -(far + near) / (far - near);

	}

	void identity() {
		// Create identity matrix with 1's on the diagonal and 0's everywhere else
		a[A00] = 1;
		a[A01] = 0;
		a[A02] = 0;
		a[A03] = 0;
		a[A10] = 0;
		a[A11] = 1;
		a[A12] = 0;
		a[A13] = 0;
		a[A20] = 0;
		a[A21] = 0;
		a[A22] = 1;
		a[A23] = 0;
		a[A30] = 0;
		a[A31] = 0;
		a[A32] = 0;
		a[A33] = 1;
	}

	/** @link https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluLookAt.xml */
	Matrix4<T>& setToLookAt(Vector3<T>& eye, Vector3<T>& center, Vector3<T>& up) {
		Vector3<T> f = (center - eye).normalize();
		Vector3<T> s = (f.cross(up)).normalize();
		Vector3<T> u = s.cross(f);

		identity();
		a[A00] = s.x;
		a[A10] = s.y;
		a[A20] = s.z;
		a[A01] = u.x;
		a[A11] = u.y;
		a[A21] = u.z;
		a[A02] = -f.x;
		a[A12] = -f.y;
		a[A22] = -f.z;
		a[A30] = -s.dot(eye);
		a[A31] = -u.dot(eye);
		a[A32] = f.dot(eye);


		return *this;
	}

	Matrix4<T>& setForTranslation(T x, T y, T z) {
		a[A30] = x;
		a[A31] = y;
		a[A32] = z;
		return *this;
	}

	Matrix4<T>& setForTranslation(const Vector3<T>& vec) {
		identity();
		a[A30] = vec.x;
		a[A31] = vec.y;
		a[A32] = vec.z;
		return *this;
	}

	T& operator[](int idx) {
		return a[idx];
	}


	Matrix4<T> operator*(const Matrix4<T>& mat) {
		Matrix4<T> result;
		result[A00] = mat.a[A00] * a[A00] + mat.a[A01] * a[A10] + mat.a[A02] * a[A20] + mat.a[A03] * a[A30];
		result[A01] = mat.a[A00] * a[A01] + mat.a[A01] * a[A11] + mat.a[A02] * a[A21] + mat.a[A03] * a[A31];
		result[A02] = mat.a[A00] * a[A02] + mat.a[A01] * a[A12] + mat.a[A02] * a[A22] + mat.a[A03] * a[A32];
		result[A03] = mat.a[A00] * a[A03] + mat.a[A01] * a[A13] + mat.a[A02] * a[A23] + mat.a[A03] * a[A33];
		result[A10] = mat.a[A10] * a[A00] + mat.a[A11] * a[A10] + mat.a[A12] * a[A20] + mat.a[A13] * a[A30];
		result[A11] = mat.a[A10] * a[A01] + mat.a[A11] * a[A11] + mat.a[A12] * a[A21] + mat.a[A13] * a[A31];
		result[A12] = mat.a[A10] * a[A02] + mat.a[A11] * a[A12] + mat.a[A12] * a[A22] + mat.a[A13] * a[A32];
		result[A13] = mat.a[A10] * a[A03] + mat.a[A11] * a[A13] + mat.a[A12] * a[A23] + mat.a[A13] * a[A33];
		result[A20] = mat.a[A20] * a[A00] + mat.a[A21] * a[A10] + mat.a[A22] * a[A20] + mat.a[A23] * a[A30];
		result[A21] = mat.a[A20] * a[A01] + mat.a[A21] * a[A11] + mat.a[A22] * a[A21] + mat.a[A23] * a[A31];
		result[A22] = mat.a[A20] * a[A02] + mat.a[A21] * a[A12] + mat.a[A22] * a[A22] + mat.a[A23] * a[A32];
		result[A23] = mat.a[A20] * a[A03] + mat.a[A21] * a[A13] + mat.a[A22] * a[A23] + mat.a[A23] * a[A33];
		result[A30] = mat.a[A30] * a[A00] + mat.a[A31] * a[A10] + mat.a[A32] * a[A20] + mat.a[A33] * a[A30];
		result[A31] = mat.a[A30] * a[A01] + mat.a[A31] * a[A11] + mat.a[A32] * a[A21] + mat.a[A33] * a[A31];
		result[A32] = mat.a[A30] * a[A02] + mat.a[A31] * a[A12] + mat.a[A32] * a[A22] + mat.a[A33] * a[A32];
		result[A33] = mat.a[A30] * a[A03] + mat.a[A31] * a[A13] + mat.a[A32] * a[A23] + mat.a[A33] * a[A33];
		return result;
	}

	Matrix4<T> operator*(const Vector3<T>& vec) {
		Matrix4<T> result;
		return result;
	}

	Matrix4<T>& operator*(const T& scale) {
		for (auto& i : a) {
			i += i * scale;
		}
		return *this;
	}

	Matrix4<T>& operator=(const Matrix4<T>& other) {
		if (this != &other) {
			for (int i = 0; i < 16; i++) {
				a[i] = other.a[i];
			}
		}
		return *this;
	}

	void zerofy() {
		for (int i = 0; i < 16; i++) {
			a[i] = 0;
		}
	}

	/** https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/opengl-perspective-projection-matrix */
	Matrix4<T> setToProjection(const T fov, const T near, const T far, const T aspectRatio) {
		const float tanHalfFovy = std::tan(fov / 2.f);

		zerofy();

		a[A00] = 1 / (aspectRatio * tanHalfFovy);
		a[A11] = 1 / (tanHalfFovy);
		a[A22] = -(far + near) / (far - near);
		a[A23] = -1;
		a[A32] = -(2 * far * near) / (far - near);
		return *this;
	}

	Matrix4<T> createFrustum(T l, T r, T b, T t, T n, T f) {
		this->identity();
		a[0] = 2.0f * n / (r - l);
		a[2] = (r + l) / (r - l);
		a[5] = 2.0f * n / (t - b);
		a[6] = (t + b) / (t - b);
		a[10] = -(f + n) / (f - n);
		a[11] = -(2.0f * f * n) / (f - n);
		a[14] = -1.0f;
		a[15] = 0.0f;
		return *this;
	}

	void debug() {
		std::cout << "----------------START OF DEBUG-------------" << std::endl;
		std::cout << "\t[" << a[A00] << "]""\t[" << a[A01] << "]""\t[" << a[A02] << "]""\t[" << a[A03] << "]"
		          << std::endl;
		std::cout << "\t[" << a[A10] << "]""\t[" << a[A11] << "]""\t[" << a[A12] << "]""\t[" << a[A13] << "]"
		          << std::endl;
		std::cout << "\t[" << a[A20] << "]""\t[" << a[A21] << "]""\t[" << a[A22] << "]""\t[" << a[A23] << "]"
		          << std::endl;
		std::cout << "\t[" << a[A30] << "]""\t[" << a[A31] << "]""\t[" << a[A32] << "]""\t[" << a[A33] << "]"
		          << std::endl;
		std::cout << "------------------END OF DEBUG-------------" << std::endl;
	}


};

typedef Matrix4<float> Matrix4f;
typedef Matrix4<int> Matrix4i;

#endif //MATRIX4_H
