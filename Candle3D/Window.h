#pragma once

#include <SDL\SDL.h>
#include <glm\glm.hpp>
#include <string>

enum class WindowFlags
{
	NONE,
	WINDOWED,
	FULLSCREEN,
	FULLSCREEN_WINDOWED
};

class Window
{
public:
	Window();
	~Window();

	void createWindow(const std::string& title, int x, int y, int width, int height, WindowFlags flags = WindowFlags::NONE);
	void setBackgroundColor(glm::vec4& color);
	void initRender();
	void swapWindow();
	void destroyWindow();

	int getWidth() const { return _width; }
	int getHeight() const { return _height; }
	glm::vec4 getBackgroundColor() const { return _backgroundColor; }
	SDL_Window* getWindow() { return _window; }

private:
	SDL_Window* _window;
	glm::vec4 _backgroundColor;
	int _width, _height;
};

