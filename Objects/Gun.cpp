//
// Created by jan on 04.06.20.
//

#include "Gun.h"
#include "../Init/Game.h"

Gun::Gun ( Texture *texture, int size, int x, int y )
        : m_texture ( texture ),
          m_size ( size )
{
    m_x_pos = x;
    m_y_pos = y;
    m_texture->SetFrame ( 0, 0 );
    m_dst_rectangle.x = m_x_pos;
    m_dst_rectangle.y = m_y_pos;
    m_dst_rectangle.w = m_size;
    m_dst_rectangle.h = m_size;
}

Gun::~Gun ( )
{
    delete m_texture;
}

void Gun::Update ( int x, int y )
{
    m_x_pos += x;
    m_y_pos += y;
    
    m_dst_rectangle.x = m_x_pos;
    m_dst_rectangle.y = m_y_pos;
}

void Gun::SetPosition ( int x, int y )
{
    m_x_pos = x;
    m_y_pos = y;
    
    m_dst_rectangle.x = m_x_pos;
    m_dst_rectangle.y = m_y_pos;
}

void Gun::Render ( )
{
    if ( m_y_pos > -m_dst_rectangle.h - 5 && m_x_pos > -m_dst_rectangle.w - 5
         && m_y_pos < Game::m_window_y + 5 && m_x_pos < Game::m_window_x + 5 )
    {
        m_texture->NextFrame ( );
        m_texture->Draw ( m_dst_rectangle );
    }
}

bool Gun::operator < ( const Entity &entity ) const
{
    return m_y_pos < entity.Height ( );
}

bool Gun::operator > ( const Entity &entity ) const
{
    return m_y_pos > entity.Height ( );
}

int Gun::Height ( ) const
{
    return m_y_pos;
}

int Gun::Width ( ) const
{
    return m_x_pos;
}

int Gun::Size ( ) const
{
    return m_size;
}

bool Gun::ProximityAction ( Entity *entity )
{
    if ( DamageStatus ( ) == entity->DamageStatus ( ) )
        return true;
    
    auto vec = Entity::Distance ( this, entity );
    int distance = ( int ) sqrt ( pow ( vec.first + 32, 2 ) + pow ( vec.second + 24, 2 ) );
    if ( distance < ( m_size ) )
    {
        Inventory::Gun += Game::m_gun_amount/2;
        return false;
    }
    
    return true;
}

int Gun::DamageStatus ( )
{
    return 1;
}

bool Gun::IsParying ( )
{
    return Entity::IsParying ( );
}

void Gun::DecreaseStamina ( int value )
{
    Entity::DecreaseStamina ( value );
}

void Gun::DecreaseHealth ( int value )
{
    Entity::DecreaseHealth ( value );
}

bool Gun::IsFighting ( )
{
    return Entity::IsFighting ( );
}
