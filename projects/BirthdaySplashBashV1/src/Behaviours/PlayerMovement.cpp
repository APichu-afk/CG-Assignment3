#include <iostream>
#include "PlayerMovement.h"
#include "Gameplay/Application.h"
#include "Gameplay/Transform.h"
#include "Gameplay/Timing.h"

#include "GLFW/glfw3.h"

PlayerMovement::PlayerMovement()
{//Defualt constructor
}

PlayerMovement::~PlayerMovement()
{//Default destrcotor
}

//Working player Movement
void PlayerMovement::player1and2move(Transform& Player1, Transform& Player2, float dt)
{
	GLFWwindow* window = Application::Instance().Window;

	int controller1 = glfwJoystickPresent(GLFW_JOYSTICK_1);
	int controller2 = glfwJoystickPresent(GLFW_JOYSTICK_2);

	//player 1 controller
	if (controller1 == 1)
	{
		int axesCount;
		const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
		const char* name = glfwGetJoystickName(GLFW_JOYSTICK_1);

		if (axes[1] >= -1 && axes[1] <= -0.2) {
			Player1.MoveLocal(0.0f, 0.0f, 8.0f*dt);
		}
		if (axes[1] <= 1 && axes[1] >= 0.2) {
			Player1.MoveLocal(0.0f, 0.0f, -8.0f*dt);
		}

		if (axes[2] >= -1 && axes[2] <= -0.2) {
			Player1.RotateLocal(0.0f, 225.0f * dt, 0.0f);
		}
		if (axes[2] <= 1 && axes[2] >= 0.2) {
			Player1.RotateLocal(0.0f, -225.0f * dt, 0.0f);
		}
	
		/*if (name == "Wireless Controller")
		{
			if (axes[3] > -1)
			{
				Player1.RotateLocal(0.0f, -225.0f * dt, 0.0f);
			}
			if (axes[4] > -1)
			{
				Player1.RotateLocal(0.0f, 225.0f * dt, 0.0f);
			}
		}
		else
		{
			if (axes[4] > -1)
			{
				Player1.RotateLocal(0.0f, 225.0f * dt, 0.0f);
			}
			if (axes[5] > -1)
			{
				Player1.RotateLocal(0.0f, -225.0f * dt, 0.0f);
			}
		}*/
	}
	else
	{
		// Keyboard controls
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			Player1.MoveLocal(0.0f, 0.0f, 8.0f * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			Player1.RotateLocal(0.0f, 225.0f * dt, 0.0f);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			Player1.MoveLocal(0.0f, 0.0f, -8.0f * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			Player1.RotateLocal(0.0f, -225.0f * dt, 0.0f);
		}
	}
	//player2 controller
	if (controller2 == 1)
	{
		int axesCount2;
		const float* axes2 = glfwGetJoystickAxes(GLFW_JOYSTICK_2, &axesCount2);
		const char* name2 = glfwGetJoystickName(GLFW_JOYSTICK_2);

		if (axes2[1] >= -1 && axes2[1] <= -0.2) {
			Player2.MoveLocal(0.0f, 0.0f, 8.0f*dt);
		}
		if (axes2[1] <= 1 && axes2[1] >= 0.2) {
			Player2.MoveLocal(0.0f, 0.0f, -8.0f * dt);
		}
		
		if (axes2[2] >= -1 && axes2[2] <= -0.2) {
			Player2.RotateLocal(0.0f, 225.0f * dt, 0.0f);
		}
		if (axes2[2] <= 1 && axes2[2] >= 0.2) {
			Player2.RotateLocal(0.0f, -225.0f * dt, 0.0f);
		}
		/*std::cout << name2 << "\n";
		if (name2 == "Wireless Controller")
		{
			if (axes2[3] > -1)
			{
				Player2.RotateLocal(0.0f, -225.0f * dt, 0.0f);
			}
			if (axes2[4] > -1)
			{
				Player2.RotateLocal(0.0f, 225.0f * dt, 0.0f);
			}
		}
		else {
			if (axes2[4] > -1)
			{
				Player2.RotateLocal(0.0f, 225.0f * dt, 0.0f);
			}
			if (axes2[5] > -1)
			{
				Player2.RotateLocal(0.0f, -225.0f * dt, 0.0f);
			}
		}*/
	}
	else
	{
		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
			Player2.MoveLocal(0.0f, 0.0f, 8.0f * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
			Player2.RotateLocal(0.0f, 225.0f * dt, 0.0f);
		}
		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
			Player2.MoveLocal(0.0f, 0.0f, -8.0f * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
			Player2.RotateLocal(0.0f, -225.0f * dt, 0.0f);
		}
	}
	
}

//Only called if colliding with a wall or player 2
void PlayerMovement::Player1vswall(Transform& Player1, float dt)
{
	GLFWwindow* window = Application::Instance().Window;

	int controller1 = glfwJoystickPresent(GLFW_JOYSTICK_1);

	if (1 == controller1)
	{
		int axesCount;
		const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
		const char* name = glfwGetJoystickName(GLFW_JOYSTICK_1);

		if (axes[1] >= -1 && axes[1] <= -0.2) {
			Player1.MoveLocal(0.0f, 0.0f, -8.0f * dt);
		}
		if (axes[1] <= 1 && axes[1] >= 0.2) {
			Player1.MoveLocal(0.0f, 0.0f, 8.0f * dt);
		}
	}
	else {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			Player1.MoveLocal(0.0f, 0.0f, -8.0f * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			Player1.MoveLocal(0.0f, 0.0f, 8.0f * dt);
		}
	}
}

void PlayerMovement::Player2vswall(Transform& Player2, float dt)
{
	GLFWwindow* window = Application::Instance().Window;

	int controller2 = glfwJoystickPresent(GLFW_JOYSTICK_2);

	if (1 == controller2)
	{
		int axesCount2;
		const float* axes2 = glfwGetJoystickAxes(GLFW_JOYSTICK_2, &axesCount2);
		const char* name2 = glfwGetJoystickName(GLFW_JOYSTICK_2);

		if (axes2[1] >= -1 && axes2[1] <= -0.2) {
			Player2.MoveLocal(0.0f, 0.0f, -8.0f * dt);
		}
		if (axes2[1] <= 1 && axes2[1] >= 0.2) {
			Player2.MoveLocal(0.0f, 0.0f, 8.0f * dt);
		}
	}
	else {
		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
			Player2.MoveLocal(0.0f, 0.0f, -8.0f * dt);
		}
		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
			Player2.MoveLocal(0.0f, 0.0f, 8.0f * dt);
		}
	}
}

void PlayerMovement::Shoot(Transform& Bullet1, Transform& Player1, float dt, bool shoot)
{
	GLFWwindow* window = Application::Instance().Window;

	int controller1 = glfwJoystickPresent(GLFW_JOYSTICK_1);

	//player 1
	if (1 == controller1) {
		int buttonCount;
		int axesCount;
		const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
		const char* name = glfwGetJoystickName(GLFW_JOYSTICK_1);
		const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

		if (axes[5] >= 0.3 || shoot) {
			Bullet1.MoveLocal(0.0f, 0.0f, 10.0f * dt);
		}
		/*if (GLFW_PRESS == buttons[0] || shoot)
		{
			Bullet1.MoveLocal(0.0f, 0.0f, 10.0f * dt);
		}*/
		else
		{
			Bullet1.SetLocalPosition(Player1.GetLocalPosition());
			Bullet1.SetLocalRotation(Player1.GetLocalRotation());
		}
	}
	else {
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS || shoot) {
			Bullet1.MoveLocal(0.0f, 0.0f, 10.0f * dt);
		}
		else
		{
			Bullet1.SetLocalPosition(Player1.GetLocalPosition());
			Bullet1.SetLocalRotation(Player1.GetLocalRotation());
		}
	}
}

void PlayerMovement::Shoot2(Transform& Bullet2, Transform& Player2, float dt, bool shoot)
{
	GLFWwindow* window = Application::Instance().Window;

	int controller2 = glfwJoystickPresent(GLFW_JOYSTICK_2);

	//player 1
	if (1 == controller2) {
		int buttonCount;
		int axesCount2;
		const float* axes2 = glfwGetJoystickAxes(GLFW_JOYSTICK_2, &axesCount2);
		const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_2, &buttonCount);

		if (axes2[5] >= 0.3 || shoot)
		{
			Bullet2.MoveLocal(0.0f, 0.0f, 10.0f * dt);
		}
		else
		{
			Bullet2.SetLocalPosition(Player2.GetLocalPosition());
			Bullet2.SetLocalRotation(Player2.GetLocalRotation());
		}
	}
	else {
		if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS || shoot) {
			Bullet2.MoveLocal(0.0f, 0.0f, 10.0f * dt);
		}
		else
		{
			Bullet2.SetLocalPosition(Player2.GetLocalPosition());
			Bullet2.SetLocalRotation(Player2.GetLocalRotation());
		}
	}
}
