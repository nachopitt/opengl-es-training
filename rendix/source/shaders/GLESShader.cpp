#include "shaders/GLESShader.h"
#include "esUtil.h"

#include <fstream>
#include <iostream>

namespace rendix::shaders
{
    rendix::shaders::GLESShader::GLESShader(ShaderType type)
        : shaderId(0) // Initialize to 0 in case of failure
    {
        GLenum shaderType;

        switch (type)
        {
        case ShaderType::VERTEX:
            shaderType = GL_VERTEX_SHADER;
            break;
        case ShaderType::FRAGMENT:
            shaderType = GL_FRAGMENT_SHADER;
            break;
        default:
            std::cerr << "Unsupported ShaderType: " << static_cast<int>(type) << std::endl;
            return; // Early exit, shaderId remains 0
        }

        // Create the shader object
        shaderId = glCreateShader(shaderType);
        if (shaderId == 0)
        {
            std::cerr << "Failed to create shader object." << std::endl;
        }
    }

    bool GLESShader::Compile(const std::string &source)
    {
        GLint compiled;

        const char *src = source.c_str();

        // Load the shader source
        glShaderSource(shaderId, 1, &src, NULL);

        // Compile the shader
        glCompileShader(shaderId);

        // Check the compile status
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compiled);

        if (!compiled)
        {
            GLint infoLen = 0;

            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLen);

            if (infoLen > 1)
            {
                errorLog.resize(infoLen);

                glGetShaderInfoLog(shaderId, infoLen, NULL, &errorLog[0]);
                esLogMessage("Error compiling shader:\n%s\n", errorLog.c_str());
            }

            glDeleteShader(shaderId);
            return false;
        }

        return true;
    }

    const std::string &GLESShader::GetErrorLog() const
    {
        return errorLog;
    }

    unsigned int GLESShader::GetShaderId() const
    {
        return shaderId;
    }

    ShaderType GLESShader::GetShaderType() const
    {
        GLint shaderType = 0;
        glGetShaderiv(shaderId, GL_SHADER_TYPE, &shaderType);

        switch (shaderType)
        {
        case GL_VERTEX_SHADER:
            return ShaderType::VERTEX;
        case GL_FRAGMENT_SHADER:
            return ShaderType::FRAGMENT;
        default:
            std::cerr << "Unsupported shader type: " << shaderType << std::endl;
            return ShaderType::UNKNOWN;
        }
    }
}
