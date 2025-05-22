#include <Primitives/Pyramid.hpp>
#include <iostream>

Pyramid::Pyramid() {
	m_vertices = {
		// Base
		Vector3(.5f, .0f, .5f), Vector3(1.f, 0.f, .0f),
		Vector3(.5f, .0f, -.5f), Vector3(.0f, 0.f, 1.f),
		Vector3(-.5f, 0.f, .5f), Vector3(.0f, 0.f, 1.f),

		Vector3(.5f, .0f, -.5f), Vector3(0.f, 0.f, 1.f),
		Vector3(-.5f, .0f, .5f), Vector3(0.f, 0.f, 1.f),
		Vector3(-.5f, .0f, -.5f), Vector3(1.f, 0.f, .0f),

		// Faces
		Vector3(.5f, .0f, .5f), Vector3(1.f, 0.f, 0.f),
		Vector3(.0f, 1.f, .0f), Vector3(0.f, 1.f, 0.f),
		Vector3(-.5f, .0f, .5f), Vector3(0.f, 0.f, 1.f),

		Vector3(.5f, .0f, -.5f), Vector3(0.f, 0.f, 1.f),
		Vector3(.0f, 1.f, .0f), Vector3(0.f, 1.f, 0.f),
		Vector3(.5f, .0f, .5f), Vector3(1.f, 0.f, 0.f),

		Vector3(-.5f, .0f, -.5f), Vector3(1.f, 0.f, 0.f),
		Vector3(.0f, 1.f, .0f), Vector3(0.f, 1.f, 0.f),
		Vector3(-.5f, .0f, .5f), Vector3(0.f, 0.f, 1.f),

		Vector3(-.5f, .0f, -.5f), Vector3(1.f, 0.f, 0.f),
		Vector3(.0f, 1.f, .0f), Vector3(0.f, 1.f, 0.f),
		Vector3(.5f, .0f, -.5f), Vector3(0.f, 0.f, 1.f),
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

Pyramid::~Pyramid() {}

void Pyramid::draw(unsigned int program) {
	glBindVertexArray(m_VAO);

	glEnable(GL_DEPTH_TEST);
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(m_model));
	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
	glDisable(GL_DEPTH_TEST);
}

void Pyramid::rotate(float angle, const Vector3& vector) {
	m_model = glm::rotate(m_model,  glm::radians(angle), glm::vec3(vector.m_x, vector.m_y, vector.m_z));
}

void Pyramid::setVertices(std::vector<Vector3> vertices) {
	m_vertices = vertices;

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(Vector3), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(Vector3), (void*)(1 * sizeof(Vector3)));
	glEnableVertexAttribArray(1);
}

glm::mat4 *Pyramid::getModelMatrix() {
	return &m_model;
}

std::vector<Vector3> *Pyramid::getVertices() {
	return &m_vertices;
}

void Pyramid::translate(const Vector3& position) {
	m_model = glm::translate(m_model, glm::vec3(position.m_x, position.m_y, position.m_z));
}
