//
// Created by Viktor on 6.3.2021 г..
//

#ifndef TERRAIN_SYSTEM_H
#define TERRAIN_SYSTEM_H


#include "../../../lib/entityx/System.h"
#include "../../components/include/transform.h"
#include "../../data/include/world.h"
#include "world_generation.h"
#include "world_meshing.h"
#include "../../events/chunk_regeneration_event.h"


struct TerrainSystem : public entityx::System<TerrainSystem>, public entityx::Receiver<TerrainSystem> {

	const int EXPLORE_DISTANCE = 4;
	const int BUILD_DISTANCE = EXPLORE_DISTANCE - 1;

	World* m_pWorld;
	Transform* m_playerTransform;

	int m_lastPlayerX;
	int m_lastPlayerZ;

	/// Contents Generation
	WorldGeneration m_worldGeneration;
	WorldMeshing m_worldMeshing;

	void exploreNewCoordinates(entityx::EntityManager& entities, int chunkX, int chunkZ);
	void buildNewCoordinates(const int chunkX, const int chunkZ);

	TerrainSystem(World* world);
	~TerrainSystem();
	void configure(entityx::EntityManager& entities, entityx::EventManager& events);
	void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt);
	void receive(const ChunkRegenerationEvent& event);

};


#endif //TERRAIN_SYSTEM_H
