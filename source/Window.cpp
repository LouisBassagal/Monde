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
	std::unique_ptr<Cube> t1 = std::make_unique<Cube>();
	std::unique_ptr<Pyramid> t2 = std::make_unique<Pyramid>();
	std::unique_ptr<Pyramid> t3 = std::make_unique<Pyramid>();
	//std::unique_ptr<ILight> light1 = std::make_unique<AmbiantLight>( Vector3{0.f, 0.f, 0.f}, Vector3{ .2f, .5f, .2f}, 1.f);
	Material mat;

	mat.shininess = 32.f;
	t1->setMaterial(mat);
	t1->setColor({ 0.3f, 0.5f, 0.f });
	t1->rotate(45.f, { 0.f, 1.f, 0.f });

	t2->setMaterial(mat);
	t2->translate({ 2.f, 2.f, -2.f });
	t2->setColor({ 0.f, .9f, 4.f });
	t2->rotate(45.f, {1.f, 0.f, 0.5f});

	t3->setMaterial(mat);
	t3->translate({ -3.f, 2.f, -4.f });
	t3->setColor({ 8.f, .4f, 1.f });
	t3->rotate(45.f, { .2f, -.6f, .5f });

	m_primitives.emplace_back(std::move(t1));
	m_primitives.emplace_back(std::move(t2));
	m_primitives.emplace_back(std::move(t3));
	//m_lights.emplace_back(std::move(light1));
}

void Window::test2() {}

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
	glClearColor(0.2f, 0.2f, 0.2f, 1.00f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_currentFrame = glfwGetTime();
	m_deltaTime = m_currentFrame - m_lastFrame;

	glUseProgram(m_shaderProgram);

	m_camera.update(m_shaderProgram);
	updateLights(m_shaderProgram);

	checkInput();

	glUniform3f(glGetUniformLocation(m_shaderProgram, "lightPos"), 0, 2, 2);
	glUniform3f(glGetUniformLocation(m_shaderProgram, "lightColor"), 1.f, 1.f, 1.f);

	for each(auto &primitive in m_primitives)
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

void Window::updateLights(unsigned int program) {
	for (auto& light : m_lights) {
		Vector3 color = light->getColor();
		glUniform3f(glGetUniformLocation(program, "lightColor"), color.m_x, color.m_y, color.m_z);
	}
}
