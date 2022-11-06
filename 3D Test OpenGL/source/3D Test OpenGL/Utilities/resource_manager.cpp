#include "resource_manager.h"

std::map<std::string, Shader> ResourceManager::Shaders;
std::map<std::string, Texture> ResourceManager::Textures;

void ResourceManager::CreateShader(const std::string vertexPath, const std::string fragmentPath, const std::string name) {
	std::ifstream vertexFile{ vertexPath };
	std::stringstream vertexStream;
	vertexStream << vertexFile.rdbuf();
	std::string vertexCode{ vertexStream.str() };

	std::ifstream fragmentFile{ fragmentPath };
	std::stringstream fragmentStream;
	fragmentStream << fragmentFile.rdbuf();
	std::string fragmentCode{ fragmentStream.str() };

	Shader shader{ vertexCode, fragmentCode };
	Shaders[name] = shader;
}

Shader& ResourceManager::GetShader(const std::string name) {
	return Shaders[name];
}

void ResourceManager::CreateTexture(const std::string file_path, const std::string name) {
	int width;
	int height;
	int nrChannels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data{ stbi_load(file_path.c_str(), &width, &height, &nrChannels, 0) };
	Texture texture{ data, width, height };
	Textures[name] = texture;
}

Texture& ResourceManager::GetTexture(const std::string name) {
	return Textures[name];
}