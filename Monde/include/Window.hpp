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

class Window {
	public:
		Window();
		~Window();

		void loop();
		void createShaderProgram();

		GLFWwindow *getWindow();

		void test();
		void test2();

	private:
		unsigned int m_shaderProgram;

		GLFWwindow *m_window;

		Camera m_camera;

		std::vector<Primitive *> m_primitives;
};
