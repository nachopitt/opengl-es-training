#ifndef RENDIX_RENDERING_GLES_CONVERT_H
#define RENDIX_RENDERING_GLES_CONVERT_H

#include "rendering/Vertex.h"
#include <GLES2/gl2.h>

namespace rendix::rendering {

    GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type);

} // namespace rendix::rendering

#endif //RENDIX_RENDERING_GLES_CONVERT_H
