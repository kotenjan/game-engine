//
// Created by jan on 08.05.20.
//

#include "GameStart.h"

GameStart::GameStart ( Texture *texture, int x, int y, int width, int height, bool visible )
        : m_texture ( texture ), m_x_pos ( x ), m_y_pos ( y ), m_width ( width ), m_height ( height ),
          m_visible ( visible )
{
    m_dst_rectangle.x = m_x_pos;
    m_dst_rectangle.y = m_y_pos;
    m_dst_rectangle.w = m_width;
    m_dst_rectangle.h = m_height;
}

bool GameStart::Click ( int x, int y )
{
    if ( x >= m_x_pos && x <= m_x_pos + m_height )
        if ( y >= m_y_pos && y <= m_y_pos + m_width )
            return true;
    return false;
}

void GameStart::Render ( )
{
    if ( m_visible )
        m_texture->Draw ( m_dst_rectangle );
}

void GameStart::Display ( )
{
    m_visible = true;
}

void GameStart::Hide ( )
{
    m_visible = false;
}

GameStart::~GameStart ( )
{
    delete m_texture;
}
