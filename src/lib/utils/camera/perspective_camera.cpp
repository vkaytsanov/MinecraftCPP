//
// Created by Viktor on 5.1.2021 г..
//

#include "include/perspective_camera.h"
#include "../../include/lib.h"


PerspectiveCamera::PerspectiveCamera() : PerspectiveCamera(70) {

}

PerspectiveCamera::PerspectiveCamera(const float fieldOfView) : PerspectiveCamera(fieldOfView,
                                                                                  Lib::graphics->getWidth(),
                                                                                  Lib::graphics->getHeight()) {

}

PerspectiveCamera::PerspectiveCamera(const float fieldOfView, const float worldWidth, const float worldHeight) {
	m_fov = fieldOfView;
	m_viewportWidth = worldWidth;
	m_viewportHeight = worldHeight;
	update(true);
}

void PerspectiveCamera::update(bool updateFrustum) {
	m_projection.setToProjection(m_fov,
	                             m_nearPlane,
	                             m_farPlane,
	                             m_viewportWidth / m_viewportHeight);

	m_view = m_pTransform->transformMatrix;
	//m_pTransform->transformMatrix.debug();

	m_combined = m_projection * m_view;
	if (updateFrustum) {
		m_frustum.update(&m_combined);
	}

}
