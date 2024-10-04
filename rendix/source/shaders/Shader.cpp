#include "shaders/Shader.h"
#include "esUtil.h"

#include <fstream>
#include <iostream>

rendix::shaders::Shader::Shader(GLenum type)
{
    // Create the shader object
    shaderId = glCreateShader(type);
}

GLuint rendix::shaders::Shader::GetShaderId() const
{
    return shaderId;
}

bool rendix::shaders::Shader::LoadFromString(const std::string& sourceCode)
{
    // Load the shader source
    glShaderSource(shaderId, 1, (const GLchar *const *)sourceCode.c_str(), NULL);

    return true;
}

bool rendix::shaders::Shader::LoadFromFile(const std::string& fileName)
{
    std::string sourceCode;
    std::ifstream shaderFile(fileName);
    
    if (!shaderFile) {
        std::cerr << "Could not open " << fileName << " shader file" << std::endl;
        return false;
    }

    this->fileName = fileName;

    shaderFile.seekg(0, std::ios::end);
    sourceCode.resize(shaderFile.tellg());
    shaderFile.seekg(0);
    shaderFile.read(&sourceCode[0], sourceCode.size());

    return LoadFromString(sourceCode);
}

bool rendix::shaders::Shader::Compile()
{
    GLint compiled;

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
            std::string infoLog;
            infoLog.resize(infoLen);

            glGetShaderInfoLog(shaderId, infoLen, NULL, &infoLog[0]);
            esLogMessage("Error compiling shader:\n%s\n", infoLog.c_str());
        }

        glDeleteShader(shaderId);
        return false;
    }

    return true;
}
