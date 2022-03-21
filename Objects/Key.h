//
// Created by jan on 04.06.20.
//

#pragma once

#include "Entity.h"

class Key : public Entity
{
public:
    Key ( Texture *texture, int x, int y, int size );
    
    ~Key ( ) override;
    
    void Update ( int x, int y ) override;
    void Render ( ) override;
    int Height ( ) const override;
    int Width ( ) const override;
    int Size  () const override;
    bool ProximityAction(Entity *entity) override;
    int DamageStatus ( ) override;
    bool IsFighting ( ) override;
    void DecreaseHealth ( int value ) override;
    void DecreaseStamina ( int value ) override;
    bool IsParying ( ) override;
    
    bool operator < ( const Entity &entity ) const override;
    bool operator > ( const Entity &entity ) const override;

private:
    
    Texture *m_texture;
    int m_x_pos;
    int m_y_pos;
    int m_size;
    SDL_Rect m_dst_rectangle;
    
};
