
#ifndef PLAYGROUND
#define PLAYGROUND


#include "../../lib/include/listener.h"
#include "../../lib/include/application.h"
#include "../../lib/utils/include/sprite_batch.h"

#include "../data/include/data_system.h"
#include "../graphics/include/graphics_system.h"
#include "game_state_manager.h"
#include "../logic/include/logic_system.h"


class Minecraft : public Listener {
public:
	SpriteBatch* batch;
	GameStateManager* gameStateManager;
	DataSystem* dataSystem;
	GraphicsSystem* graphicsSystem;
	LogicSystem* logicSystem;

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