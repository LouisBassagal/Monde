#include <Camera.hpp>

Camera::Camera() {
	m_position = { 0.f, 0.f, 0.f };
	m_direction = { 0.f, 0.f, -1.f };
	m_fov = 45.f;
	m_aspectRatio = 16.f / 9.f;
	m_nearPlane = 0.1f;
	m_farPlane = 100.f;
}

Camera::Camera(float x, float y, float z) {
	m_position = { x, y, z };
	m_direction = { 0.f, 0.f, -1.f };
	m_fov = 45.f;
	m_aspectRatio = 16.f / 9.f;
	m_nearPlane = 0.1f;
	m_farPlane = 100.f;
}

Camera::~Camera() {}

void Camera::setPosition(float x, float y, float z) {
	m_position = { x, y, z };
}

void Camera::setDirection(float x, float y, float z) {
	m_direction = { x, y, z };
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