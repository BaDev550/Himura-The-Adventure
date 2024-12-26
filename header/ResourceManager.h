#ifndef RESOURCE_MANAGER_HEADER_CLASS
#define RESOURCE_MANAGER_HEADER_CLASS
#pragma once

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include <render_engine/Shader.h>
#include <render_engine/Texture.h>

class ResourceManager
{
public:
    ResourceManager() {};
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture2D> Textures;
    
    static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
    static Shader GetShader(std::string name);
    static Texture2D LoadTexture(const char* file, bool alpha, std::string name);
    static const Texture2D GetTexture(const std::string name);
    static void Clear();
private:
    static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
    static Texture2D loadTextureFromFile(const char* file, bool alpha);
};

#endif
