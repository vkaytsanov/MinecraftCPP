
#ifndef MINECRAFT
#define MINECRAFT


#include "../../lib/include/listener.h"
#include "../../lib/include/application.h"
#include "../../lib/utils/include/sprite_batch.h"

#include "game_state_manager.h"
#include "../data/include/asset_manager.h"
#include "../data/include/world.h"
#include "../../lib/entityx/entityx.h"


class Minecraft : public Listener {
public:
	World m_world;
	entityx::EntityX m_entityX;
	GameStateManager m_gameStateManager;
	bool m_isWireframe = false;

	Minecraft() = default;
	~Minecraft() override;
	// Inherited via Listener
	void create() override;
	void render() override;
	void pause() override;
	void resume() override;
	void resize(const int width, const int height) override;
};

#endif