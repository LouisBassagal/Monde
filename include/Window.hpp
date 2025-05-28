#pragma once

#include <imgui.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <Camera.hpp>
#include <memory>

#include <ShaderReader.hpp>

#include <Primitives/Pyramid.hpp>
#include <Primitives/Cube.hpp>

#include <Lights/ILight.hpp>

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
		void updateLights(unsigned int program);

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

		std::vector<std::unique_ptr<IPrimitive>> m_primitives;
		std::vector<std::unique_ptr<ILight>> m_lights;
};
