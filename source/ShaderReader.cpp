#include "ShaderReader.hpp"
#include <iostream>

std::string ShaderReader::readShader(const std::string& filePath) {
	std::ifstream file{ filePath };
	std::string shaderCode;
	std::string line;

	if (!file.is_open()) {
		// Log error message
		std::cout << "Error: Could not open shader file: " << filePath << std::endl;
		throw std::runtime_error("Failed to open shader file: " + filePath);
	}
	while (std::getline(file, line)) {
		shaderCode += line + "\n";
	}
	file.close();
	return shaderCode;
}

std::string ShaderReader::readShader(const char *filePath) {
	return readShader(std::string(filePath));
}
