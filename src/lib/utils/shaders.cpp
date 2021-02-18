//
// Created by Viktor on 27.12.2020 г..
//

#include <string>
#include <sstream>
#include "include/shaders.h"
#include "../include/lib.h"



Shaders::Shaders(const std::string& vertexShaderPath, const std::string& fragShaderPath) {
    // assigning to temp std::string, else we get garbage value of the variable that just left the stack
    parsedVertexShader = readFromFile(shadersPath + vertexShaderPath);
    vertexShader = parsedVertexShader.c_str();

	parsedFragmentShader = readFromFile(shadersPath + fragShaderPath);
    fragShader = parsedFragmentShader.c_str();

//    Lib::app->log("VertexShader", vertexShader);
//    Lib::app->log("FragShader", fragShader);

    compile();
}



std::string Shaders::readFromFile(const std::string &path) {
    std::ifstream stream(path);
    std::string line;
    std::stringstream ss;
    while(std::getline(stream, line)){
        ss << line << "\n";
    }

    stream.close();

    return ss.str();
}

void Shaders::compile() {
    if(vertexShader == nullptr){
        Lib::app->error("Shaders", "VertexShader is null");
        exit(-1);
    }
    if(fragShader == nullptr){
        Lib::app->error("Shaders", "FragShader is null");
        exit(-1);
    }

    // compiling first the vertex shader
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, &vertexShader, nullptr);
    glCompileShader(vertexShaderID);

    int status;
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE){
        int log_length = 0;
        char message[1024];
        glGetShaderInfoLog(vertexShaderID, 1024, &log_length, message);
        // Write the error to a log
        Lib::app->error("VertexShaderError", message);
    }
    else{
        Lib::app->log("VertexShader", "compiled successfully");
    }

    // compiling now the fragment shader
    fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShaderID, 1, &fragShader, nullptr);
    glCompileShader(fragShaderID);

    status = GL_FALSE;
    glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE){
        int log_length = 0;
        char message[1024];
        glGetShaderInfoLog(fragShaderID, 1024, &log_length, message);
        // Write the error to a log
        Lib::app->error("FragmentShaderError", message);
        exit(-1);
    }
    else{
        Lib::app->log("FragmentShader", "compiled successfully");
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderID);
    glAttachShader(shaderProgram, fragShaderID);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if(status != GL_TRUE){
        int log_length = 0;
        char message[1024];
        glGetProgramInfoLog(shaderProgram, 1024, &log_length, message);
        // Write the error to a log
        Lib::app->error("LinkingShaderProgramError", message);
        exit(-1);
    }
    else{
        Lib::app->log("LinkingShaderProgram", "successful");
    }

}

void Shaders::begin() {
    glUseProgram(shaderProgram);
}

void Shaders::end() {
    glUseProgram(0);
}

Shaders::~Shaders() {
    glUseProgram(0);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragShaderID);
    glDeleteProgram(shaderProgram);
}

unsigned int Shaders::getProgram() {
    return shaderProgram;
}

int Shaders::getUniformLocation(const char* name) {
	int res = glGetUniformLocation(shaderProgram, name);

	if(res == -1){
		Lib::app->error("uniforms", "invalid location");
		exit(-1);
	}
	return res;
}

void Shaders::setMatrix4(const char* name, Matrix4f mat) {
	glUniformMatrix4fv(getUniformLocation(name), 1, false, mat.a);
}

void Shaders::setInt(const char* name, int number) {
	glUniform1i(getUniformLocation(name), number);
}










