#ifndef RENDIX_SHADERS_I_SHADER_PROGRAM_H
#define RENDIX_SHADERS_I_SHADER_PROGRAM_H

#include "shaders/IShader.h"

namespace rendix::shaders
{

    class IShaderProgram
    {
    public:
        virtual ~IShaderProgram() = default;

        virtual unsigned int GetShaderProgramId() const = 0;
        virtual bool AttachShader(const IShader &shader) = 0;
        virtual bool LinkShaders() = 0;
        virtual bool Use() = 0;
        virtual bool BindAttribute(unsigned int index, const std::string &attribute) = 0;
        virtual int GetAttributeLocation(const std::string& name) const = 0;
        virtual const std::string& GetLinkLog() const = 0;
    };
}

#endif // RENDIX_SHADERS_I_SHADER_PROGRAM_H
