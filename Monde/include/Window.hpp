#pragma once

#include <imgui.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <Primitives/Triangle.hpp>
#include <Primitives/Pyramid.hpp>
#include <Camera.hpp>

#include <../include/ShaderReader.hpp>

struct Mouse {
	public:
		float x{ 0.f };
		float y{ 0.f };

		float oldX{ 0.f };
		float oldY{ 0.f };
};

class Window {
	public:
		Window();
		~Window();

		void loop();
		void createShaderProgram();

		GLFWwindow *getWindow();

		Camera *getCamera();
		Mouse *getMouse();

		void test();
		void test2();

	private:

		void checkInput();

		unsigned int m_shaderProgram;

		float m_deltaTime{ 0.f };
		float m_lastFrame{ 0.f };
		float m_currentFrame{ 0.f };

		GLFWwindow *m_window;

		Camera m_camera;
		Mouse m_mouse;

		std::vector<Primitive *> m_primitives;
};
