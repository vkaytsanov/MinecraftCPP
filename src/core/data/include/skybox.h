//
// Created by Viktor on 24.2.2021 г..
//

#ifndef SKYBOX_H
#define SKYBOX_H

#include "../../../lib/utils/include/texture.h"
#include "../../../lib/utils/include/texture_region.h"
#include "../../../lib/utils/openGL/include/vertex_array.h"
#include "../../../lib/utils/openGL/include/vertex_buffer.h"
#include "../../../lib/utils/include/texture_cube_map.h"

class Skybox {
private:
	VertexArray vao;
	VertexBuffer vbo;
public:
	Skybox();
	const VertexArray& getVao() const;
	TextureCubeMap textureCubeMap;
};


#endif //SKYBOX_H
