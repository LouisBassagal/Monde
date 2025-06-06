#pragma once

#include <Primitives/Primitive.hpp>
#include <GL/gl.h>
#include <Vector3.hpp>

class Pyramid : public Primitive {
	public:
		Pyramid();
		~Pyramid() override;

		virtual void draw(unsigned int program) final;

		virtual glm::mat4 *getModelMatrix() final;

		std::vector<Vector3> *getVertices();
};
