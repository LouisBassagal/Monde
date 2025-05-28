#include <Primitives/Primitive.hpp>

void Primitive::translate(const Vector3& position) {
	m_model = glm::translate(m_model, glm::vec3(position.m_x, position.m_y, position.m_z));
}

void Primitive::rotate(float angle, const Vector3& vector) {
	m_model = glm::rotate(m_model, glm::radians(angle), glm::vec3(vector.m_x, vector.m_y, vector.m_z));
}

void Primitive::setMaterial(const Material& material) {
	m_material = material;
}

void Primitive::setColor(const Vector3& color) {
	m_color = color;
}
