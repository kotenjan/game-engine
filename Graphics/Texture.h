//
// Created by jan on 21.04.20.
//

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Texture
{
public:
    
    Texture ( const char *filename, SDL_Renderer *renderer, int width, int length, int num_x, int num_y );
    
    explicit Texture (const Texture *texture);
    
    ~Texture ( );
    
    void Draw ( SDL_Rect destination );
    void Draw ();
    void SetFrame(int x, int y);
    int NextFrame();
    int Width() const;
    int Height() const;
    
private:
    
    SDL_Texture  *m_texture;
    SDL_Renderer *m_renderer;
    int           m_frames_width;
    int           m_frames_length;
    int           m_frames_x;
    int           m_frames_y;
    int           m_current_x;
    int           m_current_y;
    int           m_speed;
    int           m_timeout;
    
};
