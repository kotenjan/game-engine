//
// Created by jan on 21.04.20.
//
#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../Objects/Player.h"
#include "../Objects/Objects.h"
#include "../Graphics/Texture.h"
#include "../Objects/Map.h"
#include "../Graphics/Databank.h"
#include "../Objects/Entity.h"
#include "../Objects/Pirate.h"
#include "../Objects/Stats.h"
#include "../Objects/Stats.h"
#include "../Objects/HealthBar.h"
#include "../Objects/StaminaBar.h"
#include "../Objects/Inventory.h"
#include "../Objects/ContinueButton.h"

class Game
{
public:
    
    Game ( );
    
    ~Game ( );
    
    bool InitWindow ( const char *title, int xpos, int ypos, int width, int height, bool fullscreen );
    void InitGame ( int width, int height );
    void InitMenu ( int width, int height );
    void Update ( );
    void UpdateMenu ( );
    void Render ( );
    void RenderMenu ( );
    void Clean ( );
    void HandleGameEvents ( );
    void HandleMenuEvents ( );
    static bool PrintError ( const char *message );
    bool Centered ( );
    bool PlayerFromFile ( );
    void RandomEnemies ( );
    void MapFromFile ( );
    bool EnemiesFromFile ( );
    void CleanAfterLoop ( );
    void EndGame ( );
    void SpeedUp ( );
    void Fight ( );
    void Protect ( );
    void Shoot ( );
    void SpeedDown ( );
    void KeyDown ( SDL_Event &event );
    void KeyUp (SDL_Event &event);
    
    static bool m_game_running;
    static bool m_menu_running;
    static bool m_running;
    static bool new_game;
    static int m_window_x;
    static int m_window_y;
    static int m_gun_amount;
    static int m_sword_amount;
    static int m_speed;
    static int m_game_result;

private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    Player *m_player;
    Objects *m_objects;
    Stats *m_stats;
    Stats *m_menu_stats;
    Map *m_map;
    Databank *m_databank;
    int m_x;
    int m_y;
    int m_count;
    bool m_shift;
    int m_x_click;
    int m_y_click;
    bool m_owns_key;
    Element *m_victory_bar;
    Element *m_game_over_bar;
    
};
