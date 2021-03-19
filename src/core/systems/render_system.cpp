//
// Created by Viktor on 7.3.2021 г..
//

#include "include/render_system.h"
#include "include/particle_system.h"
#include "../components/include/player_controller.h"
#include "../components/include/particle.h"


RenderSystem::RenderSystem(World* world) : m_pWorld(world),
                                           m_skyboxShader("skybox/shader.vert", "skybox/shader.frag"),
                                           m_particleShader("particle/shader.vert", "particle/shader.frag"),
                                           m_hitBoxShader("hitbox/shader.vert", "hitbox/shader.frag"),
                                           m_camera(70){

}

void RenderSystem::configure(entityx::EntityManager& entities, entityx::EventManager& events) {
	for (const auto& entity : entities.entities_with_components<PlayerController>()) {
		m_pPlayerTransform = entity.getComponent<Transform>().get();
	}
	// follow the player
	m_camera.m_pTransform = m_pPlayerTransform;

}

void RenderSystem::preUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
}

void RenderSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {

}

void RenderSystem::postUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
	m_camera.update(true);
	renderSkybox();
	renderWorld();
	renderHitbox();
	//renderParticles(entities);
}

void RenderSystem::renderSkybox() {
	glDepthMask(GL_FALSE);

	m_skyboxShader.begin();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_skybox.textureCubeMap.getBuffer());
	const Matrix4f& mat = m_camera.getCombinedMatrix().noTranslation();
	m_skyboxShader.setMatrix4("proj", mat);
	m_skyboxShader.setInt("texSkybox", 0);

	m_skybox.getVao().bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	m_skybox.getVao().unbind();

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	m_skyboxShader.end();

	glDepthMask(GL_TRUE);
}

void RenderSystem::renderWorld() {
	int playerX = (int) m_camera.m_pTransform->position.x / CHUNK_SIZE_X;
	int playerZ = (int) m_camera.m_pTransform->position.z / CHUNK_SIZE_Z;

	m_chunkRenderer.beginChunkRendering(&m_camera, RENDER_DISTANCE);
	for (int x = playerX - RENDER_DISTANCE; x < playerX + RENDER_DISTANCE; x++) {
		for (int z = playerZ - RENDER_DISTANCE; z < playerZ + RENDER_DISTANCE; z++) {
			entityx::Entity* chunk = m_pWorld->getChunk(x, z);
			if (m_camera.m_frustum.boxInFrustum(chunk->getComponent<ChunkAABB>().get())) {
				m_chunkRenderer.renderChunk(chunk->getComponent<ChunkMesh>().get(), x, z);
			}
		}
	}

	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int x = playerX - RENDER_DISTANCE; x < playerX + RENDER_DISTANCE; x++) {
		for (int z = playerZ - RENDER_DISTANCE; z < playerZ + RENDER_DISTANCE; z++) {
			entityx::Entity* chunk = m_pWorld->getChunk(x, z);
			if (m_camera.m_frustum.boxInFrustum(chunk->getComponent<ChunkAABB>().get())) {
				m_chunkRenderer.renderTransparentChunk(chunk->getComponent<ChunkMesh>().get(), x, z);
			}
		}
	}

	for (int x = playerX - RENDER_DISTANCE; x < playerX + RENDER_DISTANCE; x++) {
		for (int z = playerZ - RENDER_DISTANCE; z < playerZ + RENDER_DISTANCE; z++) {
			entityx::Entity* chunk = m_pWorld->getChunk(x, z);
			if (m_camera.m_frustum.boxInFrustum(chunk->getComponent<ChunkAABB>().get())) {
				m_chunkRenderer.renderModelChunk(chunk->getComponent<ChunkMesh>().get(), x, z);
			}
		}
	}
	m_chunkRenderer.endChunkRendering();
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
}

void RenderSystem::renderParticles(entityx::EntityManager& entities) {
	m_particleShader.begin();
	m_particleShader.setMatrix4("proj", m_camera.getCombinedMatrix().noTranslation());
	for(entityx::Entity entity : entities.entities_with_components<Particle>()){
		Particle* particle = entity.getComponent<Particle>().get();
		particle->vao.bind();
		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);
		particle->vao.unbind();
	}
	m_particleShader.end();
}

void RenderSystem::renderHitbox() {
	if(PlayerSystem::m_sIsRayHit) {
		glLineWidth(5.0f);
		m_hitBoxShader.begin();
		m_hitBoxShader.setMatrix4("combined", m_camera.getCombinedMatrix());
		m_hitBoxShader.setInt("worldPositionX", PlayerSystem::m_sHitBoxCube.x);
		m_hitBoxShader.setInt("worldPositionY", PlayerSystem::m_sHitBoxCube.y);
		m_hitBoxShader.setInt("worldPositionZ", PlayerSystem::m_sHitBoxCube.z);

		m_hitBoxRenderer.m_cubeVao.bind();
		glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, nullptr);
		m_hitBoxRenderer.m_cubeVao.unbind();
		m_hitBoxShader.end();
		glLineWidth(1.0f);
	}
}





