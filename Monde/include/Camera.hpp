#pragma once

#include <Vector3.hpp>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
	public:
		enum DIRECTION {
			FRONT,
			BACK,
			LEFT,
			RIGHT
		};

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
		void setSpeed(float speed);
		void setSensitivity(float sensitivity);
		void setYaw(float yaw);
		void setPitch(float pitch);

		float getYaw();
		float getPitch();
		float getSensitivity();
		float getFOV() const;

		void move(DIRECTION direction, float deltaTime);
		void update(unsigned int program);

	private:
		glm::vec3 m_position{ 0.f, 0.f, 2.f };
		glm::vec3 m_front{ 0.f, 0.f, -1.f };
		glm::vec3 m_direction{ m_position + m_front };
		glm::vec3 m_up{ 0.f, 1.f, 0.f };

		float m_fov;
		float m_aspectRatio;
		float m_nearPlane;
		float m_farPlane;
		float m_speed{ 1.f };

		float m_yaw{ -90.f };
		float m_pitch{ 0.f };
		float m_roll{ 0.f };

		float m_sensitivity{ 0.1f };

		glm::mat4 m_projection{ 1.f };
		glm::mat4 m_view{ 1.f };
};
