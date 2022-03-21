//
// Created by jan on 15.06.20.
//

#pragma once

#include <cstdint>

class Controller
{
public:
    
    void Run ( int width, int height, unsigned frame_start, unsigned frame_time, uint8_t framerate,
               uint8_t delay );
};
