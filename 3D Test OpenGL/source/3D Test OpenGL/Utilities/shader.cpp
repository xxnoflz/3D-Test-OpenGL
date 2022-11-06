#include "shader.h"

Shader::Shader(const std::string vertexCode, const std::string fragmentCode) {
	const char* vertexCode_str{ vertexCode.c_str() };
	GLuint vertexShader{ glCreateShader(GL_VERTEX_SHADER) };
	glShaderSource(vertexShader, 1, &vertexCode_str, nullptr);
	glCompileShader(vertexShader);

	const char* fragmentCode_str{ fragmentCode.c_str() };
	GLuint fragmentShader{ glCreateShader(GL_FRAGMENT_SHADER) };
	glShaderSource(fragmentShader, 1, &fragmentCode_str, nullptr);
	glCompileShader(fragmentShader);

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertexShader);
	glAttachShader(m_ID, fragmentShader);
	glLinkProgram(m_ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use() const {
	glUseProgram(m_ID);
}

void Shader::SetVec3(const std::string name, glm::vec3& value) {
	glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
} 

void Shader::SetMat4(const std::string name, glm::mat4& value) {
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, false, &value[0][0]);
}