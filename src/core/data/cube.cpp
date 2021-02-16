//
// Created by Viktor on 14.2.2021 г..
//

#include "include/cube.h"
#include "include/cube_data.h"

Cube::Cube(TextureRegion textureRegion, Shaders* shaders, int sides)
		: Entity(shaders), textureRegion(textureRegion){
	GLfloat* uvs = textureRegion.getUVs();
	if(sides == 3){
		for(int i = 0; i < 6 * 4 * 2; i++){
			uvs[i] *= uvs3side[i];
		}
	}
	this->shaders = shaders;
	Entity::generateBuffers(vertices, normals, uvs, indices, 6 * 4 * 3, 6 * 6);
	delete uvs;
}

void Cube::draw() {

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureRegion.getTexture()->getBuffer());

	glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);

}

Cube::~Cube() {
	glDeleteBuffers(1, &indicesBuffer);
	glDeleteVertexArrays(1, &vertexArrayObject);
}


