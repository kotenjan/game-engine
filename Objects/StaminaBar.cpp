//
// Created by jan on 08.05.20.
//

#include "StaminaBar.h"

StaminaBar::StaminaBar ( Texture *texture, Texture *point, int x, int y, int width, int height, bool visible )
        : m_texture ( texture ), m_points ( point ), m_x_pos ( x ), m_y_pos ( y ), m_width ( width ),
          m_height ( height ), m_visible ( visible )
{
    m_dst_rectangle.x = m_x_pos;
    m_dst_rectangle.y = m_y_pos;
    m_dst_rectangle.w = m_width;
    m_dst_rectangle.h = m_height;
}

bool StaminaBar::Click ( int x, int y )
{
    return false;
}

void StaminaBar::Render ( )
{
    if ( m_visible )
    {
        int line = m_points->Width ( );
        int health = ( int ) ( ( float ) m_texture->Width ( ) / ( float ) m_points->Width ( ) *
                               ( float ) Player::stamina / 100.0 );
        
        SDL_Rect rect;
        rect.x = m_x_pos;
        rect.y = m_y_pos;
        rect.w = 5;
        rect.h = 16;
        
        for ( int i = 0; i < health; i++ )
        {
            m_points->Draw ( rect );
            rect.x += line;
        }
        
        m_texture->Draw ( m_dst_rectangle );
        
    }
}

void StaminaBar::Display ( )
{
    m_visible = true;
}

void StaminaBar::Hide ( )
{
    m_visible = false;
}

StaminaBar::~StaminaBar ( )
{
    delete m_texture;
    delete m_points;
}
