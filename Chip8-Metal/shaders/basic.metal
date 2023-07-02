//
//  basic.metal
//  GameObjc
//
//  Created by ザスキ・オスカー on 6/27/23.
//

#include <metal_stdlib>
#include <simd/simd.h>

using namespace metal;

struct v2f {
    float4 position [[position]];
    half4 color;
};

float4x4 translate(float4x4 mat, float2 tran) {
    mat[0][3] += tran.x;
    mat[1][3] += tran.y;
    return mat;
}

float4x4 scale(float4x4 mat, float2 sc) {
    mat[0][0] *= sc.x;
    mat[1][1] *= sc.y;
    return mat;
}

vertex v2f basic_vertex( uint vertexId [[vertex_id]], device const float3* positions [[buffer(0)]], device const float4* colors [[buffer(1)]], device const float2* newPos [[buffer(2)]] ) {
    float4x4 model = {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0, 0.0, 1.0}
    };
    
    float4x4 view = model;
    
    model = translate(model, float2(-480.0, -240.0));
    model = translate(model, *newPos);
    view = scale(view, float2(1/480.0, -1/240.0));
    
    float4 mvp = transpose(view) * transpose(model) * float4(positions[vertexId], 1.0);
    
    v2f o;
    o.position = mvp;
    o.color = half4(*colors);
    return o;
}

fragment half4 basic_fragment( v2f in [[stage_in]] ) {
    return in.color;
}
