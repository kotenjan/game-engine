//
// Created by jan on 22.04.20.
//

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../Graphics/Texture.h"
#include "Position.h"

class Tile
{
public:
    
    Tile ( Texture *texture, SDL_Rect destination, bool accessible = true );
    
    ~Tile();
    
    virtual bool IsAccessible();
    virtual void Draw ( int x_pos, int y_pos );
    virtual Position GetPosition();

private:
    
    Texture *m_texture;
    Position m_position;
    bool m_accessible;
    
};
