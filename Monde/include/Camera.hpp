#pragma once

#include <Vector3.hpp>

class Camera {
	public:
		Camera();
		Camera(float x, float y, float z);
		~Camera();

		void setPosition(float x, float y, float z);
		void setDirection(float x, float y, float z);
		void setFOV(float fov);
		void setAspectRatio(float ratio);
		void setNearPlane(float near);
		void setFarPlane(float far);

	private:
		Vector3 m_position;
		Vector3 m_direction;

		float m_fov;
		float m_aspectRatio;
		float m_nearPlane;
		float m_farPlane;
};
