//
// Created by jan on 04.06.20.
//

#include "Key.h"
#include "../Init/Game.h"

Key::Key ( Texture *texture, int x, int y, int size )
        : m_texture ( texture ),
          m_x_pos ( x ),
          m_y_pos ( y ),
          m_size ( size )
{
    m_texture->SetFrame ( 0, 0 );
    m_dst_rectangle.x = m_x_pos;
    m_dst_rectangle.y = m_y_pos;
    m_dst_rectangle.w = m_size;
    m_dst_rectangle.h = m_size;
}

Key::~Key ( )
{
    delete m_texture;
}

void Key::Update ( int x, int y )
{
    m_x_pos += x;
    m_y_pos += y;
    
    m_dst_rectangle.x = m_x_pos;
    m_dst_rectangle.y = m_y_pos;
}

void Key::Render ( )
{
    if ( !Inventory::Key )
    {
        if ( m_y_pos > -m_dst_rectangle.h - 5 && m_x_pos > -m_dst_rectangle.w - 5
             && m_y_pos < Game::m_window_y + 5 && m_x_pos < Game::m_window_x + 5 )
        {
            m_texture->NextFrame ( );
            m_texture->Draw ( m_dst_rectangle );
        }
    }
    
}

bool Key::operator < ( const Entity &entity ) const
{
    return m_y_pos < entity.Height ( );
}

bool Key::operator > ( const Entity &entity ) const
{
    return m_y_pos > entity.Height ( );
}

int Key::Height ( ) const
{
    return m_y_pos;
}

int Key::Width ( ) const
{
    return m_x_pos;
}

int Key::Size ( ) const
{
    return m_size;
}

bool Key::ProximityAction ( Entity *entity )
{
    if ( DamageStatus ( ) == entity->DamageStatus ( ) )
        return true;
    
    auto vec = Entity::Distance ( this, entity );
    int distance = ( int ) sqrt ( pow ( vec.first, 2 ) + pow ( vec.second, 2 ) );
    if ( distance < ( m_size / 3 ) * 2 )
    {
        Inventory::Key = 1;
        return false;
    }
    
    return true;
}

int Key::DamageStatus ( )
{
    return 1;
}

bool Key::IsFighting ( )
{
    return Entity::IsFighting ( );
}

void Key::DecreaseHealth ( int value )
{
    Entity::DecreaseHealth ( value );
}

void Key::DecreaseStamina ( int value )
{
    Entity::DecreaseStamina ( value );
}

bool Key::IsParying ( )
{
    return Entity::IsParying ( );
}
