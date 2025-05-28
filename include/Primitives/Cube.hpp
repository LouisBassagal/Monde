#pragma once

#include <Primitives/Primitive.hpp>

class Cube : public Primitive {
	public:
		Cube();
		~Cube() override;

		virtual void draw(unsigned int program) final;

		virtual glm::mat4 *getModelMatrix() final;

		std::vector<Vector3> *getVertices();
};