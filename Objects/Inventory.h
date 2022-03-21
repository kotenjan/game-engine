//
// Created by jan on 09.05.20.
//

#pragma once

#include "Element.h"

class Inventory : public Element
{
public:
    
    Inventory ( Texture *texture, Texture *valid,Texture *invalid, int x, int y, int width, int height, bool visible );
    
    ~Inventory() override;
    
    bool Click ( int x, int y ) override;
    void Render ( ) override;
    void Display ( ) override;
    void Hide ( ) override;
    
    static int Key;
    static int Gun;
    static int Sword;

private:

    Texture *m_texture;
    Texture *m_valid;
    Texture *m_invalid;
    int m_x_pos;
    int m_y_pos;
    int m_width;
    int m_height;
    bool m_visible;
    SDL_Rect m_dst_rectangle;
    
};
