#pragma once

#include <imgui.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <Primitives/Triangle.hpp>

#include <../include/ShaderReader.hpp>

class Window {
	public:
		Window();
		~Window();

		void loop();
		void createShaderProgram();

		GLFWwindow *getWindow();

		void test();

	private:
		unsigned int m_shaderProgram;

		GLFWwindow *m_window;

		std::vector<Primitive *> m_primitives;
};
