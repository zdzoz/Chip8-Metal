//
//  Rect.cpp
//  GameObjc
//
//  Created by ザスキ・オスカー on 6/29/23.
//

#include "rectangle.hpp"

#include <simd/simd.h>

#include "Renderer.hpp"

bool Rectangle::isCompiled = false;
MTL::RenderPipelineState* Rectangle::PSO_ = nullptr;

Rectangle::Rectangle() noexcept : dim({0.0f, 0.0f}) {
    if (!isCompiled) compile_shaders();
    make_buffers();
}

Rectangle::Rectangle(float r, float g, float b, float a) noexcept {
    color = {r, g, b, a};
    if (!isCompiled) compile_shaders();
    make_buffers();
}

Rectangle::Rectangle(Color rgba) noexcept {
    color = rgba;
    if (!isCompiled) compile_shaders();
    make_buffers();
}

Rectangle::Rectangle(float w, float h) noexcept : dim({w, h}) {
    if (!isCompiled) compile_shaders();
    make_buffers();
}

Rectangle::Rectangle(float w, float h, Color rgba) noexcept : dim({w, h}) {
    color = rgba;
    if (!isCompiled) compile_shaders();
    make_buffers();
}

Rectangle::Rectangle(float w, float h, float r, float g, float b, float a) noexcept : dim({w, h}) {
    color = {r, g, b, a};
    if (!isCompiled) compile_shaders();
    make_buffers();
}

void Rectangle::compile_shaders() {
    using NS::StringEncoding::UTF8StringEncoding;
    
    NS::Error* pError = nullptr;
    auto pLibrary = NS::TransferPtr(Renderer::instance().Device()->newDefaultLibrary());
    if ( !pLibrary )
    {
        printf( "%s", pError->localizedDescription()->utf8String() );
        assert( false );
    }
    
    auto pVertFn = NS::TransferPtr(pLibrary->newFunction( NS::String::string("basic_vertex", UTF8StringEncoding) ));
    auto pFragFn = NS::TransferPtr(pLibrary->newFunction( NS::String::string("basic_fragment", UTF8StringEncoding) ));

    auto pDesc = NS::TransferPtr(MTL::RenderPipelineDescriptor::alloc()->init());
    pDesc->setVertexFunction( pVertFn.get() );
    pDesc->setFragmentFunction( pFragFn.get() );
    pDesc->colorAttachments()->object(0)->setPixelFormat( MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB );

    PSO_ = Renderer::instance().Device()->newRenderPipelineState( pDesc.get(), &pError );
    if ( !PSO_ ) {
        __builtin_printf( "%s", pError->localizedDescription()->utf8String() );
        assert( false );
    }
    isCompiled = true;
}

void Rectangle::make_buffers() {
    simd::float3 positions[] = {
        {  0.0f,  0.0f, 0.0f },
        {  0.0f, dim.h, 0.0f },
        { dim.w, dim.h, 0.0f },
        { dim.w,  0.0f, 0.0f }
    };
    
    dim.x = 0.0f;
    dim.y = 0.0f;
    
    uint16_t indices[] {
        0, 1, 2,
        2, 3, 0
    };

    vertexPosBuffer_ = Renderer::instance().Device()->newBuffer(positions, 4 * sizeof(simd::float3), MTL::ResourceStorageModeManaged);
    indexPosBuffer_ = Renderer::instance().Device()->newBuffer(indices, 6 * sizeof(uint16_t), MTL::ResourceStorageModeManaged);
}

void Rectangle::draw() {
    
}

void Rectangle::pos(float x, float y) {
    dim.x = x;
    dim.y = y;
}

float* Rectangle::pos() {
    return dim.get();
}

const float& Rectangle::x() const {
    return dim.x;
}

const float& Rectangle::y() const {
    return dim.y;
}
