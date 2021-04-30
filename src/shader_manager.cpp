#include "shader_manager.hpp"

#include <iostream>
#include <fstream>

ShaderManager::ShaderManager(std::filesystem::path path)
{
    std::ifstream shader_stream(path);

    if (!shader_stream.is_open())
    {
        std::cout << "ERROR: ShaderManager failed to open file: " << path << std::endl;
    }
    std::stringstream buffer; 
    buffer << shader_stream.rdbuf();
    this->source = buffer.str();
}

const char *ShaderManager::get_source()
{
    return this->source.c_str();
}