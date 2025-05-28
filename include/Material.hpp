#pragma once

#include <Vector3.hpp>

struct Material {
	public:
		Material() {};
		~Material() {};

		Vector3 ambient{ .2f, .2f, .2f };
		Vector3 diffuse{ .8f, .8f, .8f };
		Vector3 specular{ .8f, .8f, .8f };
		float shininess{ 1.f };
};