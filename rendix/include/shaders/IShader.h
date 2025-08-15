#ifndef RENDIX_SHADERS_I_SHADER_H
#define RENDIX_SHADERS_I_SHADER_H

#include <string>

namespace rendix::shaders {

    enum class ShaderType
    {
        VERTEX,
        FRAGMENT,
        // Extend with Geometry, Compute, etc. as needed
        UNKNOWN
    };

    class IShader
    {
    public:
        virtual ~IShader() = default;
        virtual bool Compile(const std::string &source) = 0;
        virtual const std::string &GetErrorLog() const = 0;
        virtual unsigned int GetShaderId() const = 0;
        virtual ShaderType GetShaderType() const = 0;
    };
}

#endif //RENDIX_SHADERS_I_SHADER_H
