#include "Shader.h"

// TODO :: Write the constructor with a other init methods declared in the .h file
Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	std::string vertexCode = readShaderFile(vertexFile);
	std::string fragmentCode = readShaderFile(fragmentFile);

	const char* vertexSource   = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	vertexID   = initVertexShader(vertexSource);
	fragmentID = initFragmentShader(fragmentSource);
	programID  = initShaderProgram();
}


// TODO: Fix the inputted issue with empty strings being returned == returned
std::string readShaderFile(const char* filename) {
	std::ifstream fileStream(filename);

	if (!fileStream.is_open()) {
		std::cerr << "ERROR::SHADER::FILE_NOT_FOUND: Failed to open file: " << filename << std::endl;
		return "";
	}

	std::stringstream sstr;
	sstr << fileStream.rdbuf();

	fileStream.close();

	return sstr.str();
}


// TODO :: Write the initVertex function == Complete
GLuint Shader::initVertexShader(const char* vertexShaderSource) {
	vertexID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexID, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexID);

	int success;
	glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);

	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(vertexID, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPLILATION_FAILED:\n " << infoLog << std::endl;
	}
	else {
		std::cout << "Vertex shader compiled successfully. Vertex ID: " << vertexID << std::endl;
	}

	return vertexID;
}

// TODO :: Write the initFragment function == Complete
GLuint Shader::initFragmentShader(const char* fragmentShaderSource) {
	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentID, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentID);

	
	int success;
	glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
	
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(fragmentID, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPLILATION_FAILED:\n " << infoLog << std::endl;
	}
	else {
		std::cout << "Fragment shader compiled successfully. Fragment ID: " << fragmentID << std::endl;
	}

	return fragmentID;
}

// TODO :: Write the initShaderPorgram function == Complete
GLuint Shader::initShaderProgram() {
	programID = glCreateProgram();
	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragmentID);
	glLinkProgram(programID);

	int success;
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED:\n " << infoLog << std::endl;

	} else {
		std::cout << "Shader program linked successfully. Program ID: " << programID << std::endl;
	}

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);

	return programID;
}

void Shader::Activate() {
	glUseProgram(programID);
}

void Shader::Delete() {
	glDeleteProgram(programID);
}
