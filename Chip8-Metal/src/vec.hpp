//
//  vec.hpp
//  GameObjc
//
//  Created by ザスキ・オスカー on 6/29/23.
//

#pragma once
template <typename T>
struct vec2 {
    union {
        struct { T x, y; };
        struct { T w, h; };
    };
    
    T* get() {
        return &this->x;
    }
};
