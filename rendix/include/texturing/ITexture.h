#ifndef RENDIX_TEXTURING_ITEXTURE_H
#define RENDIX_TEXTURING_ITEXTURE_H

#include <memory>
#include <string>

namespace rendix::texturing {

class ITexture {
public:
    virtual ~ITexture() = default;

    virtual void bind(unsigned int slot = 0) const = 0;
    virtual void unbind() const = 0;

    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;

    static std::shared_ptr<ITexture> create(const std::string& path);
};

}  // namespace rendix::texturing

#endif  // RENDIX_TEXTURING_ITEXTURE_H
