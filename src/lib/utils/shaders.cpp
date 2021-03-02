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


std::string Shaders::readFromFile(const std::string& path) {
	std::ifstream stream(path);
	std::string line;
	std::stringstream ss;
	while (std::getline(stream, line)) {
		ss << line << "\n";
	}

	stream.close();

	return ss.str();
}

void Shaders::compile() {
	if (vertexShader == nullptr) {
		Lib::app->error("Shaders", "VertexShader is null");
		exit(-1);
	}
	if (fragShader == nullptr) {
		Lib::app->error("Shaders", "FragShader is null");
		exit(-1);
	}

	// compiling first the vertex shader
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &vertexShader, nullptr);
	glCompileShader(vertexShaderID);

	int status;
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		int log_length = 0;
		char message[1024];
		glGetShaderInfoLog(vertexShaderID, 1024, &log_length, message);
		// Write the error to a log
		Lib::app->error("VertexShaderError", message);
	}
	else {
		Lib::app->log("VertexShader", "compiled successfully");
	}

	// compiling now the fragment shader
	fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShaderID, 1, &fragShader, nullptr);
	glCompileShader(fragShaderID);

	status = GL_FALSE;
	glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		int log_length = 0;
		char message[1024];
		glGetShaderInfoLog(fragShaderID, 1024, &log_length, message);
		// Write the error to a log
		Lib::app->error("FragmentShaderError", message);
		exit(-1);
	}
	else {
		Lib::app->log("FragmentShader", "compiled successfully");
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShaderID);
	glAttachShader(shaderProgram, fragShaderID);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		int log_length = 0;
		char message[1024];
		glGetProgramInfoLog(shaderProgram, 1024, &log_length, message);
		// Write the error to a log
		Lib::app->error("LinkingShaderProgramError", message);
		exit(-1);
	}
	else {
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
	Lib::app->log("Shaders", "deleting");
	glUseProgram(0);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragShaderID);
	glDeleteProgram(shaderProgram);
}

unsigned int Shaders::getProgram() {
	return shaderProgram;
}

GLint Shaders::getUniformLocation(std::string& name) {
	if (uniforms.find(name) == uniforms.end()) {
		int res = glGetUniformLocation(shaderProgram, name.c_str());
		if (res == -1) {
			Lib::app->error("uniforms", ("invalid location on " + name).c_str());
			exit(-1);
		}
		uniforms[name] = res;
	}


	return uniforms[name];
}

void Shaders::setMatrix4(std::string name, Matrix4f& mat) {
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, mat.a);
}

void Shaders::setInt(std::string name, int number) {
	glUniform1i(getUniformLocation(name), number);
}

void Shaders::setFloat(std::string name, float number) {
	glUniform1f(getUniformLocation(name), number);
}

void Shaders::setVector3f(std::string name, float x, float y, float z) {
	glUniform3f(getUniformLocation(name), x, y, z);
}

void Shaders::setVector3f(std::string name, Vector3f& vec) {
	glUniform3f(getUniformLocation(name), vec.x, vec.y, vec.z);
}










