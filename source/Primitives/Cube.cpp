#include <Primitives/Cube.hpp>
#include <iostream>

Cube::Cube() {
	m_vertices = {
		// Left
		{.5f, .0f, .5f}, {.5f, .0f, -.5f}, {.5f, 1.f, .5f},
		{.5f, 1.f, -.5f}, {.5f, .0f, -.5f}, {.5f, 1.f, .5f},

		// Front
		{.5f, .0f, -.5f}, {.5f, 1.f, -.5f}, {-.5f, 1.f, -.5f},
		{-.5f, .0f, -.5f}, {-.5f, 1.f, -.5f}, {.5f, .0f, -.5f},

		// Right
		{-.5f, .0f, .5f}, {-.5f, .0f, -.5f}, {-.5f, 1.f, .5f},
		{-.5f, 1.f, -.5f}, {-.5f, .0f, -.5f}, {-.5f, 1.f, .5f},

		// Back
		{.5f, .0f, .5f}, {.5f, 1.f, .5f}, {-.5f, 1.f, .5f},
		{-.5f, .0f, .5f}, {-.5f, 1.f, .5f}, {.5f, .0f, .5f},

		// Down
		{.5f, .0f, .5f}, {-.5f, .0f, .5f}, {.5f, .0f, -.5f},
		{-.5f, .0f, .5f}, {.5f, 0.f, -.5f}, {-.5f, .0f, -.5f},

		// Up
		{.5f, 1.f, .5f}, {-.5f, 1.f, .5f}, {.5f, 1.f, -.5f},
		{-.5f, 1.f, .5f}, {.5f, 1.f, -.5f}, {-.5f, 1.f, -.5f},
	};

	m_normals = {
		// Left
		{1.f, 0.f, 0.f}, {1.f, 0.f, 0.f}, {1.f, 0.f, 0.f},
		{1.f, 0.f, 0.f}, {1.f, 0.f, 0.f}, {1.f, 0.f, 0.f},

		// Front
		{0.f, 0.f, -1.f}, {0.f, 0.f, -1.f}, {0.f, 0.f, -1.f},
		{0.f, 0.f, -1.f}, {0.f, 0.f, -1.f}, {0.f, 0.f, -1.f},

		// Right
		{-1.f, 0.f, 0.f}, {-1.f, 0.f, 0.f}, {-1.f, 0.f, 0.f},
		{-1.f, 0.f, 0.f}, {-1.f, 0.f, 0.f}, {-1.f, 0.f, 0.f},

		// Back
		{0.f, 0.f, 1.f}, {0.f, 0.f, 1.f}, {0.f, 0.f, 1.f},
		{0.f, 0.f, 1.f}, {0.f, 0.f, 1.f}, {0.f, 0.f, 1.f},

		// Bottom
		{0.f, -1.f, 0.f}, {0.f, -1.f, 0.f}, {0.f, -1.f, 0.f},
		{0.f, -1.f, 0.f}, {0.f, -1.f, 0.f}, {0.f, -1.f, 0.f},

		// Top
		{0.f, 1.f, 0.f}, {0.f, 1.f, 0.f}, {0.f, 1.f, 0.f},
		{0.f, 1.f, 0.f}, {0.f, 1.f, 0.f}, {0.f, 1.f, 0.f}
	};

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_verticesVBO);
	glGenBuffers(1, &m_normalVBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, m_normalVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * m_normals.size(), m_normals.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void*)0);
	glEnableVertexAttribArray(1);
}

Cube::~Cube() {}

void Cube::draw(unsigned int program) {
	glBindVertexArray(m_VAO);

	m_normalMatrix = glm::transpose(glm::inverse(m_model));

	glEnable(GL_DEPTH_TEST);
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(m_model));
	glUniformMatrix4fv(glGetUniformLocation(program, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(m_normalMatrix));

	glUniform3f(glGetUniformLocation(program, "material.ambient"), m_material.ambient.m_x, m_material.ambient.m_y, m_material.ambient.m_z);
	glUniform3f(glGetUniformLocation(program, "material.diffuse"), m_material.diffuse.m_x, m_material.diffuse.m_y, m_material.diffuse.m_z);
	glUniform3f(glGetUniformLocation(program, "material.specular"), m_material.specular.m_x, m_material.specular.m_y, m_material.specular.m_z);
	glUniform1f(glGetUniformLocation(program, "material.shininess"), m_material.shininess);

	glUniform3f(glGetUniformLocation(program, "objectColor"), m_color.m_x, m_color.m_y, m_color.m_z);

	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
	glDisable(GL_DEPTH_TEST);
}

glm::mat4 *Cube::getModelMatrix() {
	return &m_model;
}

std::vector<Vector3> *Cube::getVertices() {
	return &m_vertices;
}
