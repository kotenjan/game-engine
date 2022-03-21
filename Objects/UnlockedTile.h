//
// Created by jan on 22.04.20.
//

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../Graphics/Texture.h"
#include "Position.h"
#include "Tile.h"

class UnlockedTile : public Tile
{
public:
    
    UnlockedTile ( Texture *texture, SDL_Rect destination, bool accessible = true );
    
    bool IsAccessible ( ) override;
    void Draw ( int x_pos, int y_pos ) override;
    Position GetPosition ( ) override;
    
};
