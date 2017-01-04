#include "MainGame.h"
#include "ResourceManager.h"

#include <SDL\SDL.h>
#include <GL\glew.h>


GLfloat vertices[] = {
	// Positions          // Colors           // Texture Coords
	0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // Top Right
	0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // Bottom Right
	-0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f    // Top Left 
};

GLuint indices[] = {  // Note that we start from 0!
	0, 1, 3,
	3, 2, 1
};

MainGame::MainGame() : _isRunning(true), _screenWidth(1280), _screenHeight(720)
{

}

MainGame::~MainGame()
{

}

void MainGame::init()
{
	_window.createWindow("Engine Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight);
	_window.setBackgroundColor(glm::vec4(30, 10, 80, 255));

	glGenVertexArrays(1, &_vaoID);
	glGenBuffers(1, &_vboID);
	glGenBuffers(1, &_eboID);

	glBindVertexArray(_vaoID);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	_staticShader.init("Shaders/staticShader.vert", "Shaders/staticShader.frag");
	_staticShader.bindAttributes();

	_texture = ResourceManager::loadTexture("Textures/test.png");
}

void MainGame::input()
{

}

void MainGame::update()
{
	_inputManager.update();
}

void MainGame::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(_vaoID);

	_staticShader.start();
	_staticShader.getUniformLocations();
	_staticShader.loadTexture();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture.id);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);

	_staticShader.stop();

	glBindVertexArray(0);

	_window.swapWindow();
}

void MainGame::gameLoop()
{
	_timer.TimeInit();

	while (_isRunning) {
		_timer.FpsLimitInit();
		_timer.calcDeltaTime();

		update();
		input();
		render();

		_timer.LimitFPS(60.0f);
		_timer.CalculateFPS(false);
	}
}

void MainGame::cleanUp()
{
	_staticShader.cleanUp();

	SDL_Quit();
	exit(0);
}

void MainGame::run()
{
	init();
	gameLoop();
	cleanUp();
}