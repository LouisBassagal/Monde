#pragma once

#include <Vector3.hpp>
#include <Lights/ILight.hpp>

class Light : public ILight  {
	public:
		Light(Vector3 position, Vector3 color, float intensity);
		virtual ~Light();

		virtual void setPosition(const Vector3& position);
		virtual void setColor(const Vector3& color);
		virtual void setIntensity(float intensity);

		virtual Vector3 getPosition() const;
		virtual Vector3 getColor() const;
		virtual float getIntensity() const;

		virtual void update(unsigned int program) = 0;

	protected:
		Vector3 m_position;
		Vector3 m_color{ 1.f, 1.f, 1.f };
		float m_intensity{ 1.f };
};