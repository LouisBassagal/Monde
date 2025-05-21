#pragma once

#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>

#include <../include/Vector3.hpp>

class Primitive
{
	public:
		virtual ~Primitive() {};

		virtual void draw() = 0;
};
