//
// Created by jan on 03.05.20.
//

#pragma once

#include "Entity.h"
#include "Map.h"


class Player : public Entity
{
public:
    
    Player ( int x, int y, int size, int speed, Map *map );
    
    ~Player ( ) override;
    
    void Update ( int x, int y ) override;
    void Render ( ) override;
    int Height ( ) const override;
    int Width ( ) const override;
    int Size ( ) const override;
    void UpdateMovement ( int animation );
    bool ProximityAction ( Entity *entity ) override;
    bool ProximityAction ( int distance ) override;
    bool ProximityAction ( ) override;
    int DamageStatus ( ) override;
    bool IsFighting ( ) override;
    bool IsParying ( ) override;
    void DecreaseHealth ( int value ) override;
    void DecreaseStamina ( int value ) override;
    void SetPosition ( int x, int y );
    void ReplaceTexture ( Texture *texture );
    void DecreaseStamina ( int &x, int &y );
    
    bool operator < ( const Entity &entity ) const override;
    bool operator > ( const Entity &entity ) const override;
    
    static int stamina;
    static int health;
    static bool fencing;
    static bool protecting;

private:
    
    Texture *m_texture;
    int m_x_pos;
    int m_y_pos;
    int m_size;
    SDL_Rect m_dst_rectangle;
    Map *m_map;
    bool m_recharging;
    
};