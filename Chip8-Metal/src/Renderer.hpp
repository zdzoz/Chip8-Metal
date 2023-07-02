//
//  Renderer.hpp
//  GameObjc
//
//  Created by ザスキ・オスカー on 6/22/23.
//

#pragma once
#include <Metal/Metal.hpp>
#include <queue>
#include <mutex>

#include "shape.hpp"

#define TRUE 1
#define FALSE 0

#define EMULATOR_WIDTH 960
#define EMULATOR_HEIGHT 480
#define EMULATOR_WIDTH_PX 64
#define EMULATOR_HEIGHT_PX 32
#define PIXEL_W (EMULATOR_WIDTH/EMULATOR_WIDTH_PX)
#define PIXEL_H (EMULATOR_HEIGHT/EMULATOR_HEIGHT_PX)

#define WINDOW_WIDTH EMULATOR_WIDTH
#define WINDOW_HEIGHT 480

#define PIXEL_ON 0xff/0xff, 0xff/0xff, 0xff/0xff, 0xff/0xff
#define PIXEL_OFF 0.0, 0.0, 0.0, 0.0

class Renderer {
    MTL::Device* device_;
    MTL::CommandQueue* CommandQueue_;
    MTL::RenderPipelineState* PSO_;
    static Renderer* _ren;
    static int count;
    mutable std::queue<std::shared_ptr<Shape>> drawables;
public:
    mutable std::mutex drawLock;
    Renderer(MTL::Device* device);
    ~Renderer();
    
    static Renderer& instance();
    
    inline MTL::Device* const Device() const {
        return device_;
    }
    
    void buildShaders();
    void buildBuffers();
    void draw(MTL::RenderPassDescriptor* rpd, CA::MetalDrawable* currentDrawable) const;
    
    void addDrawable(std::shared_ptr<Shape> shape) const;
    
    void DrawPixel(const uint8_t x, const uint8_t y);
    
    void DrawScreen();
    
    void ClearScreen();
};
