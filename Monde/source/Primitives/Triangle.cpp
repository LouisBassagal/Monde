#include <../include/Primitives/Triangle.hpp>

Triangle::Triangle() {
	unsigned int VBO;
	unsigned int VAO;

	m_vertices = {
		Vector3(-0.5f, -0.5f, 0.0f),
		Vector3(0.5f, -0.5f, 0.0f),
		Vector3(0.0f, 0.5f, 0.0f)
	};

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);
}

Triangle::~Triangle() {}

void Triangle::draw() {
	glBindVertexArray(m_VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}