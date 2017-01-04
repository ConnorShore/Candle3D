#include "ShaderProgram.h"

#include <vector>
#include <fstream>


ShaderProgram::ShaderProgram()
{
}

GLuint ShaderProgram::loadShader(const std::string& file, GLuint type)
{
	//read shader from file
	std::string input;
	std::ifstream shaderStream(file, std::ios::in);
	if (shaderStream.is_open()) {
		std::string line;
		while (std::getline(shaderStream, line))
			input += "\n" + line;
		shaderStream.close();
	}

	GLuint shaderID = glCreateShader(type);

	GLint Result = GL_FALSE;
	int InfoLogLength;

	//Compile shader
	if (type == GL_VERTEX_SHADER)
		printf("Compiling vertex shader: %s\n", file.c_str());
	else if (type == GL_FRAGMENT_SHADER)
		printf("Compiling fragment shader: %s\n", file.c_str());

	const char* shaderPointer = input.c_str();

	glShaderSource(shaderID, 1, &shaderPointer, NULL);
	glCompileShader(shaderID);

	//Check shader
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(shaderID, InfoLogLength, NULL, ShaderErrorMessage.data());
	if(ShaderErrorMessage.data() != NULL) fprintf(stdout, "%s\n", ShaderErrorMessage.data());

	return shaderID;
}

void ShaderProgram::init(const std::string& vertexFile, const std::string& fragmentFile)
{
	VERTEX_FILE = vertexFile;
	FRAGMENT_FILE = fragmentFile;

	_vertexShaderID = loadShader(vertexFile, GL_VERTEX_SHADER);
	_fragmentShaderID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	_programID = glCreateProgram();

	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);
	glLinkProgram(_programID);
	glValidateProgram(_programID);

	//Check program
	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetProgramiv(_programID, GL_LINK_STATUS, &Result);
	glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage(InfoLogLength, int(1));
	glGetProgramInfoLog(_programID, InfoLogLength, NULL, ProgramErrorMessage.data());
	if(ProgramErrorMessage.data() != NULL) fprintf(stdout, "%s\n", ProgramErrorMessage.data());
}

void ShaderProgram::start()
{
	glUseProgram(_programID);
}

void ShaderProgram::stop()
{
	glUseProgram(0);
}

void ShaderProgram::cleanUp()
{
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
	glDeleteProgram(_programID);
}

void ShaderProgram::bindAttribute(int attrib, std::string name)
{
	glBindAttribLocation(_programID, attrib, name.c_str());
}

GLuint ShaderProgram::getUniformLocation(std::string name)
{
	return glGetUniformLocation(_programID, name.c_str());
}

void ShaderProgram::loadInt(int location, int value)
{
	glUniform1i(location, value);
}

void ShaderProgram::loadFloat(int location, float value)
{
	glUniform1f(location, value);
}

void ShaderProgram::loadVector2f(int location, glm::vec2& vector)
{
	glUniform2f(location, vector.x, vector.y);
}

void ShaderProgram::loadVector3f(int location, glm::vec3& vector)
{
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void ShaderProgram::loadVector4f(int location, glm::vec4& vector)
{
	glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}

void ShaderProgram::loadMatrix4f(int location, glm::mat4& matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, &(matrix[0][0]));
}

ShaderProgram::~ShaderProgram()
{
}