//
// Created by Viktor on 27.12.2020 г..
//

#ifndef SHADERS_H
#define SHADERS_H


#include "GL/glew.h"
#include "../geometry/include/matrix4.h"
#include <fstream>
static const std::string shadersPath = "../src/assets/shaders/";

class Shaders {
private:

    const char* vertexShader;
    const char* fragShader;
    unsigned int vertexShaderID;
    unsigned int fragShaderID;
    unsigned int shaderProgram;

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

	int getUniformLocation(const char* name);
	void setMatrix4(const char* name, Matrix4f mat);
	void setInt(const char* name, int number);
};


#endif //SHADERS_H
