//
// Created by Viktor on 27.12.2020 г..
//

#ifndef SHADERS_H
#define SHADERS_H


#include "GL/glew.h"
#include "../geometry/include/matrix4.h"
#include <unordered_map>
#include <fstream>

static const std::string shadersPath = "../src/assets/shaders/";

class Shaders {
private:

	const char* vertexShader;
	const char* fragShader;
	unsigned int vertexShaderID;
	unsigned int fragShaderID;
	unsigned int shaderProgram;

	std::unordered_map<std::string, GLint> uniforms;

public:
	std::string parsedVertexShader;
	std::string parsedFragmentShader;
	Shaders(const std::string& vertexShader, const std::string& fragShader);
	~Shaders();
	std::string readFromFile(const std::string& path);
	void compile();
	void begin();
	void end();
	unsigned int getProgram();

	GLint getUniformLocation(std::string& name);
	void setMatrix4(std::string name, Matrix4f& mat);
	void setInt(std::string name, int number);
	void setFloat(std::string name, float number);
	void setVector3f(std::string name, float x, float y, float z);
	void setVector3f(std::string name, Vector3f& vec);
};


#endif //SHADERS_H
