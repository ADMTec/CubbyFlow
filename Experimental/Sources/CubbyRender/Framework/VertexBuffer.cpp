/*************************************************************************
> File Name: VertexBuffer.cpp
> Project Name: CubbyFlow
> This code is based on Jet Framework that was created by Doyub Kim.
> References: https://github.com/doyubkim/fluid-engine-dev
> Purpose: Abstract base class for VertexBuffer object.
> Created Time: 2020/03/16
> Copyright (c) 2020, Ji-Hong snowapril
*************************************************************************/
#include <Framework/VertexBuffer.h>

namespace CubbyFlow {
namespace CubbyRender {
    
    VertexBuffer::VertexBuffer()
    {
        //! Do nothing
    }

    VertexBuffer::VertexBuffer(size_t numberOfElements, VertexFormat format)
        : Buffer(nullptr, numberOfElements, format)
    {
        //! Do nothing
    }

    VertexBuffer::~VertexBuffer()
    {
        //! Do nothing
    }

} 
}