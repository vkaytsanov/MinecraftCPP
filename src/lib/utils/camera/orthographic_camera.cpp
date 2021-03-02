//
// Created by Viktor on 21.12.2020 г..
//


#include "include/orthographic_camera.h"
#include "../../include/lib.h"

OrthographicCamera::OrthographicCamera() {
	m_nearPlane = 0;

}

OrthographicCamera::OrthographicCamera(const float viewportWidth, const float viewportHeight) {
	this->m_viewportWidth = viewportWidth;
	this->m_viewportHeight = viewportHeight;
	m_nearPlane = 0;
	update(true);
}

void OrthographicCamera::update(bool updateFrustum) {
	m_projection.setToOrthogonal(
			-m_viewportWidth / 2,
			m_viewportWidth / 2,
			-m_viewportHeight / 2,
			m_viewportHeight / 2,
			m_nearPlane,
			m_farPlane
	);
	m_view.setToLookAt(m_position, m_direction, m_up);
	m_combined = m_projection * m_view;

	if (updateFrustum){
		m_frustum.update(&m_combined);
	}
}

void OrthographicCamera::translate(float x, float y) {
	Camera::translate(x, y, 0);
}


