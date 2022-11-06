#include "QuadRenderer.h"

QuadRenderer::QuadRenderer(Shader& shader) : m_shader(shader) {
	this->Init();
}

void QuadRenderer::Init() {
	std::vector<float> vertices{
		//vertex pos		//texture pos
		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		0.0f, 1.0f,	0.0f,	0.0f, 1.0f,
		1.0f, 0.0f,	0.0f,	1.0f, 0.0f,

		1.0f, 1.0f,	0.0f,	1.0f, 1.0f,
		0.0f, 1.0f,	0.0f,	0.0f, 1.0f,
		1.0f, 0.0f,	0.0f,	1.0f, 0.0f
	};

	GLuint VBO;

	glGenVertexArrays(1, &this->m_VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(this->m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void QuadRenderer::Draw(Texture& texture, const glm::vec3& position, const glm::vec2& size, float degree, const glm::vec3& rotation_axes) {
	glm::mat4 model{ glm::mat4(1.0f) };
	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(degree), rotation_axes);
	model = glm::scale(model, glm::vec3(size, 2.0f));

	m_shader.use();
	m_shader.SetMat4("model", model);
	texture.Bind();

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}