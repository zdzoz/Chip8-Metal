//
//  Rect.hpp
//  GameObjc
//
//  Created by ザスキ・オスカー on 6/29/23.
//

#pragma once

#include "shape.hpp"
#include "vec.hpp"

class Rectangle : public Shape {
    static MTL::RenderPipelineState* PSO_;
    static bool isCompiled;
    vec2<float> dim;
    void compile_shaders();
    void make_buffers();
public:
    Rectangle() noexcept;
    Rectangle(float r, float g, float b, float a) noexcept;
    Rectangle(Color rgba) noexcept;
    Rectangle(float w, float h) noexcept;
    Rectangle(float w, float h, Color rgba) noexcept;
    Rectangle(float w, float h, float r, float g, float b, float a) noexcept;
    
    void draw() override;
    
    void pos(float x, float y) override;
    float* pos() override;
    
    virtual inline const Color* const rgba() const override {
        return &color;
    }
    
    virtual const MTL::RenderPipelineState* PSO() const override {
        return PSO_;
    }
    
    const float& x() const;
    const float& y() const;
    
};
