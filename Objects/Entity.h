//
// Created by jan on 22.04.20.
//

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../Graphics/Texture.h"

class Entity
{
public:
    
    Entity ( );
    virtual ~Entity ( );
    
    virtual void Update ( int x, int y );
    virtual void Render ( );
    virtual int Height ( ) const;
    virtual int Width ( ) const;
    virtual int Size ( ) const;
    virtual bool ProximityAction ( Entity *entity );
    virtual bool ProximityAction ( int distance );
    virtual bool ProximityAction ( );
    virtual int DamageStatus ( );
    virtual void DecreaseHealth ( int value );
    virtual void DecreaseStamina ( int value );
    virtual bool IsFighting ( );
    virtual bool IsParying ( );
    
    virtual bool operator < ( const Entity &entity ) const;
    virtual bool operator > ( const Entity &entity ) const;
    
    static std::pair<int, int> Distance ( Entity *first, Entity *second );
    
};
