#include "shaders/ShaderProgram.h"
#include "esUtil.h"

#include <fstream>
#include <iostream>

rendix::shaders::ShaderProgram::ShaderProgram()
{
    // Crete the program object
    shaderProgramId = glCreateProgram();
}

GLuint rendix::shaders::ShaderProgram::GetShaderProgramId() const
{
    return shaderProgramId;
}

bool rendix::shaders::ShaderProgram::AttachShader(const Shader& shader)
{
    if (shaderProgramId == 0)
    {
        return false;
    }

    glAttachShader(shaderProgramId, shader.GetShaderId());

    return true;
}

bool rendix::shaders::ShaderProgram::LinkShaders()
{
    GLint linked;

    if (shaderProgramId == 0)
    {
        return false;
    }

    // Link the program
    glLinkProgram(shaderProgramId);

    // Check the link status
    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &linked);

    if (!linked)
    {
        GLint infoLen = 0;

        glGetProgramiv(shaderProgramId, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1)
        {
            std::string infoLog;
            infoLog.resize(infoLen);

            glGetProgramInfoLog(shaderProgramId, infoLen, NULL, &infoLog[0]);
            esLogMessage("Error linking shader program:\n%s\n", infoLog.c_str());
        }

        glDeleteProgram(shaderProgramId);
        return false;
    }

    return true;
}

bool rendix::shaders::ShaderProgram::Use()
{
    if (shaderProgramId == 0)
    {
        return false;
    }

    glUseProgram(shaderProgramId);

    return true;
}

bool rendix::shaders::ShaderProgram::BindAttribute(GLuint index, const GLchar* attribute)
{
    if (shaderProgramId == 0)
    {
        return false;
    }

    // Bind vPosition to attribute 0
    glBindAttribLocation(shaderProgramId, index, attribute);

    return true;
}
