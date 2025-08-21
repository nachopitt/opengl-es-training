#include "shaders/GLESShaderProgram.h"
#include "esUtil.h"

#include <fstream>
#include <iostream>

rendix::shaders::GLESShaderProgram::~GLESShaderProgram()
{
    if (shaderProgramId != 0)
    {
        glDeleteProgram(shaderProgramId);
    }
}

rendix::shaders::GLESShaderProgram::GLESShaderProgram()
{
    // Crete the program object
    shaderProgramId = glCreateProgram();
}

GLuint rendix::shaders::GLESShaderProgram::GetShaderProgramId() const
{
    return shaderProgramId;
}

bool rendix::shaders::GLESShaderProgram::AttachShader(const IShader &shader)
{
    if (shaderProgramId == 0)
    {
        return false;
    }

    glAttachShader(shaderProgramId, shader.GetShaderId());

    return true;
}

bool rendix::shaders::GLESShaderProgram::LinkShaders()
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
            linkLog.resize(infoLen);

            glGetProgramInfoLog(shaderProgramId, infoLen, NULL, &linkLog[0]);
            esLogMessage("Error linking shader program:\n%s\n", linkLog.c_str());
        }

        glDeleteProgram(shaderProgramId);
        return false;
    }

    return true;
}

bool rendix::shaders::GLESShaderProgram::Use()
{
    if (shaderProgramId == 0)
    {
        return false;
    }

    glUseProgram(shaderProgramId);

    return true;
}

bool rendix::shaders::GLESShaderProgram::BindAttribute(unsigned int index, const std::string &attribute)
{
    if (shaderProgramId == 0)
    {
        return false;
    }

    // Bind vPosition to attribute 0
    glBindAttribLocation(shaderProgramId, index, attribute.c_str());

    return true;
}

int rendix::shaders::GLESShaderProgram::GetAttributeLocation(const std::string &name) const
{
    if (shaderProgramId == 0)
    {
        return -1;
    }

    return glGetAttribLocation(shaderProgramId, name.c_str());
}

const std::string& rendix::shaders::GLESShaderProgram::GetLinkLog() const
{
    return linkLog;
}

void rendix::shaders::GLESShaderProgram::SetUniform(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(shaderProgramId, name.c_str()), value);
}

void rendix::shaders::GLESShaderProgram::SetUniform(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(shaderProgramId, name.c_str()), value);
}

void rendix::shaders::GLESShaderProgram::SetUniform(const std::string& name, const glm::vec2& value)
{
    glUniform2fv(glGetUniformLocation(shaderProgramId, name.c_str()), 1, glm::value_ptr(value));
}

void rendix::shaders::GLESShaderProgram::SetUniform(const std::string& name, const glm::vec3& value)
{
    glUniform3fv(glGetUniformLocation(shaderProgramId, name.c_str()), 1, glm::value_ptr(value));
}

void rendix::shaders::GLESShaderProgram::SetUniform(const std::string& name, const glm::vec4& value)
{
    glUniform4fv(glGetUniformLocation(shaderProgramId, name.c_str()), 1, glm::value_ptr(value));
}

void rendix::shaders::GLESShaderProgram::SetUniform(const std::string& name, const glm::mat4& value)
{
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramId, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
