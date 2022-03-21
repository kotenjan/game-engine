//
// Created by jan on 21.04.20.
//

#include "Texture.h"

Texture::Texture ( const char *filename, SDL_Renderer *renderer, int width, int length, int num_x, int num_y )
        : m_texture ( SDL_CreateTextureFromSurface ( renderer, IMG_Load ( filename ) ) ),
          m_renderer ( renderer ), m_frames_width ( width ), m_frames_length ( length ), m_frames_x ( num_x ),
          m_frames_y ( num_y ), m_current_x ( 0 ), m_current_y ( 0 ), m_speed ( 1000 / m_frames_x )
{
}

void Texture::Draw ( SDL_Rect destination )
{
    SDL_Rect source = { ( m_frames_width / m_frames_x ) * m_current_x,
                        ( m_frames_length / m_frames_y ) * m_current_y,
                        ( m_frames_width / m_frames_x ),
                        ( m_frames_length / m_frames_y ) };
    SDL_RenderCopy ( m_renderer, m_texture, &source, &destination );
}

void Texture::SetFrame ( int x, int y )
{
    m_current_x = x;
    m_current_y = y;
}

int Texture::NextFrame ( )
{
    m_current_x = static_cast<int>(( SDL_GetTicks ( ) / m_speed ) % m_frames_x);
    return m_current_x;
}

Texture::Texture ( const Texture *texture )
{
    m_texture = texture->m_texture;
    m_renderer = texture->m_renderer;
    m_frames_width = texture->m_frames_width;
    m_frames_length = texture->m_frames_length;
    m_frames_x = texture->m_frames_x;
    m_frames_y = texture->m_frames_y;
    m_current_x = texture->m_current_x;
    m_current_y = texture->m_current_y;
    m_speed = texture->m_speed;
}

int Texture::Width ( ) const
{
    return m_frames_width / m_frames_x;
}

int Texture::Height ( ) const
{
    return m_frames_length / m_frames_y;
}

void Texture::Draw ( )
{
    SDL_Rect source = { ( m_frames_width / m_frames_x ) * m_current_x,
                        ( m_frames_length / m_frames_y ) * m_current_y,
                        ( m_frames_width / m_frames_x ),
                        ( m_frames_length / m_frames_y ) };
    SDL_Rect destination { 0, 0, source.w, source.h };
    SDL_RenderCopy ( m_renderer, m_texture, &source, &destination );
}

Texture::~Texture ( )
{
    SDL_DestroyTexture(m_texture);
}

