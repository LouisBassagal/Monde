#include <Camera.hpp>

Camera::Camera() {
	m_position = { 0.f, 0.f, 2.f };
	m_fov = 45.f;
	m_aspectRatio = 16.f / 9.f;
	m_nearPlane = 0.1f;
	m_farPlane = 100.f;

	m_view = glm::lookAt(m_position, m_direction, m_up);
	m_projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);
}

Camera::Camera(float x, float y, float z) {
	m_position = { x, y, z };
	m_fov = 90.f;
	m_aspectRatio = 16.f / 9.f;
	m_nearPlane = 0.1f;
	m_farPlane = 100.f;

	m_view = glm::lookAt(m_position, m_direction, m_up);
	m_projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);
}

Camera::~Camera() {}

void Camera::setPosition(float x, float y, float z) {
	m_position = { x, y, z };
}

void Camera::setDirection(float x, float y, float z) {}

void Camera::setProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane) {
	m_fov = fov;
	m_aspectRatio = aspectRatio;
	m_nearPlane = nearPlane;
	m_farPlane = farPlane;

	m_projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);
}

void Camera::setFOV(float fov) {
	m_fov = fov > 120.f ? 120.f : fov < 10.f ? 10.f : fov;

	m_projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);
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

void Camera::setSpeed(float speed) {
	m_speed = speed;
}

void Camera::setSensitivity(float sensitivity) {
	m_sensitivity = sensitivity;
}

void Camera::setYaw(float yaw) {
	m_yaw = yaw;
	m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front.y = sin(glm::radians(m_pitch));
	m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(m_front);
}

void Camera::setPitch(float pitch) {
	m_pitch = pitch;
	m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front.y = sin(glm::radians(m_pitch));
	m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(m_front);
}

float Camera::getYaw() {
	return m_yaw;
}

float Camera::getPitch() {
	return m_pitch;
}

float Camera::getSensitivity() {
	return m_sensitivity;
}

float Camera::getFOV() const {
	return m_fov;
}

void Camera::move(DIRECTION direction, float deltaTime) {
	glm::vec3 side = glm::normalize(glm::cross(m_front, m_up));

	if (direction == FRONT)
		m_position += m_front * m_speed * deltaTime;
	else if (direction == BACK)
		m_position -= m_front * m_speed * deltaTime;
	else if (direction == LEFT)
		m_position -= side * m_speed * deltaTime;
	else if (direction == RIGHT)
		m_position += side * m_speed * deltaTime;
}

void Camera::update(unsigned int program) {
	m_view = glm::lookAt(m_position, m_position + m_front, m_up);

	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(m_view));
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(m_projection));
}
