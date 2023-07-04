//
//  Renderer.m
//  GameObjc
//
//  Created by ザスキ・オスカー on 6/22/23.
//

#import "RendererAdapter.h"

#include "Renderer.hpp"

@implementation RendererAdapter
{
    std::unique_ptr<Renderer> _renderer;
}

-(nonnull instancetype)initWithMetalKitView:(nonnull MTKView *)view;
{
    self = [super init];
    if (self)
    {
        _renderer = std::make_unique<Renderer>((__bridge MTL::Device*)view.device);
    }
    return self;
}

- (void)drawInMTKView:(nonnull MTKView *)view {
    _renderer->draw((__bridge MTL::RenderPassDescriptor*)view.currentRenderPassDescriptor, (__bridge CA::MetalDrawable*)view.currentDrawable);
}

- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size {
    /// Respond to drawable size or orientation changes here
}

@end
