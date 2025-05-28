#pragma once

#include <Vector3.hpp>

class ILight {
	public:
		virtual ~ILight() {};

		virtual void setPosition(const Vector3& position) = 0;
		virtual void setColor(const Vector3& color) = 0;
		virtual void setIntensity(float intensity) = 0;

		virtual Vector3 getPosition() const = 0;
		virtual Vector3 getColor() const = 0;
		virtual float getIntensity() const = 0;

		virtual void update(unsigned int program) = 0;
};