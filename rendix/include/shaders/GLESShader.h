#ifndef RENDIX_SHADERS_GLES_SHADER_H
#define RENDIX_SHADERS_GLES_SHADER_H

#include "shaders/IShader.h"
#include <string>
#include <GLES2/gl2.h>

namespace rendix::shaders
{
    class GLESShader : public IShader
    {
    public:
        GLESShader(ShaderType type);
        bool Compile(const std::string &source) override;
        const std::string &GetErrorLog() const override;
        unsigned int GetShaderId() const override;
        ShaderType GetShaderType() const override;

    private:
        GLuint shaderId;
        std::string errorLog;
    };
}

#endif // RENDIX_SHADERS_GLES_SHADER_H
