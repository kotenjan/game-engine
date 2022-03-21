//
// Created by jan on 04.06.20.
//

#include "Heart.h"
#include "../Init/Game.h"

Heart::Heart ( Texture *texture, int size, Map *map )
        : m_texture ( texture ),
          m_size ( size ),
          m_map ( map )
{
    SDL_Rect pos = m_map->GetRandomAccessible ( );
    m_x_pos = pos.x;
    m_y_pos = pos.y;
    m_texture->SetFrame ( 0, 0 );
    m_dst_rectangle.x = m_x_pos;
    m_dst_rectangle.y = m_y_pos;
    m_dst_rectangle.w = m_size;
    m_dst_rectangle.h = m_size;
}

Heart::~Heart ( )
{
    delete m_texture;
}

void Heart::Update ( int x, int y )
{
    m_x_pos += x;
    m_y_pos += y;
    
    m_dst_rectangle.x = m_x_pos;
    m_dst_rectangle.y = m_y_pos;
}

void Heart::Render ( )
{
    if ( m_y_pos > -m_dst_rectangle.h - 5 && m_x_pos > -m_dst_rectangle.w - 5
         && m_y_pos < Game::m_window_y + 5 && m_x_pos < Game::m_window_x + 5 )
    {
        m_texture->NextFrame ( );
        m_texture->Draw ( m_dst_rectangle );
    }
}

bool Heart::operator < ( const Entity &entity ) const
{
    return m_y_pos < entity.Height ( );
}

bool Heart::operator > ( const Entity &entity ) const
{
    return m_y_pos > entity.Height ( );
}

int Heart::Height ( ) const
{
    return m_y_pos;
}

int Heart::Width ( ) const
{
    return m_x_pos;
}

int Heart::Size ( ) const
{
    return m_size;
}

bool Heart::ProximityAction ( Entity *entity )
{
    if ( DamageStatus ( ) == entity->DamageStatus ( ) )
        return true;
    
    auto vec = Entity::Distance ( this, entity );
    int distance = ( int ) sqrt ( pow ( vec.first, 2 ) + pow ( vec.second, 2 ) );
    if ( distance < ( m_size / 3 ) * 2 )
    {
        Player::health += 50;
        SDL_Rect pos = m_map->GetRandomAccessible ( );
        m_x_pos = pos.x;
        m_y_pos = pos.y;
        std::cout << "HEART:" << m_x_pos << " " << m_y_pos << "\n";
    }
    
    return true;
}

int Heart::DamageStatus ( )
{
    return 1;
}

bool Heart::IsFighting ( )
{
    return Entity::IsFighting ( );
}

void Heart::DecreaseHealth ( int value )
{
    Entity::DecreaseHealth ( value );
}

void Heart::DecreaseStamina ( int value )
{
    Entity::DecreaseStamina ( value );
}

bool Heart::IsParying ( )
{
    return Entity::IsParying ( );
}
