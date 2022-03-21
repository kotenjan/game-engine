//
// Created by jan on 09.05.20.
//

#include "PlayerIcon.h"

PlayerIcon::PlayerIcon ( Texture *texture, int x, int y, int width, int height, bool visible, Player *player, int sword,
                         int gun, int speed, int number )
        : m_texture ( texture ), m_x_pos ( x ), m_y_pos ( y ), m_width ( width ), m_height ( height ),
          m_visible ( visible ), m_player ( player ), m_sword ( sword ), m_gun ( gun ), m_speed ( speed ), m_number(number)
{
    m_dst_rectangle.x = m_x_pos;
    m_dst_rectangle.y = m_y_pos;
    m_dst_rectangle.w = m_width;
    m_dst_rectangle.h = m_height;
}

bool PlayerIcon::Click ( int x, int y )
{
    if ( x >= m_x_pos && x <= m_x_pos + m_width )
        if ( y >= m_y_pos && y <= m_y_pos + m_height )
        {
            std::ofstream myfile;
            myfile.open ( "../Graphics/Savefile/type.txt" );
            myfile << m_number;
            myfile.close ( );
            std::cout << "Click\n";
            m_player->ReplaceTexture ( new Texture ( m_texture ) );
            Game::new_game = true;
            Game::m_game_running = true;
            Game::m_menu_running = false;
            Game::m_running = true;
            Game::new_game = true;
            Game::m_sword_amount = m_sword;
            Game::m_speed = m_speed;
            Game::m_gun_amount = m_gun;
            return true;
        }
    return false;
}

PlayerIcon::~PlayerIcon ( )
{
    delete m_texture;
}

void PlayerIcon::Render ( )
{
    m_texture->NextFrame ( );
    if ( m_visible )
        m_texture->Draw ( m_dst_rectangle );
}

void PlayerIcon::Display ( )
{
    m_visible = true;
}

void PlayerIcon::Hide ( )
{
    m_visible = false;
}