//
//  shape.hpp
//  GameObjc
//
//  Created by ザスキ・オスカー on 6/29/23.
//

#pragma once
#include <Metal/Metal.hpp>

#include <iostream>

#include "vec.hpp"

class Shape {
protected:
//    MTL::RenderPipelineState* PSO_;
    MTL::Buffer* vertexPosBuffer_;
    MTL::Buffer* indexPosBuffer_;
    
    struct Color {
        float r, g, b, a;
    } color;
    
    Shape() noexcept {};
    ~Shape() {
//        PSO_->release();
        vertexPosBuffer_->release();
        indexPosBuffer_->release();
    };
public:
    virtual void draw() = 0;
    
    virtual inline const Color* const rgba() const = 0;
    
    virtual const MTL::RenderPipelineState* PSO() const = 0;
    
    virtual void pos(float x, float y) = 0;
    virtual float* pos() = 0;
    
    inline const MTL::Buffer* vertexBuffer() const {
        return vertexPosBuffer_;
    }
    
    inline const MTL::Buffer* indexBuffer() const {
        return indexPosBuffer_;
    }
};
