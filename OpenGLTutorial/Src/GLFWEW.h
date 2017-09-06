/**
*	@file GLFWEW
*/

//#pragma once
#ifndef GLFWEW_INCLUDED
#define GLFWEW_INCLUDED
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "glm/gtc/matrix_transform.hpp"
#include "GamePad.h"

namespace GLFWEW
{
	/**
	*	GLFWとGLEWのラッパークラス
	*/
	class Window
	{
	public:
		static Window& Instance();
		bool Init(int w, int h, const char* title);
		bool ShowldClose() const;
		void SwapBuffers() const;
		const GamePad& GetGamePad() const;
		void UpdateGamePad();

	private:
		Window();
		~Window();
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		bool isGLFWInitialized;
		bool isInitialized;
		GLFWwindow* window;
		GamePad gamepad;
	};
}	//namespace GLFWEW

#endif // !GLFWEW_INCLUDED