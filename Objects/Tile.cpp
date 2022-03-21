//
// Created by jan on 22.04.20.
//

#include "Tile.h"
#include "../Init/Game.h"

Tile::Tile ( Texture *texture, SDL_Rect destination, bool accessible )
        : m_texture ( texture ), m_position ( destination ), m_accessible ( accessible )
{
}

void Tile::Draw ( int x_pos, int y_pos )
{
    int y = m_position.Get ( ).y + y_pos;
    int x = m_position.Get ( ).x + x_pos;
    int h = m_position.Get ( ).h;
    int w = m_position.Get ( ).w;
    
    if ( y > -h - 5 && x > -w - 5 && y < Game::m_window_y + 5 && x < Game::m_window_x + 5)
        m_texture->Draw ( m_position.Sum ( x_pos, y_pos ) );
}

Tile::~Tile ( )
{
    delete m_texture;
}

bool Tile::IsAccessible ( )
{
    return m_accessible;
}

Position Tile::GetPosition ( )
{
    return m_position;
}
