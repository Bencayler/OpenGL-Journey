#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string readShaderFile(const char* filename);

class Shader {
	private:
		GLuint programID;
		GLuint vertexID;
		GLuint fragmentID;

	public:


		GLuint initVertexShader(const char* vertexShaderSource);
		GLuint initFragmentShader(const char* fragmentShaderSource);
		GLuint initShaderProgram();
		
		Shader(const char* vertexFile, const char* fragmentFile);

		void Activate();
		void Delete();

};

#endif
