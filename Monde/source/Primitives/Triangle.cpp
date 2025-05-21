#include <../include/Primitives/Triangle.hpp>

Triangle::Triangle() {
	m_vertices = {
		Vector3(-0.5f, -0.5f, 0.0f), Vector3(1.f, 0.f, 0.f),
		Vector3(0.5f, -0.5f, 0.0f), Vector3(0.f, 1.f, 0.f),
		Vector3(0.0f, 0.5f, 0.0f), Vector3(0.f, 0.f, 1.f)
	};

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(Vector3), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(Vector3), (void*)(1 * sizeof(Vector3)));
	glEnableVertexAttribArray(1);
}

Triangle::~Triangle() {}

void Triangle::draw() {
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
}