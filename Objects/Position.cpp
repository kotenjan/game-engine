//
// Created by jan on 22.04.20.
//

#include "Position.h"

Position::Position ( SDL_Rect &destination )
        : m_position ( destination )
{
}

SDL_Rect Position::operator + ( const SDL_Rect &source )
{
    return SDL_Rect { m_position.x + source.x, m_position.y + source.y, m_position.w, m_position.h };
}

SDL_Rect Position::Sum ( int x, int y )
{
    return SDL_Rect { m_position.x + x, m_position.y + y, m_position.w, m_position.h };
}

void Position::SetX ( int x )
{
    m_position.x = x;
}

void Position::AddX ( int x )
{
    m_position.x += x;
}

void Position::SetY ( int y )
{
    m_position.y = y;
}

void Position::AddY ( int y )
{
    m_position.y = y;
}

SDL_Rect Position::Get ( )
{
    return m_position;
}
