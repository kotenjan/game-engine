//
// Created by jan on 03.05.20.
//
#include "Pirate.h"

Pirate::Pirate ( Texture *texture, int x, int y, int size, Map *map, Objects *objects, Databank *databank )
        : m_texture ( texture ),
          m_x_pos ( x ),
          m_y_pos ( y ),
          m_size ( size ),
          m_x_dir ( 0 ),
          m_y_dir ( 0 ),
          m_speed ( 1 ),
          m_steps ( 0 ),
          m_map ( map ),
          m_health ( 20 ),
          m_objects ( objects ),
          m_databank ( databank )
{
    m_texture->SetFrame ( 0, 2 );
    m_dst_rectangle.x = m_x_pos;
    m_dst_rectangle.y = m_y_pos;
    m_dst_rectangle.w = m_size;
    m_dst_rectangle.h = m_size;
}

Pirate::~Pirate ( )
{
    delete m_texture;
}

void Pirate::Update ( int x, int y )
{
    m_x_pos += x;
    m_y_pos += y;
    
    m_dst_rectangle.x = m_x_pos;
    m_dst_rectangle.y = m_y_pos;
}

void Pirate::Render ( )
{
    if ( m_y_pos > -m_dst_rectangle.h - 5 && m_x_pos > -m_dst_rectangle.w - 5
         && m_y_pos < Game::m_window_y + 5 && m_x_pos < Game::m_window_x + 5 )
    {
        m_texture->NextFrame ( );
        m_texture->Draw ( m_dst_rectangle );
    }
}

bool Pirate::operator < ( const Entity &entity ) const
{
    return m_y_pos < entity.Height ( );
}

bool Pirate::operator > ( const Entity &entity ) const
{
    return m_y_pos > entity.Height ( );
}

int Pirate::Height ( ) const
{
    return m_y_pos;
}

int Pirate::Width ( ) const
{
    return m_x_pos;
}

int Pirate::Size ( ) const
{
    return m_size;
}

bool Pirate::ProximityAction ( Entity *entity )
{
    if ( DamageStatus ( ) == entity->DamageStatus ( ) )
        return true;
    if ( m_health <= 0 )
    {
        int r = rand ( ) % 12;
        if ( r == 5 )
        {
            m_objects->Add ( new Sword ( new Texture ( m_databank->m_sword_icon ), 32, m_x_pos, m_y_pos ) );
        }
        if ( r == 10 )
        {
            m_objects->Add ( new Gun ( new Texture ( m_databank->m_gun_icon ), 32, m_x_pos, m_y_pos ) );
        }
        
        return false;
    }
    
    auto vec = Entity::Distance ( this, entity );
    int distance = ( int ) sqrt ( pow ( vec.first, 2 ) + pow ( vec.second, 2 ) );
    if ( entity->DamageStatus ( ) == -1 )
        return distance >= m_size / 2;
    
    if ( distance < m_size / 2 )
    {
        m_texture->SetFrame ( 0, 2 );
        m_sequence = m_texture->NextFrame ( );
        if ( m_sequence > 1 )
            m_texture->SetFrame ( 0, 0 );
        else
        {
            if ( !entity->IsParying ( ) || Player::stamina < 10 )
                entity->DecreaseHealth ( 1 );
            else
                entity->DecreaseStamina ( 1 );
        }
        return true;
    }
    
    else if ( distance < m_size * 6 )
    {
        walk ( vec.first / abs ( vec.first ), vec.second / abs ( vec.second ) );
    }
    else
    {
        m_texture->SetFrame ( 0, 2 );
    }
    
    return true;
}

int Pirate::DamageStatus ( )
{
    return 1;
}

void Pirate::walk ( int b, int a )
{
    bool vertical =
            m_map->IsAccessible ( this->Width ( ), this->Height ( ) + b, this->Size ( ) ) && b != 0;
    bool horizontal =
            m_map->IsAccessible ( this->Width ( ) + a, this->Height ( ), this->Size ( ) ) && a != 0;
    if ( vertical || horizontal )
    {
        m_texture->SetFrame ( 0, 1 );
        Update ( a * horizontal, b * vertical );
    }
}

bool Pirate::ProximityAction ( int distance )
{
    return distance >= m_size / 2;
}

bool Pirate::ProximityAction ( )
{
    //todo: react to the ground
    return true;
}

bool Pirate::IsFighting ( )
{
    return m_sequence < 2;
}

void Pirate::DecreaseHealth ( int value )
{
    m_health -= value;
}

bool Pirate::IsParying ( )
{
    return false;
}

void Pirate::DecreaseStamina ( int value )
{

}