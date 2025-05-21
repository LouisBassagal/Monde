#pragma once

#include <Primitives/Primitive.hpp>
#include <GL/gl.h>
#include <Vector3.hpp>


class Square : public Primitive
{
	public:
		Square();
		~Square() override;

		virtual void draw() final;

	private:
		std::vector<Vector3> m_vertices;
		std::vector<Vector3> m_normals;

		unsigned int m_VBO;
		unsigned int m_VAO;
};
