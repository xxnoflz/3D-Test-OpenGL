#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

class Shader {
public:
	Shader(const std::string vertexCode = "", const std::string fragmentCode = "");

	void use() const;

	void SetVec3(const std::string name, glm::vec3& value);
	void SetMat4(const std::string name, glm::mat4& value);
private:
	GLuint m_ID;
};