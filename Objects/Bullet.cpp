//
// Created by jan on 03.05.20.
//
#include "Bullet.h"

Bullet::Bullet ( Texture *texture, int x, int y, int size, Map *map, int dir_x, int dir_y )
        : m_texture ( texture ),
          m_x_pos ( x ),
          m_y_pos ( y ),
          m_size ( size ),
          m_speed ( 1 ),
          m_steps ( 0 ),
          m_map ( map ),
          m_health ( 20 )
{
    m_x_dir = ( dir_x * 4 ) % 5;
    m_y_dir = ( dir_y * 4 ) % 5;
    m_texture->SetFrame ( 0, 0 );
    m_dst_rectangle.x = m_x_pos;
    m_dst_rectangle.y = m_y_pos;
    m_dst_rectangle.w = m_size;
    m_dst_rectangle.h = m_size;
}

Bullet::~Bullet ( )
{
    delete m_texture;
}

void Bullet::Update ( int x, int y )
{
    m_x_pos += x + m_x_dir;
    m_y_pos += y + m_y_dir;
    
    m_dst_rectangle.x = m_x_pos;
    m_dst_rectangle.y = m_y_pos;
}

void Bullet::Render ( )
{
    m_texture->NextFrame ( );
    m_texture->Draw ( m_dst_rectangle );
}

bool Bullet::operator < ( const Entity &entity ) const
{
    return m_y_pos < entity.Height ( );
}

bool Bullet::operator > ( const Entity &entity ) const
{
    return m_y_pos > entity.Height ( );
}

int Bullet::Height ( ) const
{
    return m_y_pos;
}

int Bullet::Width ( ) const
{
    return m_x_pos;
}

int Bullet::Size ( ) const
{
    return m_size;
}

bool Bullet::ProximityAction ( Entity *entity )
{
    if ( !( m_y_pos > -m_dst_rectangle.h - 5 && m_x_pos > -m_dst_rectangle.w - 5
            && m_y_pos < Game::m_window_y + 5 && m_x_pos < Game::m_window_x + 5 ) )
        return false;
    
    if ( DamageStatus ( ) != entity->DamageStatus ( ) )
        return true;
    
    auto vec = Entity::Distance ( this, entity );
    int distance = ( int ) sqrt ( pow ( vec.first + 64, 2 ) + pow ( vec.second + 47, 2 ) );
    if ( distance < m_size * 2 )
    {
        entity->DecreaseHealth ( 500 );
        //return false; //uncomment for one kill per shot only
    }
    
    return true;
}

int Bullet::DamageStatus ( )
{
    return 1;
}

bool Bullet::IsFighting ( )
{
    return m_sequence < 2;
}

void Bullet::DecreaseHealth ( int value )
{
    m_health -= value;
}

bool Bullet::IsParying ( )
{
    return false;
}

void Bullet::DecreaseStamina ( int value )
{

}