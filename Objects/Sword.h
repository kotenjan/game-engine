//
// Created by jan on 04.06.20.
//

//
// Created by jan on 04.06.20.
//

#pragma once

#include "Entity.h"

class Sword : public Entity
{
public:
    Sword ( Texture *texture, int size, int x, int y );
    
    ~Sword ( ) override;
    
    void Update ( int x, int y ) override;
    void Render ( ) override;
    int Height ( ) const override;
    int Width ( ) const override;
    int Size  () const override;
    bool ProximityAction(Entity *entity) override;
    int DamageStatus ( ) override;
    
    bool operator < ( const Entity &entity ) const override;
    bool operator > ( const Entity &entity ) const override;

private:
    
    Texture *m_texture;
    int m_x_pos;
    int m_y_pos;
    int m_size;
    SDL_Rect m_dst_rectangle;
    
};
