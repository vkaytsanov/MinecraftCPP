//
// Created by Viktor on 6.1.2021 г..
//

#include "include/first_person_camera_controller.h"
#include "../../include/lib.h"

FirstPersonCameraController::FirstPersonCameraController(Camera* camera) {
	m_pCamera = camera;
}

void FirstPersonCameraController::handleButtonMovement(const float dt) {
	Vector3f f = m_pCamera->getForwardVector();
	Vector3f r = m_pCamera->getRightVector();
	if (Lib::input->isKeyPressed(SDLK_a)) {
		m_pCamera->m_pTransform->position -= (r.normalize() * dt * CHARACTER_MOVEMENT_INTENSITY);
	}
	if (Lib::input->isKeyPressed(SDLK_d)) {
		m_pCamera->m_pTransform->position += (r.normalize() * dt * CHARACTER_MOVEMENT_INTENSITY);
	}
	if (Lib::input->isKeyPressed(SDLK_w)) {
		m_pCamera->m_pTransform->position -= (f.normalize() * dt * CHARACTER_MOVEMENT_INTENSITY);
	}
	if (Lib::input->isKeyPressed(SDLK_s)) {
		m_pCamera->m_pTransform->position += (f.normalize() * dt * CHARACTER_MOVEMENT_INTENSITY);
	}
}

void FirstPersonCameraController::handleMouseMovement(const float dt) {
	if (Lib::input->isMouseRightClick()) {
		float xRot = -(Lib::input->getMouseDeltaY()) * dt * CAMERA_MOVEMENT_INTENSITY;
		float yRot = (Lib::input->getMouseDeltaX()) * dt * CAMERA_MOVEMENT_INTENSITY;
		m_pCamera->m_pTransform->rotation = Vector3f(std::clamp(m_pCamera->m_pTransform->rotation.x + xRot, -90.f, 90.f),
		                                             m_pCamera->m_pTransform->rotation.y + yRot,
		                                             0);

		Lib::input->resetMouse();
	}
}

void FirstPersonCameraController::update(const float dt) {
	handleButtonMovement(dt);
	handleMouseMovement(dt);
}

