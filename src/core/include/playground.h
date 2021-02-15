
#ifndef PLAYGROUND
#define PLAYGROUND


#include "../../lib/include/listener.h"
#include "../../lib/include/application.h"
#include "../../lib/utils/include/universal_viewport.h"
#include "../../lib/utils/include/shaders.h"
#include "../../lib/utils/include/sprite_batch.h"
#include "../../lib/utils/include/first_person_camera_controller.h"
#include "../data/include/cube.h"
#include "../data/include/data_system.h"
#include "../data/cubes/include/grass_cube.h"


class Playground : public Listener {
private:
    UniversalViewport* viewport;
    SpriteBatch* batch;
    FirstPersonCameraController* cameraController;
    DataSystem* dataSystem;
	GrassCube* cube;
	bool isWireframe = false;
public:
    Playground() = default;
    ~Playground() override;
    // Inherited via Listener
    void create() override;
    void render() override;
    void pause() override;
    void resume() override;
    void resize(const int width, const int height) override;
};

#endif