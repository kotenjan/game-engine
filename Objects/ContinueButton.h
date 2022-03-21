//
// Created by jan on 09.05.20.
//

#pragma once

#include "Element.h"
#include "../Init/Game.h"

class ContinueButton : public Element
{
public:
    
    ContinueButton ( Texture *texture, int x, int y, int width, int height, bool visible, Texture *a, Texture *b, Player *player );
    
    ~ContinueButton() override;
    
    bool Click ( int x, int y ) override;
    void Render ( ) override;
    void Display ( ) override;
    void Hide ( ) override;

private:
    
    Texture *m_texture;
    Texture *m_char_a;
    Texture *m_char_b;
    Player *m_player;
    SDL_Rect m_dst_rectangle;
    int m_x_pos;
    int m_y_pos;
    int m_width;
    int m_height;
    bool m_visible;
    
};
