#ifndef RENDIX_SHADERS_GLES_SHADER_PROGRAM_H
#define RENDIX_SHADERS_GLES_SHADER_PROGRAM_H

#include <vector>
#include <GLES2/gl2.h>
#include <string>

#include "shaders/IShaderProgram.h"
#include "shaders/GLESShader.h"

namespace rendix::shaders
{
    class GLESShaderProgram : public IShaderProgram
    {
        public:
            GLESShaderProgram();
            ~GLESShaderProgram();

            unsigned int GetShaderProgramId() const override;
            bool AttachShader(const IShader& shader) override;
            bool LinkShaders() override;
            bool Use() override;
            bool BindAttribute(unsigned int index, const std::string &attribute) override;
            int GetAttributeLocation(const std::string& name) const override;
            const std::string& GetLinkLog() const override;

        private:
            GLuint shaderProgramId;
            std::string linkLog;
    };
}

#endif //RENDIX_SHADERS_GLES_SHADER_PROGRAM_H
