#pragma once

#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

#include <Vector3.hpp>
#include <Material.hpp>
#include <Primitives/IPrimitive.hpp>

class Primitive : public IPrimitive
{
	public:
		virtual ~Primitive() {};

		virtual void draw(unsigned int program) = 0;

		virtual void translate(const Vector3 &position);
		virtual void rotate(float angle, const Vector3 &vector);

		virtual void setMaterial(const Material& material);
		virtual void setColor(const Vector3& color);

		virtual glm::mat4 *getModelMatrix() = 0;

	protected:
		std::vector<Vector3> m_vertices;
		std::vector<Vector3> m_normals;

		unsigned int m_VAO;
		unsigned int m_verticesVBO;
		unsigned int m_normalVBO;

		glm::mat4 m_model{ 1.f };
		glm::mat4 m_normalMatrix{ 1.f };
		Material m_material;
		Vector3 m_color{ 1.f, 1.f, 1.f };
};
