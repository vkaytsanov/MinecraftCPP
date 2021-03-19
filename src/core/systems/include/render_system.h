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
#include "../../data/include/hit_box.h"


class RenderSystem : public entityx::System<RenderSystem>{
private:
	static constexpr int RENDER_DISTANCE = 3;
	World* m_pWorld;
	PerspectiveCamera m_camera;
	Transform* m_pPlayerTransform;
	Skybox m_skybox;

	Shaders m_skyboxShader;
	Shaders m_hitBoxShader;
	Shaders m_particleShader;

	ChunkRenderer m_chunkRenderer;
	HitBox m_hitBoxRenderer;
	void renderSkybox();
	void renderWorld();
	void renderHitbox();
public:
	RenderSystem(World* world);
	void configure(entityx::EntityManager& entities, entityx::EventManager& events) override;
	void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	void preUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	void postUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	void renderParticles(entityx::EntityManager& entities);
};


#endif //RENDER_SYSTEM_H
