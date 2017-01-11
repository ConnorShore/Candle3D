#include "Camera.h"

#include "glm\gtc\matrix_transform.hpp"
#include "SDL\SDL.h"

Camera::Camera() : _mouseLook(false)
{
}


Camera::~Camera()
{
}

void Camera::init(Window& window, int screenWidth, int screenHeight)
{
	_window = window;
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	resetCamera();
}

void Camera::update(InputManager& inputManager)
{
	viewing.viewMatrix = updateViewMatrix();
	viewing.projectionMatrix = updateProjectionMatrix();

	lookCalculations();

	if (_mouseLook)
		mouseLook(inputManager);
	else
		showCursor();
}

glm::mat4 Camera::updateViewMatrix()
{
	glm::mat4 view = glm::lookAt(transform.position, transform.position + transform.direction, transform.up);
	return view;
}

glm::mat4 Camera::updateProjectionMatrix()
{
	glm::mat4 projection = glm::perspective(viewing.fov, (float)_screenWidth / (float)_screenHeight, viewing.zNear, viewing.zFar);
	return projection;
}

void Camera::lookCalculations()
{
	transform.direction = glm::vec3(
		cos(transform.pitch) * sin(transform.yaw),
		sin(transform.pitch),
		cos(transform.pitch) * cos(transform.yaw));

	transform.right = glm::vec3(
		sin(transform.yaw - 3.14f / 2.0f),
		0,
		cos(transform.yaw - 3.14f / 2.0f));

	transform.up = glm::cross(transform.right, transform.direction);
}

void Camera::mouseLook(InputManager& inputManager)
{
	hideCursor();

	int mousePosX = inputManager.mousePos.x;
	int mousePosY = inputManager.mousePos.y;

	static int midWidth = _screenWidth / 2;
	static int midHeight = _screenHeight / 2;

	SDL_GetMouseState(&mousePosX, &mousePosY);
	SDL_WarpMouseInWindow(_window.getWindow(), midWidth, midHeight);

	transform.yaw += transform.sensitivity * float(midWidth - inputManager.mousePos.x);
	transform.pitch += transform.sensitivity * float(midHeight - inputManager.mousePos.y);

	if (transform.pitch >= MAX_ANGLE)
		transform.pitch = MAX_ANGLE;

	if (transform.pitch <= -MAX_ANGLE)
		transform.pitch = -MAX_ANGLE;
}


void Camera::resetCamera()
{
	showCursor();

	transform.direction = glm::vec3(0.0f, 0.0f, -1.0f);
	transform.position = glm::vec3(0.0f, 0.0f, 3.0f);
	transform.up = glm::vec3(0.0f, 1.0f, 0.0f);
	transform.sensitivity = 0.0025f;
	transform.yaw = 3.1415f;
	transform.pitch = 0.0f;

	viewing.fov = 65.0f;
	viewing.zNear = 0.1f;
	viewing.zFar = 500.0f;
}

void Camera::resetView()
{
	showCursor();

	transform.direction = glm::vec3(0.0f, 0.0f, -1.0f);
	transform.up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::showCursor()
{
	SDL_ShowCursor(1);
}

void Camera::hideCursor()
{
	SDL_ShowCursor(0);
}

void Camera::translate(Translate direction, float speed)
{
	switch (direction) {
		case Translate::FORWARD:
			transform.position += speed * transform.direction;
			break;
		case Translate::BACK:
			transform.position -= speed * transform.direction;
			break;
		case Translate::LEFT:
			transform.position -= speed * transform.right;
			break;
		case Translate::RIGHT:
			transform.position += speed * transform.right;
			break;
	}
}