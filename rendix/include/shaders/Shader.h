#ifndef RENDIX_SHADERS_SHADER_H
#define RENDIX_SHADERS_SHADER_H

#include <string>
#include <vector>
#include <GLES2/gl2.h>

namespace rendix::shaders
{
    class Shader
    {
        public:
            Shader(GLenum type);
            GLuint GetShaderId() const;
            bool LoadFromString(const std::string& sourceCode);
            bool LoadFromFile(const std::string& fileName);
            bool Compile();

        private:
            GLuint shaderId;
            std::string fileName;
    };
}

#endif //RENDIX_SHADERS_SHADER_H
