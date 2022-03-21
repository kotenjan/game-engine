//
// Created by jan on 22.04.20.
//

#include "Entity.h"

Entity::Entity ( ) = default;

Entity::~Entity ( ) = default;

void Entity::Update ( int x, int y )
{
}

void Entity::Render ( )
{
}

bool Entity::operator < ( const Entity &entity ) const
{
    return false;
}

bool Entity::operator > ( const Entity &entity ) const
{
    return false;
}

int Entity::Height ( ) const
{
    return 0;
}

int Entity::Width ( ) const
{
    return 0;
}

int Entity::Size ( ) const
{
    return 0;
}

bool Entity::ProximityAction ( Entity *entity )
{
    return true;
}

std::pair<int, int> Entity::Distance ( Entity *first, Entity *second )
{
    int x_a = first->Height ( ) - first->Size ( ) / 2;
    int y_a = first->Width ( ) - first->Size ( ) / 2;
    int x_b = second->Height ( ) - second->Size ( ) / 2;
    int y_b = second->Width ( ) - second->Size ( ) / 2;
    return std::pair<int, int>{x_b - x_a, y_b - y_a};
}

int Entity::DamageStatus ( )
{
    return 1;
}

bool Entity::ProximityAction ( int distance )
{
    return true;
}

bool Entity::ProximityAction ( )
{
    return true;
}

void Entity::DecreaseHealth ( int value )
{

}

bool Entity::IsFighting() {
    return false;
}

bool Entity::IsParying ( )
{
    return false;
}

void Entity::DecreaseStamina ( int value )
{

}
