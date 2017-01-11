#include "RenderSystem.h"

#include <sstream>
#include <string>


RenderSystem::RenderSystem()
{
}


RenderSystem::~RenderSystem()
{
}

void RenderSystem::init()
{
	
}

void RenderSystem::render(Model& model)
{
	GLuint diffuseNum = 1, specularNum = 1;
	int numMeshes = model.getMeshes().size();

	for (int i = 0; i < numMeshes; i++) {
		Mesh mesh = model.getMeshes()[i];
		for (int j = 0; j < mesh.textures.size(); j++) {
			glActiveTexture(GL_TEXTURE0 + j);

			std::stringstream stream;
			std::string number;
			std::string name = mesh.textures[j].type;

			if (name == "texture_diffuse") {
				stream << diffuseNum++;
			}
			else if (name == "texture_specular") {
				stream << specularNum++;
			}

			number = stream.str();

			glUniform1f(glGetUniformLocation(_staticShader.getProgram(), ("material." + name + number).c_str()), j);
			glBindTexture(GL_TEXTURE_2D, mesh.textures[j].id);
		}

		glActiveTexture(GL_TEXTURE0);

		//Draw Mesh
		glBindVertexArray(mesh.getVaoID());
		glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}
