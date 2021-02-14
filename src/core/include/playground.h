
#ifndef PLAYGROUND
#define PLAYGROUND


#include "../../lib/include/listener.h"
#include "../../lib/include/application.h"
#include "../../lib/utils/include/universal_viewport.h"
#include "../../lib/utils/include/shaders.h"
#include "../../lib/utils/include/sprite_batch.h"
#include "../../lib/utils/include/first_person_camera_controller.h"
#include "../objects/include/triangle.h"
#include "../objects/include/texture_object.h"


class Playground : public Listener {
private:
    unsigned int vertexArray;
    Shaders* textureShaders;
    Shaders* colorShaders;
    UniversalViewport* viewport;
    SpriteBatch* batch;
    FirstPersonCameraController* cameraController;
    TextureObject* cone;
    TextureObject* cube;

public:
    Playground() = default;
    ~Playground() override;
    // Inherited via Listener
    void create() override;
    void render() override;
    void pause() override;
    void resume() override;
    void resize(const int& width, const int& height) override;
};

#endif