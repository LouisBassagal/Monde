#include <Camera.hpp>

Camera::Camera() {
	m_position = { 0.f, 0.f, 0.f };
	m_direction = { 0.f, 0.f, -1.f };
	m_fov = 45.f;
	m_aspectRatio = 16.f / 9.f;
	m_nearPlane = 0.1f;
	m_farPlane = 100.f;

	m_view = glm::mat4{ 1.0f };
	m_view = glm::translate(m_view, glm::vec3{ 0.f, -.5f, -3.f });
}

Camera::Camera(float x, float y, float z) {
	m_position = { x, y, z };
	m_direction = { 0.f, 0.f, -1.f };
	m_fov = 45.f;
	m_aspectRatio = 16.f / 9.f;
	m_nearPlane = 0.1f;
	m_farPlane = 100.f;

	m_view = glm::mat4{ 1.0f };
	m_view = glm::translate(m_view, glm::vec3{ 0.f, -.5f, -3.f });
}

Camera::~Camera() {}

void Camera::setPosition(float x, float y, float z) {
	m_position = { x, y, z };
}

void Camera::setDirection(float x, float y, float z) {
	m_direction = { x, y, z };
}

void Camera::setProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane) {
	m_fov = fov;
	m_aspectRatio = aspectRatio;
	m_nearPlane = nearPlane;
	m_farPlane = farPlane;

	m_projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);
	//m_projection = glm::ortho(-m_aspectRatio, m_aspectRatio, -1.f, 1.f, m_nearPlane, m_farPlane);
}

void Camera::setFOV(float fov) {
	m_fov = fov;
}

void Camera::setAspectRatio(float ratio) {
	m_aspectRatio = ratio;
}

void Camera::setNearPlane(float near) {
	m_nearPlane = near;
}

void Camera::setFarPlane(float far) {
	m_farPlane = far;
}

void Camera::initProjectionMatrix(unsigned int program) {
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(m_projection));

}

void Camera::initViewMatrix(unsigned int program) {
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(m_view));
}
