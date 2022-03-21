//
// Created by jan on 23.04.20.
//

#include "Databank.h"

Databank::Databank ( SDL_Renderer *renderer )
        : m_ground ( new Texture ( "../Graphics/Images/green.png", renderer, 128, 128, 1, 1 ) ),
          m_wall ( new Texture ( "../Graphics/Images/brown.png", renderer, 128, 128, 1, 1 ) ),
          m_player ( new Texture ( "../Graphics/Images/player.png", renderer, 128, 128, 4, 4 ) ),
          m_enemy1 ( new Texture ( "../Graphics/Images/player2.png", renderer, 128, 96, 4, 3 ) ),
          m_enemy2 ( new Texture ( "../Graphics/Images/enemy1.png", renderer, 256, 96, 8, 3 ) ),
          m_bar ( new Texture ( "../Graphics/Images/bar.png", renderer, 128, 16, 1, 1 ) ),
          m_key ( new Texture ( "../Graphics/Images/key.png", renderer, 16, 16, 1, 1 ) ),
          m_health_bar ( new Texture ( "../Graphics/Images/health_bar.png", renderer, 6, 16, 1, 1 ) ),
          m_stamina_bar ( new Texture ( "../Graphics/Images/stamina_bar.png", renderer, 6, 16, 1, 1 ) ),
          m_new_game ( new Texture ( "../Graphics/Images/new_game.png", renderer, 64, 16, 1, 1 ) ),
          m_continue ( new Texture ( "../Graphics/Images/continue.png", renderer, 128, 32, 1, 1 ) ),
          m_end_game ( new Texture ( "../Graphics/Images/end_game.png", renderer, 64, 16, 1, 1 ) ),
          m_ok ( new Texture ( "../Graphics/Images/OK.png", renderer, 32, 32, 1, 1 ) ),
          m_nok ( new Texture ( "../Graphics/Images/NOK.png", renderer, 32, 32, 1, 1 ) ),
          m_equipment ( new Texture ( "../Graphics/Images/equipment.png", renderer, 256, 64, 1, 1 ) ),
          m_coin ( new Texture ( "../Graphics/Images/coin.png", renderer, 128, 16, 8, 1 ) ),
          m_map ( "../Graphics/Maps/map_1.txt" ),
          m_enemies_txt ( "../Graphics/Savefile/enemies.txt" ),
          m_map_txt ( "../Graphics/Savefile/map.txt" ),
          m_player_txt ( "../Graphics/Savefile/player.txt" ),
          m_locked_tile ( new Texture ( "../Graphics/Images/blue.png", renderer, 128, 128, 1, 1 ) ),
          m_victory ( new Texture ( "../Graphics/Images/victory.png", renderer, 128, 32, 1, 1 ) ),
          m_game_over ( new Texture ( "../Graphics/Images/game_over.png", renderer, 128, 32, 1, 1 ) ),
          m_lock ( new Texture ( "../Graphics/Images/lock.png", renderer, 110, 110, 1, 1 ) ),
          m_stat_a ( new Texture ( "../Graphics/Images/stats1.png", renderer, 64, 64, 1, 1 ) ),
          m_stat_b ( new Texture ( "../Graphics/Images/stats2.png", renderer, 64, 64, 1, 1 ) ),
          m_select_hero ( new Texture ( "../Graphics/Images/select_char_text.png", renderer, 128, 16, 1, 1 ) ),
          m_gun_icon ( new Texture ( "../Graphics/Images/gun_icon.png", renderer, 32, 32, 1, 1 ) ),
          m_sword_icon ( new Texture ( "../Graphics/Images/sword_icon.png", renderer, 32, 32, 1, 1 ) )
          
{
}

Databank::~Databank ( )
{
    delete m_ground;
    delete m_wall;
    delete m_player;
    delete m_enemy1;
    delete m_enemy2;
    delete m_bar;
    delete m_key;
    delete m_health_bar;
    delete m_stamina_bar;
    delete m_end_game;
    delete m_continue;
    delete m_new_game;
    delete m_ok;
    delete m_nok;
    delete m_equipment;
    delete m_coin;
    delete m_locked_tile;
    delete m_victory;
    delete m_game_over;
    delete m_lock;
    delete m_stat_a;
    delete m_stat_b;
    delete m_select_hero;
    delete m_sword_icon;
    delete m_gun_icon;
}
