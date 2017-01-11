#pragma once

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	void init(const std::string& vertexFile, const std::string& fragmentFile);
	void start();
	void stop();
	void cleanUp();

	std::string getVertexFile() const { return VERTEX_FILE; }
	std::string getFragmentFile() const { return FRAGMENT_FILE; }

	GLuint getProgram() { return _programID; }

protected:
	GLuint getUniformLocation(std::string name);
	void bindAttribute(int attrib, std::string name);
	void loadInt(int location, int value);
	void loadFloat(int location, float value);
	void loadVector2f(int location, glm::vec2& vector);
	void loadVector3f(int location, glm::vec3& vector);
	void loadVector4f(int location, glm::vec4& vector);
	void loadMatrix4f(int location, glm::mat4& matrix);

	virtual void bindAttributes() = 0;
	virtual void getUniformLocations() = 0;

	std::string VERTEX_FILE, FRAGMENT_FILE;

private:
	GLuint _programID;
	GLuint _vertexShaderID, _fragmentShaderID;

	GLuint loadShader(const std::string& file, GLuint type);
};