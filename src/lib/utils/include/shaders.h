//
// Created by Viktor on 27.12.2020 г..
//

#ifndef SHADERS_H
#define SHADERS_H


#include "GL/glew.h"
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
};


#endif //SHADERS_H
