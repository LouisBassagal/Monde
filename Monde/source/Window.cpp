#include "Window.hpp"
#include <iostream>

Window::Window() {
	m_window = glfwCreateWindow(1280, 720, "GLFW Window", nullptr, nullptr);
	
}

Window::~Window() {
	if (m_window) {
		glfwDestroyWindow(m_window);
		m_window = nullptr;
	}
	glfwTerminate();
}

GLFWwindow *Window::getWindow() {
	return m_window;
}

void Window::test() {
	auto triangle = new Triangle();
	m_primitives.push_back(triangle);
}

void Window::loop() {
	glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(m_shaderProgram);

	for each(auto primitive in m_primitives) {
		primitive->draw();
	}
}

void Window::createShaderProgram() {
	const std::string vertexShaderSource = ShaderReader::readShader(VERTEX_FILEPATH);
	const std::string fragmentShaderSource = ShaderReader::readShader(FRAGMENT_FILEPATH);
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	const char* vertexShaderSourceCStr = vertexShaderSource.c_str();

	glShaderSource(vertexShader, 1, &vertexShaderSourceCStr, nullptr);
	glCompileShader(vertexShader);

	int success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "Vertex Shader Load Failed\n" << infoLog << std::endl;
	} else {
		std::cout << "Vertex Shader Loaded Successfully" << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char* fragmentShaderSourceCStr = fragmentShaderSource.c_str();

	glShaderSource(fragmentShader, 1, &fragmentShaderSourceCStr, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "Fragment Shader Load Failed\n" << infoLog << std::endl;
	} else {
		std::cout << "Fragment Shader Loaded Successfully" << std::endl;
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	m_shaderProgram = shaderProgram;
}
