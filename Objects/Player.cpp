//
// Created by jan on 03.05.20.
//

#include "Player.h"
#include "../Init/Game.h"

int Player::stamina = 100;
int Player::health = 100;
bool Player::fencing = false;
bool Player::protecting = false;

Player::Player ( int x, int y, int size, int speed, Map *map )
        : m_x_pos ( x ),
          m_y_pos ( y ),
          m_size ( size ),
          m_map ( map ),
          m_recharging ( false )
{
    m_dst_rectangle.w = m_size;
    m_dst_rectangle.h = m_size;
    m_dst_rectangle.x = m_x_pos;
    m_dst_rectangle.y = m_y_pos;
    Player::stamina = 100;
    Player::health = 50;
    Player::fencing = false;
    Player::protecting = false;
}

Player::~Player ( )
{
    delete m_texture;
}

void Player::Update ( int x, int y )
{
    //todo: implement stamina decreases
    if ( m_recharging )
    {
        x = ( x > 0 ) - ( x < 0 );
        y = ( y > 0 ) - ( y < 0 );
    }
    
    else if ( x * x > 1 || y * y > 1 )
        Player::stamina -= 3;
    Player::stamina = Player::stamina < 0 ? 0 : Player::stamina;
    if ( Player::stamina <= 0 )
        m_recharging = true;
    if ( Player::stamina >= 50 )
        m_recharging = false;
    
    
    m_x_pos += x;
    m_y_pos += y;
    
    m_dst_rectangle.x = m_x_pos;
    m_dst_rectangle.y = m_y_pos;
}

void Player::Render ( )
{
    if ( Player::health < 1 )
    {
        Game::m_menu_running = true;
        Game::m_game_running = false;
        Game::m_game_result = -1;
    
        std::ofstream myfile;
        myfile.open ( "../Graphics/Savefile/result.txt" );
        myfile << "1";
        myfile.close ( );
    }
    
    Player::stamina = Player::stamina > 100 ? 100 : Player::stamina + 1;
    m_texture->NextFrame ( );
    m_texture->Draw ( m_dst_rectangle );
}

bool Player::operator < ( const Entity &entity ) const
{
    return m_y_pos < entity.Height ( );
}

bool Player::operator > ( const Entity &entity ) const
{
    return m_y_pos > entity.Height ( );
}

int Player::Height ( ) const
{
    return m_y_pos;
}

int Player::Width ( ) const
{
    return m_x_pos;
}

int Player::Size ( ) const
{
    return m_size;
}

void Player::UpdateMovement ( int animation )
{
    m_texture->SetFrame ( 0, animation );
}

bool Player::ProximityAction ( Entity *entity )
{
    if ( 1 != entity->DamageStatus ( ) )
        return true;
    
    auto vec = Entity::Distance ( this, entity );
    int distance = ( int ) sqrt ( pow ( vec.first, 2 ) + pow ( vec.second, 2 ) );
    if ( entity->DamageStatus ( ) == -1 )
        return distance >= m_size / 2;
    
    if ( distance < m_size / 2 && Player::fencing )
        entity->DecreaseHealth ( 1 );
    
    return true;
}

int Player::DamageStatus ( )
{
    return 0;
}

bool Player::ProximityAction ( int distance )
{
    return distance >= m_size / 2;
}

bool Player::ProximityAction ( )
{
    // todo: animation with tile
    return true;
}

bool Player::IsFighting ( )
{
    return Player::fencing;
}

void Player::DecreaseHealth ( int value )
{
    Player::health -= value;
    Player::health = Player::health < 0 ? 0 : Player::health;
}

void Player::DecreaseStamina ( int value )
{
    Player::stamina -= value;
    Player::stamina = Player::stamina < 0 ? 0 : Player::stamina;
}

bool Player::IsParying ( )
{
    return Player::protecting;
}

void Player::SetPosition ( int x, int y )
{
    m_x_pos = x;
    m_y_pos = y;
    
    m_dst_rectangle.x = m_x_pos;
    m_dst_rectangle.y = m_y_pos;
}

void Player::ReplaceTexture ( Texture *texture )
{
    //delete m_texture;
    m_texture = texture;
}

void Player::DecreaseStamina ( int &x, int &y )
{
    if ( m_recharging )
    {
        x = ( x > 0 ) - ( x < 0 );
        y = ( y > 0 ) - ( y < 0 );
    }
    
    else if ( x * x > 1 || y * y > 1 )
        Player::stamina -= 3;
    Player::stamina = Player::stamina < 0 ? 0 : Player::stamina;
    if ( Player::stamina <= 0 )
        m_recharging = true;
    if ( Player::stamina >= 50 )
        m_recharging = false;
}
