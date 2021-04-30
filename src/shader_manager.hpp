#pragma once

#include <string>
#include <filesystem>

class ShaderManager
{
private:
    std::string source;

public:
    ShaderManager(const std::filesystem::path path);

    const char *get_source();
};