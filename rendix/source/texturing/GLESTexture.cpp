#include "texturing/GLESTexture.h"
#include "texturing/ITexture.h"
#include <GLES2/gl2.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace rendix::texturing {

std::shared_ptr<ITexture> ITexture::create(const std::string& path) {
    return std::make_shared<GLESTexture>(path);
}

GLESTexture::GLESTexture(const std::string& path)
    : m_id(0), m_width(0), m_height(0) {
    int channels;
    stbi_uc* data = stbi_load(path.c_str(), &m_width, &m_height, &channels, STBI_rgb_alpha);

    if (!data) {
        std::cerr << "Failed to load texture: " << path << std::endl;
        return;
    }

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

GLESTexture::~GLESTexture() {
    glDeleteTextures(1, &m_id);
}

void GLESTexture::bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void GLESTexture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

}  // namespace rendix::texturing