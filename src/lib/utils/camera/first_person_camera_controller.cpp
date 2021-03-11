//
// Created by Viktor on 6.1.2021 г..
//

#include "include/first_person_camera_controller.h"
#include "../../include/lib.h"

FirstPersonCameraController::FirstPersonCameraController(Camera* camera) {
	m_pCamera = camera;
}

void FirstPersonCameraController::handleButtonMovement(const float dt) {
	float horizontalInput = 0.0f;
	float verticalInput = 0.0f;
	Vector3f f = m_pCamera->getForwardVector();
	Vector3f r = m_pCamera->getRightVector();
	if (Lib::input->isKeyPressed(SDLK_a)) {
		horizontalInput -= (dt * CHARACTER_MOVEMENT_INTENSITY);
	}
	if (Lib::input->isKeyPressed(SDLK_d)) {
		horizontalInput += (dt * CHARACTER_MOVEMENT_INTENSITY);
	}
	if (Lib::input->isKeyPressed(SDLK_w)) {
		verticalInput -= (dt * CHARACTER_MOVEMENT_INTENSITY);
	}
	if (Lib::input->isKeyPressed(SDLK_s)) {
		verticalInput += (dt * CHARACTER_MOVEMENT_INTENSITY);
	}

	if(horizontalInput != 0.0f || verticalInput != 0.0f) {
		m_pCamera->m_pTransform->translate(m_pCamera->m_pTransform->forward * verticalInput +
		                                   m_pCamera->m_pTransform->right * horizontalInput);
	}
}

void FirstPersonCameraController::handleMouseMovement(const float dt) {
	if (Lib::input->isMouseRightClick()) {
		float xRot = -(Lib::input->getMouseDeltaY()) * dt * CAMERA_MOVEMENT_INTENSITY;
		float yRot = (Lib::input->getMouseDeltaX()) * dt * CAMERA_MOVEMENT_INTENSITY;
//		m_pCamera->m_pTransform->rotate(xRot,yRot,0);
		m_pCamera->m_pTransform->eulerAngles += Vector3f(xRot, yRot, 0);
		m_pCamera->m_pTransform->eulerAngles.x = std::clamp(m_pCamera->m_pTransform->eulerAngles.x, -90.f, 90.f);
		m_pCamera->m_pTransform->hasChanged = true;
		Lib::input->resetMouse();
	}
}

void FirstPersonCameraController::update(const float dt) {
	handleButtonMovement(dt);
	handleMouseMovement(dt);
}

