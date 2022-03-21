//
// Created by jan on 22.04.20.
//

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "../Graphics/Databank.h"
#include "../Graphics/Texture.h"
#include "Tile.h"
#include "Objects.h"
#include <fstream>
#include "Key.h"

class Map
{
public:
    
    Map ( Databank *databank, int tile_size, int width, int height, Objects *objects );
    
    ~Map ( );
    
    void Render ( );
    
    bool IsAccessible ( int x, int y, int size );
    void Update ( int x, int y );
    Tile *GetTile ( int x, int y );
    SDL_Rect GetRandomAccessible ( );
    int GetFreeTiles();
    void SetPosition(int x, int y);
    
    std::vector<Tile*> m_tiles;
    int m_length;
    int m_height;
    int m_x_pos;
    int m_y_pos;
    int m_tile_size;
    int m_screen_size_x;
    int m_screen_size_y;
    Databank *m_databank;
    Objects *m_objects;
    Entity *m_key;
    
};