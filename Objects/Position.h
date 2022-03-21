//
// Created by jan on 22.04.20.
//

#pragma once

#include <SDL2/SDL.h>
#include "../Graphics/Texture.h"

class Position
{
public:
    
    Position ( SDL_Rect &destination );
    
    SDL_Rect operator + ( const SDL_Rect &source );
    SDL_Rect Sum ( int x, int y );
    void SetX ( int x );
    void AddX ( int x );
    void SetY ( int y );
    void AddY ( int y );
    SDL_Rect Get ( );

private:
    
    SDL_Rect m_position;
    
};
