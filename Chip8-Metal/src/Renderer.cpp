//
//  Renderer.cpp
//  GameObjc
//
//  Created by ザスキ・オスカー on 6/22/23.
//

// generate metal implementation
#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION

#include "Renderer.hpp"

#include <iostream>
#include <simd/simd.h>
#include "rectangle.hpp"

#define CLEAR_COLOR MTL::ClearColor(4/255., 4/255., 6/255., 1.)
#define NSUInt(x) NS::UInteger(x)

typedef NS::UInteger nsuint;
typedef NS::String nsstring;

int Renderer::count = 0;
Renderer* Renderer::_ren = nullptr;

Renderer::Renderer(MTL::Device* device) : device_(device->retain()), CommandQueue_(device->newCommandQueue()) {
    if (count++ > 0) assert(false);
    _ren = this;
//    buildShaders();
//    buildBuffers();
}

Renderer::~Renderer() {
//    VertexPositionsBuffer_->release();
//    VertexColorsBuffer_->release();
    PSO_->release();
    CommandQueue_->release();
    device_->release();
    count--;
}

Renderer& Renderer::instance() {
    return *_ren;
}

void Renderer::draw(MTL::RenderPassDescriptor* rpd, CA::MetalDrawable* currentDrawable) const {
    rpd->colorAttachments()->object(0)->setClearColor(CLEAR_COLOR);
    auto pPool = NS::TransferPtr(NS::AutoreleasePool::alloc()->init());

    MTL::CommandBuffer* pCmd = CommandQueue_->commandBuffer();
    
    MTL::RenderCommandEncoder* pEnc = pCmd->renderCommandEncoder( rpd );
    
    drawLock.lock();
    while (!drawables.empty()) {
        auto shape = drawables.front();
        drawables.pop();
        pEnc->setRenderPipelineState( shape->PSO() );
        pEnc->setVertexBuffer(shape->vertexBuffer(), 0, 0);
        pEnc->setVertexBytes(shape->rgba(), 4 * sizeof(float), 1);
        pEnc->setVertexBytes(shape->pos(), 2 * sizeof(float), 2);
        pEnc->drawIndexedPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, (nsuint)6, MTL::IndexType::IndexTypeUInt16, shape->indexBuffer(), (nsuint)0);
    }
    drawLock.unlock();
    
    pEnc->endEncoding();
    pCmd->presentDrawable(currentDrawable);
    pCmd->commit();
}

void Renderer::addDrawable(std::shared_ptr<Shape> shape) const {
    drawables.push(shape);
}

void Renderer::DrawPixel(const uint8_t x, const uint8_t y) {
    drawLock.lock();
    auto rect = std::make_shared<Rectangle>(PIXEL_W, PIXEL_H, PIXEL_ON);
    rect->pos(x * PIXEL_W, y * PIXEL_H);
    addDrawable(rect);
    drawLock.unlock();
}

void Renderer::DrawScreen() {}

void Renderer::ClearScreen() {}
