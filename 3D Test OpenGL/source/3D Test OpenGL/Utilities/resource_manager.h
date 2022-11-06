#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <map>

#include "../vendor/stb_image.h"

#include "shader.h"
#include "texture.h"

class ResourceManager {
public:
	static void CreateShader(const std::string vertexPath, const std::string fragmentPath, const std::string name);
	static Shader& GetShader(const std::string name);

	static void CreateTexture(const std::string file_path, const std::string name);
	static Texture& GetTexture(const std::string name);
private:
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Texture> Textures;
};