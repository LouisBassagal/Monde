#pragma once

#include <Primitives/Primitive.hpp>
#include <GL/gl.h>
#include <Vector3.hpp>

class Pyramid : public Primitive {
	public:
		Pyramid();
		~Pyramid() override;

		virtual void draw(unsigned int program) final;
		virtual void translate(const Vector3& position) final;
		virtual void rotate(float angle, const Vector3& vector) final;
		virtual void setVertices(std::vector<Vector3> vertices) final;

		virtual glm::mat4 *getModelMatrix() final;

		std::vector<Vector3> *getVertices();

	private:
		std::vector<Vector3> m_vertices;
		std::vector<Vector3> m_normals;

		unsigned int m_VBO;
		unsigned int m_VAO;

		glm::mat4 m_model{ 1.f };
};
