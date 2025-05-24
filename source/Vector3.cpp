#include <../include/Vector3.hpp>
#include <cmath>

Vector3::Vector3(float x, float y, float z) : m_x(x), m_y(y), m_z(z) {}

Vector3::~Vector3(){}

Vector3 Vector3::operator+(const Vector3& other) const {
	return Vector3(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
}

Vector3 Vector3::operator-(const Vector3& other) const {
	return Vector3(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
}

Vector3 Vector3::operator*(const float& other) const {
	return Vector3(m_x * other, m_y * other, m_z * other);
}

Vector3 Vector3::operator/(const float& other) const {
	return Vector3(m_x / other, m_y / other, m_z / other);
}

Vector3 Vector3::operator*(const int& other) const {
	return Vector3(m_x * other, m_y * other, m_z * other);
}

Vector3 Vector3::operator/(const int& other) const {
	return Vector3(m_x / other, m_y / other, m_z / other);
}

float Vector3::dot(const Vector3& other) const {
	return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
}

Vector3 Vector3::cross(const Vector3& other) const {
	return Vector3(
		m_y * other.m_z - m_z * other.m_y,
		m_z * other.m_x - m_x * other.m_z,
		m_x * other.m_y - m_y * other.m_x
	);
}

Vector3 Vector3::normalize() const {
	float len = length();
	if (len == 0)
		return Vector3(0, 0, 0);
	return Vector3(m_x / len, m_y / len, m_z / len);
}

float Vector3::length() const {
	return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}
