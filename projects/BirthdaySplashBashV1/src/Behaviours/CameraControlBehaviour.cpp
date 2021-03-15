#include "CameraControlBehaviour.h"

#include "Gameplay/Application.h"
#include "Gameplay/Timing.h"
#include "Gameplay/Transform.h"


void CameraControlBehaviour::OnLoad(entt::handle entity) {
	_initial = entity.get<Transform>().GetLocalRotationQuat();
}

void CameraControlBehaviour::Update(entt::handle entity)
{
	float dt = Timing::Instance().DeltaTime;
	GLFWwindow* window = Application::Instance().Window;
	double mx, my;
	glfwGetCursorPos(window, &mx, &my);
	Transform& transform = entity.get<Transform>();

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
		if (!_isPressed) {
			_isPressed = true;
			_prevMouseX = mx;
			_prevMouseY = my;
		}

		_rotationX += static_cast<float>(mx - _prevMouseX) * 0.5f;
		_rotationY += static_cast<float>(my - _prevMouseY) * 0.3f;
		glm::quat rotX = glm::angleAxis(glm::radians(_rotationX), glm::vec3(0, 0, 1));
		glm::quat rotY = glm::angleAxis(glm::radians(_rotationY), glm::vec3(1, 0, 0));
		transform.SetLocalRotation(rotX * rotY);
		
		_prevMouseX = mx;
		_prevMouseY = my;
	} else {
		_isPressed = false;
	}

	glm::vec3 movement = glm::vec3(0.0f);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		movement.x += -5.0f * dt;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		movement.x += 5.0f * dt;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		movement.z += -5.0f * dt;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		movement.z += 5.0f * dt;
	}
	transform.MoveLocal(movement);
}
