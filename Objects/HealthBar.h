//
// Created by jan on 08.05.20.
//
#pragma once

#include <SDL2/SDL_rect.h>
#include "../Graphics/Texture.h"
#include "Element.h"
#include "Player.h"

class HealthBar : public Element
{
public:
    
    HealthBar ( Texture *texture, Texture *point, int x, int y, int width, int height, bool visible );
    
    ~HealthBar() override;
    
    bool Click ( int x, int y ) override;
    void Render ( ) override;
    void Display ( ) override;
    void Hide ( ) override;

private:
    
    Texture *m_texture;
    Texture *m_points;
    SDL_Rect m_dst_rectangle;
    int m_x_pos;
    int m_y_pos;
    int m_width;
    int m_height;
    bool m_visible;
};
