//
// Created by Viktor on 9.1.2021 г..
//

#include "include/texture_object.h"
#include "../../lib/utils/geometry/include/vector3.h"
#include "../../lib/utils/geometry/include/vector2.h"
#include "../../lib/include/lib.h"
#include "include/object_loader.h"
#include <vector>
#include <cassert>

TextureObject::TextureObject(const char *objFile) : Object() {

    texture = new GLTexture("../res/uvtemplate.bmp");

    std::vector<Vector3f> out_vertices;
    std::vector<Vector2f> out_uvs;
    std::vector<Vector3f> out_normals;

    loadOBJ(objFile, out_vertices, out_uvs, out_normals);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, out_vertices.size() * sizeof(Vector3f), &out_vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, out_uvs.size() * sizeof(Vector2f), &out_uvs[0], GL_STATIC_DRAW);

    verticesSize = out_vertices.size();


}

void TextureObject::draw() {
    unsigned int textureID = glGetUniformLocation(shaderID, "myTextureSampler");
    if(textureID == - 1){
        Lib::app->error("uniforms", "invalid location");
    }
    else{
        glUniform1i(textureID, 0);
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->getBuffer());

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            false,
            0,
            nullptr
    );


    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glVertexAttribPointer(
            2,
            2,
            GL_FLOAT,
            false,
            0,
            nullptr
    );

    glDrawArrays(GL_TRIANGLES, 0, verticesSize);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(2);
}

TextureObject::~TextureObject() {
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &uvBuffer);
    delete texture;

}


