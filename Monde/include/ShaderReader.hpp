#pragma once

#include <string>
#include <fstream>

constexpr const char *VERTEX_FILEPATH = "Z:/Projets/Monde/Monde/source/shaders/vertex.glsl";
constexpr const char *FRAGMENT_FILEPATH = "Z:/Projets/Monde/Monde/source/shaders/fragment.glsl";

class ShaderReader {
	public:
		static std::string readShader(const std::string& filePath);
		static std::string readShader(const char* filePath);
};