#pragma once
#include <glad/glad.h>

class Texture {
public:
	Texture(unsigned char* data = nullptr, int width = 0, int height = 0);

	void Bind() const;
private:
	GLuint m_ID;
};