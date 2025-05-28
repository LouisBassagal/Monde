#include <Lights/Light.hpp>

Light::Light(Vector3 position, Vector3 color, float intensity)
	: m_position{ position }, m_color{ color }, m_intensity{ intensity } {
}

Light::~Light() {}

void Light::setPosition(const Vector3& position) {
	m_position = position;
}

void Light::setColor(const Vector3& color) {
	m_color = color;
}

void Light::setIntensity(float intensity) {
	m_intensity = intensity;
}

Vector3 Light::getPosition() const {
	return m_position;
}

Vector3 Light::getColor() const {
	return m_color;
}

float Light::getIntensity() const {
	return m_intensity;
}