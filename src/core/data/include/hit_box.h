//
// Created by Viktor on 19.3.2021 г..
//

#ifndef HIT_BOX_H
#define HIT_BOX_H

#include "../../../lib/utils/openGL/include/vertex_array.h"
#include "../../../lib/utils/openGL/include/vertex_buffer.h"
#include "../../../lib/utils/openGL/include/index_buffer.h"
#include "../../../lib/utils/geometry/include/vector3.h"
#include "../../../lib/utils/include/shaders.h"
#include "../../../lib/utils/camera/include/camera.h"
#include "../../systems/include/chunk_renderer.h"

class HitBox {
private:
	VertexBuffer m_cubeVbo;
	IndexBuffer m_cubeIbo;
public:
	VertexArray m_cubeVao;
	HitBox();

};


#endif //HIT_BOX_H
