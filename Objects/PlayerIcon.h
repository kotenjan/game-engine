//
// Created by jan on 09.05.20.
//

#pragma once

#include "Element.h"
#include "../Init/Game.h"

class PlayerIcon : public Element
{
public:
    
    PlayerIcon ( Texture *texture, int x, int y, int width, int height, bool visible, Player *player, int sword,
                 int gun, int speed, int number );
    
    ~PlayerIcon() override;
    
    bool Click ( int x, int y ) override;
    void Render ( ) override;
    void Display ( ) override;
    void Hide ( ) override;

private:
    
    Texture *m_texture;
    SDL_Rect m_dst_rectangle;
    Player *m_player;
    int m_x_pos;
    int m_y_pos;
    int m_width;
    int m_height;
    bool m_visible;
    int m_sword;
    int m_gun;
    int m_speed;
    int m_number;
    
};
