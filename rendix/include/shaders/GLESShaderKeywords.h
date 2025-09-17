#ifndef RENDIX_SHADER_KEYWORDS_H
#define RENDIX_SHADER_KEYWORDS_H

#include <string>

namespace rendix::shaders::keywords
{
    // The '\n' is important to ensure each define is on a new line.
    const std::string HasMVP  = "#define HAS_MVP 1\n";
    const std::string HasColor = "#define HAS_COLOR 1\n";
    const std::string HasTexture = "#define HAS_TEXTURE 1\n";
    const std::string HasLighting = "#define HAS_LIGHTING 1\n";
    // Add new features here...
    // const std::string HasNormals = "#define HAS_NORMALS 1\n";
}

#endif // RENDIX_SHADER_KEYWORDS_H
