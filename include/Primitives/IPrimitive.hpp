#pragma once

#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

#include <../include/Vector3.hpp>

class IPrimitive
{
	public:
		virtual ~IPrimitive() {};

		virtual void draw(unsigned int program) = 0;
		virtual void translate(const Vector3 &position) = 0;
		virtual void rotate(float angle, const Vector3 &vector) = 0;

		virtual glm::mat4 *getModelMatrix() = 0;
};
