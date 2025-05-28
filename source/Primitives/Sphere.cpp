#include <Primitives/Sphere.hpp>
#include <iostream>

Sphere::Sphere(unsigned horizontal, unsigned vertical) {
	m_vertices = {};

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_verticesVBO);
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(Vector3), (void*)0);
	glEnableVertexAttribArray(0);
}

Sphere::~Sphere() {}

void Sphere::draw(unsigned int program) {
	glBindVertexArray(m_VAO);

	glEnable(GL_DEPTH_TEST);
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(m_model));
	glUniform3f(glGetUniformLocation(program, "objectColor"), m_color.m_x, m_color.m_y, m_color.m_z);
	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
	glDisable(GL_DEPTH_TEST);
}

glm::mat4 *Sphere::getModelMatrix() {
	return &m_model;
}

std::vector<Vector3> *Sphere::getVertices() {
	return &m_vertices;
}
