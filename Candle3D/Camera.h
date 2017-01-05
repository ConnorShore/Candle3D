#pragma once

#include "glm\glm.hpp"
#include "InputManager.h"
#include "Window.h"

enum Translate
{
	FORWARD, BACK, LEFT, RIGHT
};

struct Transform
{
	glm::vec3 position, direction, right, up;
	float pitch, yaw, roll, sensitivity;
};

struct Viewing
{
	glm::mat4 viewMatrix, projectionMatrix;
	float fov, zNear, zFar;
};

class Camera
{
public:
	Camera();
	~Camera();

	void init(Window& window, int screenWidth, int screenHeight);
	void update(InputManager& inputManager);
	void resetCamera();
	void resetView();
	void showCursor();
	void hideCursor();

	void translate(Translate direction, float speed);

	void setMouseLook(bool look) { _mouseLook = look; }

	//--------------------//

	Transform transform;
	Viewing viewing;

private:
	const float MAX_ANGLE = 85.0f;
	const float MIN_ANGLE = -85.0f;

	Window _window;

	int _screenWidth, _screenHeight;

	bool _mouseLook;

	//--------------------//

	glm::mat4 updateViewMatrix();
	glm::mat4 updateProjectionMatrix();

	void lookCalculations();
	void mouseLook(InputManager& inputManager);
};

