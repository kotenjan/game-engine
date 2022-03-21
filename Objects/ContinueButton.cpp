//
// Created by jan on 09.05.20.
//

#include "ContinueButton.h"

ContinueButton::ContinueButton ( Texture *texture, int x, int y, int width, int height, bool visible, Texture *a,
                                 Texture *b, Player *player )
        : m_texture ( texture ), m_x_pos ( x ), m_y_pos ( y ), m_width ( width ), m_height ( height ),
          m_visible ( visible ), m_char_a ( b ), m_char_b ( a ), m_player(player)
{
    m_dst_rectangle.x = m_x_pos;
    m_dst_rectangle.y = m_y_pos;
    m_dst_rectangle.w = m_width;
    m_dst_rectangle.h = m_height;
}

bool ContinueButton::Click ( int x, int y )
{
    if ( x >= m_x_pos && x <= m_x_pos + m_width )
        if ( y >= m_y_pos && y <= m_y_pos + m_height )
        {
    
            std::ifstream f1 ( "../Graphics/Savefile/type.txt" );
            if ( f1.good ( ) )
            {
                std::string g;
                getline ( f1, g );
                f1.close ( );
                if ( g == "1" )
                    m_player->ReplaceTexture ( new Texture ( m_char_b ) );
                else
                    m_player->ReplaceTexture ( new Texture ( m_char_a ) );
            }
            else
                m_player->ReplaceTexture ( new Texture ( m_char_a ) );
            std::cout << "Click\n";
            Game::m_game_running = true;
            Game::m_menu_running = false;
            Game::m_running = true;
            Game::new_game = false;
            return true;
        }
    return false;
}

void ContinueButton::Render ( )
{
    if ( m_visible )
        m_texture->Draw ( m_dst_rectangle );
}

void ContinueButton::Display ( )
{
    m_visible = true;
}

void ContinueButton::Hide ( )
{
    m_visible = false;
}

ContinueButton::~ContinueButton ( )
{
    delete m_texture;
    delete m_char_a;
    delete m_char_b;
}
