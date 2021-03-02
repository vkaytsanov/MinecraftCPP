//
// Created by Viktor on 5.1.2021 г..
//

#include "include/perspective_camera.h"


PerspectiveCamera::PerspectiveCamera() {
	m_fov = 60;
}

PerspectiveCamera::PerspectiveCamera(const float fieldOfView) {
	m_fov = fieldOfView;
}

PerspectiveCamera::PerspectiveCamera(const float fieldOfView, const float worldWidth, const float worldHeight) {
	m_fov = fieldOfView;
	this->m_viewportWidth = worldWidth;
	this->m_viewportHeight = worldHeight;
	update(true);
}

void PerspectiveCamera::update(bool updateFrustum) {

	m_projection.setToProjection(m_fov,
	                             m_nearPlane,
	                             m_farPlane,
	                             m_viewportWidth / m_viewportHeight);
	Vector3f target = m_position + m_direction;
	m_view.setToLookAt(m_position, target, m_up);
	m_combined = m_projection * m_view;
	if (updateFrustum){
		m_frustum.update(&m_combined);
	}


}
