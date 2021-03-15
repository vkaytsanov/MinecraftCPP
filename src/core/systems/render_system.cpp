//
// Created by Viktor on 7.3.2021 г..
//

#include "include/render_system.h"
#include "../components/include/player_controller.h"


RenderSystem::RenderSystem(World* world) : m_pWorld(world),
                                           m_skyboxShader("skybox/shader.vert", "skybox/shader.frag"),
                                           m_camera(70){

}

void RenderSystem::configure(entityx::EntityManager& entities, entityx::EventManager& events) {
	for (const auto& entity : entities.entities_with_components<PlayerController>()) {
		m_pPlayerTransform = entity.getComponent<Transform>().get();
	}

	m_camera.m_pTransform = m_pPlayerTransform;

}

void RenderSystem::preUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
//	m_camera.m_pTransform->position = m_pPlayerTransform->position + Vector3f(0, 2, 0);
//	m_camera.m_pTransform->rotation = m_pPlayerTransform->rotation;
}

void RenderSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
	// follow the player
	m_camera.update(true);
	renderSkybox();
	renderWorld();
}

void RenderSystem::renderSkybox() {
	glDepthMask(GL_FALSE);

	m_skyboxShader.begin();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_pSkybox.textureCubeMap.getBuffer());
	const Matrix4f& mat = m_camera.getCombinedMatrix().noTranslation();
	m_skyboxShader.setMatrix4("proj", mat);
	m_skyboxShader.setInt("texSkybox", 0);

	m_pSkybox.getVao().bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	m_pSkybox.getVao().unbind();

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




