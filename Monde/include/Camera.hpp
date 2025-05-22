#pragma once

#include <Vector3.hpp>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
	public:
		Camera();
		Camera(float x, float y, float z);
		~Camera();

		void setPosition(float x, float y, float z);
		void setDirection(float x, float y, float z);
		void setProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane);
		void setFOV(float fov);
		void setAspectRatio(float ratio);
		void setNearPlane(float near);
		void setFarPlane(float far);

		void initProjectionMatrix(unsigned int program);
		void initViewMatrix(unsigned int program);

	private:
		Vector3 m_position{ 0.f, 0.f, 0.f };
		Vector3 m_direction{ 0.f, 0.f, 0.f };

		float m_fov;
		float m_aspectRatio;
		float m_nearPlane;
		float m_farPlane;

		glm::mat4 m_projection{ 1.f };
		glm::mat4 m_view{ 1.f };
};
