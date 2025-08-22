#ifndef RENDIX_TEXTURING_GLES_TEXTURE_H
#define RENDIX_TEXTURING_GLES_TEXTURE_H

#include "texturing/ITexture.h"
#include <string>

namespace rendix::texturing {

class GLESTexture : public ITexture {
public:
    GLESTexture(const std::string& path);
    ~GLESTexture();

    void bind(unsigned int slot = 0) const override;
    void unbind() const override;

    int getWidth() const override { return m_width; }
    int getHeight() const override { return m_height; }

private:
    unsigned int m_id;
    int m_width;
    int m_height;
};

}  // namespace rendix::texturing

#endif  // RENDIX_TEXTURING_GLES_TEXTURE_H