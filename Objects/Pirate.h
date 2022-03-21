//
// Created by jan on 03.05.20.
//

#pragma once

#include "Entity.h"
#include "../Init/Game.h"
#include "Map.h"

class Pirate : public Entity
{
public:
    
    Pirate ( Texture *texture, int x, int y, int size, Map *map, Objects *objects, Databank *databank );
    
    ~Pirate ( ) override;
    
    void Update ( int x, int y ) override;
    void Render ( ) override;
    int Height ( ) const override;
    int Width ( ) const override;
    int Size ( ) const override;
    bool ProximityAction ( Entity *entity ) override;
    bool ProximityAction ( int distance ) override;
    bool ProximityAction ( ) override;
    int DamageStatus ( ) override;
    bool IsFighting ( ) override;
    void DecreaseHealth ( int value ) override;
    void DecreaseStamina ( int value ) override;
    bool IsParying ( ) override;
    void walk ( int b, int a );
    
    bool operator < ( const Entity &entity ) const override;
    bool operator > ( const Entity &entity ) const override;

private:
    
    Texture *m_texture;
    int m_x_pos;
    int m_y_pos;
    int m_size;
    int m_x_dir;
    int m_y_dir;
    int m_speed;
    int m_steps;
    int m_health;
    Map *m_map;
    int m_sequence;
    SDL_Rect m_dst_rectangle;
    Objects *m_objects;
    Databank *m_databank;
    
};