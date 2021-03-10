//
// Created by Viktor on 7.3.2021 г..
//

#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H


#include "../../../lib/entityx/System.h"
#include "../../../lib/utils/include/shaders.h"
#include "../../../lib/utils/camera/include/perspective_camera.h"
#include "../../../lib/utils/camera/include/orthographic_camera.h"
#include "../../data/include/skybox.h"
#include "chunk_renderer.h"
#include "../../data/include/world.h"
#include "../../../lib/utils/include/universal_viewport.h"
#include "player_system.h"


class RenderSystem : public entityx::System<RenderSystem>{
private:
	static constexpr int RENDER_DISTANCE = 2;
	World* m_pWorld;
	PerspectiveCamera m_camera;
	FirstPersonCameraController m_cameraController;
	Transform* m_playerTransform;
	Skybox m_pSkybox;
	Shaders m_skyboxShader;

	ChunkRenderer m_chunkRenderer;
	void renderSkybox();
	void renderWorld();
public:
	RenderSystem(World* world);
	void configure(entityx::EntityManager& entities, entityx::EventManager& events) override;
	void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
};


#endif //RENDER_SYSTEM_H
