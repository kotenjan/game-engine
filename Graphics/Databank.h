//
// Created by jan on 23.04.20.
//

#pragma once

#include "Texture.h"

class Databank
{
public:
    
    explicit Databank ( SDL_Renderer *renderer );
    
    ~Databank ( );
    
    Texture *m_ground;
    Texture *m_wall;
    Texture *m_player;
    Texture *m_enemy1;
    Texture *m_enemy2;
    Texture *m_bar;
    Texture *m_key;
    Texture *m_health_bar;
    Texture *m_stamina_bar;
    Texture *m_end_game;
    Texture *m_continue;
    Texture *m_new_game;
    Texture *m_ok;
    Texture *m_nok;
    Texture *m_equipment;
    Texture *m_coin;
    std::string m_map;
    std::string m_enemies_txt;
    std::string m_map_txt;
    std::string m_player_txt;
    Texture *m_locked_tile;
    Texture *m_victory;
    Texture *m_game_over;
    Texture *m_lock;
    Texture *m_stat_a;
    Texture *m_stat_b;
    Texture *m_select_hero;
    Texture *m_gun_icon;
    Texture *m_sword_icon;
    
};
