#pragma once

class Vector3 {
	public:
		Vector3(float x, float y, float z);
		~Vector3();

		Vector3 operator+(const Vector3 &other) const;
		Vector3 operator-(const Vector3 &other) const;
		Vector3 operator*(const float &other) const;
		Vector3 operator/(const float &other) const;
		Vector3 operator*(const int &other) const;
		Vector3 operator/(const int &other) const;

		Vector3 cross(const Vector3 &other) const;
		Vector3 normalize() const;

		float dot(const Vector3 &other) const;
		float length() const;

		float m_x;
		float m_y;
		float m_z;
};
