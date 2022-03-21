//
// Created by jan on 09.05.20.
//

#pragma once

#include "Element.h"
#include "../Init/Game.h"

class TextBox : public Element
{
public:
    
    TextBox ( Texture *texture, int x, int y, int width, int height, bool visible );
    
    ~TextBox() override;
    
    bool Click ( int x, int y ) override;
    void Render ( ) override;
    void Display ( ) override;
    void Hide ( ) override;

private:
    
    Texture *m_texture;
    SDL_Rect m_dst_rectangle;
    int m_x_pos;
    int m_y_pos;
    int m_width;
    int m_height;
    bool m_visible;
    
};
