#include "Window.hpp"
#include <iostream>

static void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
	Mouse* mouse = instance->getMouse();
	ImGuiIO& io = ImGui::GetIO();

	float xOffset;
	float yOffset;
	float yaw = instance->getCamera()->getYaw();
	float pitch = instance->getCamera()->getPitch();
	float sensitivity = instance->getCamera()->getSensitivity();

	mouse->oldX = mouse->x;
	mouse->oldY = mouse->y;
	mouse->x = static_cast<float>(xpos);
	mouse->y = static_cast<float>(ypos);

	xOffset = mouse->x - mouse->oldX;
	yOffset = mouse->oldY - mouse->y;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !io.WantCaptureMouse) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		instance->getCamera()->setYaw(yaw + xOffset * sensitivity);
		instance->getCamera()->setPitch(pitch + yOffset * sensitivity);
	} else {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
	Camera* camera = instance->getCamera();
	ImGuiIO& io = ImGui::GetIO();
	float fov = camera->getFOV();

	if (io.WantCaptureMouse)
		return;
	camera->setFOV(fov - yoffset * 2);
}

Window::Window() {
	if (glfwInit() == GLFW_FALSE) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		throw;
	}
	m_window = glfwCreateWindow(1280, 720, "Mon Monde", nullptr, nullptr);
	
	glfwMakeContextCurrent(m_window);

	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		throw;
	}

   glViewport(0, 0, 1280, 720);  

   glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {  
       glViewport(0, 0, width, height);  
   });  

   m_camera.setProjectionMatrix(45.f, 1280.f / 720.f, 0.1f, 1000.f);

   glfwSetWindowUserPointer(m_window, this);
   glfwSetCursorPosCallback(m_window, mouse_callback);
   glfwSetScrollCallback(m_window, scroll_callback);
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

Camera* Window::getCamera()
{
	return &m_camera;
}

Mouse* Window::getMouse() {
	return &m_mouse;
}

void Window::test() {
	Pyramid *t1 = new Pyramid();

	m_primitives.push_back(t1);
}

void Window::test2() {
	for each(auto p in m_primitives) {
		p->rotate(0.1f, Vector3(.0f, 1.f, 0.f));
	}
}

void Window::checkInput() {
	// Camera inputs

	if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		m_camera.setSpeed(5.f);
	} else {
		m_camera.setSpeed(1.f);
	}

	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
		m_camera.move(Camera::FRONT, m_deltaTime);
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		m_camera.move(Camera::BACK, m_deltaTime);
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		m_camera.move(Camera::LEFT, m_deltaTime);
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		m_camera.move(Camera::RIGHT, m_deltaTime);
}

void Window::loop() {
	glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_currentFrame = glfwGetTime();
	m_deltaTime = m_currentFrame - m_lastFrame;

	glUseProgram(m_shaderProgram);

	m_camera.update(m_shaderProgram);

	checkInput();

	for each(auto primitive in m_primitives)
		primitive->draw(m_shaderProgram);
	m_lastFrame = m_currentFrame;
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
