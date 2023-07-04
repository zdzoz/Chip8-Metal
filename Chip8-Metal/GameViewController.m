//
//  GameViewController.m
//  GameObjc
//
//  Created by ザスキ・オスカー on 6/22/23.
//

#import "GameViewController.h"
#import "RendererAdapter.h"

#define EMULATOR_WIDTH 960
#define EMULATOR_HEIGHT 480

@implementation GameViewController
{
    MTKView *_view;

    RendererAdapter *_renderer;
    bool isResizable;
}

- (void)viewDidAppear {
    [super viewDidAppear];
    NSRect frame = [self.view.window frame];
    frame.size = CGSizeMake(EMULATOR_WIDTH, EMULATOR_HEIGHT);
    [self.view.window setFrame:frame display:YES];
    
    if (!isResizable)
        self.view.window.styleMask &= ~NSWindowStyleMaskResizable;
}

- (void)viewDidLoad {
    [super viewDidLoad];

    isResizable = NO;
    
    _view = (MTKView *)self.view;

    _view.device = MTLCreateSystemDefaultDevice();
    _view.colorPixelFormat = MTLPixelFormatBGRA8Unorm_sRGB;

    if(!_view.device)
    {
        NSLog(@"Metal is not supported on this device");
        self.view = [[NSView alloc] initWithFrame:self.view.frame];
        return;
    }

    _renderer = [[RendererAdapter alloc] initWithMetalKitView:_view];

    [_renderer mtkView:_view drawableSizeWillChange:_view.bounds.size];
    
    _view.delegate = _renderer;
}

@end
