//
// Created by Viktor on 21.12.2020 г..
//

#ifndef CAMERA_H
#define CAMERA_H

#include "../../geometry/include/matrix4.h"
#include "../../geometry/include/vector3.h"
#include "frustum.h"

/**
 *  @pdf https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwjz_Y71-t7tAhVCPuwKHVgYCCoQFjACegQIARAC&url=https%3A%2F%2Fweb.cs.wpi.edu%2F~emmanuel%2Fcourses%2Fcs543%2Ff13%2Fslides%2Flecture04_p3.pdf&usg=AOvVaw3DhRKP2d1wamu2osZL4Ibp
 *  @link https://en.wikipedia.org/wiki/Viewing_frustum
 */


class Camera {
public:
	/** near clipping plane */
	float m_nearPlane = 0.001f;
	/** far clipping plane */
	float m_farPlane = 100.0f;
	/** Camera p_position vector */
	Vector3f m_position;
	/** Camera m_up vector */
	Vector3f m_up;
	/** Camera's looking m_direction vector */
	Vector3f m_direction;
	/** Camera m_view matrix */
	Matrix4f m_view;
	/** Camera m_projection matrix */
	Matrix4f m_projection;
	/** Camera's m_combined matrix */
	Matrix4f m_combined;

	Frustum m_frustum;

	float m_viewportWidth;
	float m_viewportHeight;
	Camera();
	~Camera();
	virtual void update(bool updateFrustum = true) = 0;
	void updateCombined();
	void translate(float x, float y, float z);
	void rotateX(float degree);
	void rotate(float deltaX, float deltaY) const;
	void rotateY(float degree);
	void rotateZ(float degree);

};


#endif //CAMERA_H
