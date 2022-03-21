//
// Created by jan on 02.05.20.
//

#pragma once

#include "Entity.h"
#include "../Graphics/Databank.h"
#include <iostream>
#include <list>
#include <algorithm>
#include "Gun.h"
#include "Sword.h"

class Objects
{
public:
    
    Objects ( Databank *databank);
    ~Objects ( );
    
    void Render ( Entity *player );
    void Add    ( Entity *entity);
    void Update ( Entity *player, int x = 0, int y = 0);

private:
    
    std::list<Entity*> m_entities;
    Databank *m_databank;
};
