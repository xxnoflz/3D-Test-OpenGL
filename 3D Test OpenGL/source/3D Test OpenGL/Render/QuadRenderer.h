#pragma once
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "../Utilities/shader.h"
#include "../Utilities/texture.h"

class QuadRenderer {
public:
	QuadRenderer(Shader& shader);

	void Draw(Texture& texture, const glm::vec3& position, const glm::vec2& size, const float degree, const glm::vec3& rotation_axes);
private:
	GLuint m_VAO;
	Shader m_shader;

	void Init();
};