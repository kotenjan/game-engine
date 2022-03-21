//
// Created by jan on 15.06.20.
//

#include "Controller.h"
#include "Game.h"

void Controller::Run ( int width, int height, unsigned frame_start, unsigned frame_time, uint8_t framerate,
                       uint8_t delay )
{
    Game *game = new Game ( );
    Game::m_running = true;
    Game::m_menu_running = true;
    Game::m_game_running = false;
    
    game->InitWindow ( "RPG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, false );
    
    while ( Game::m_running )
    {
        game->InitMenu ( width, height );
        while ( Game::m_menu_running )
        {
            frame_start = SDL_GetTicks ( );
            
            game->HandleMenuEvents ( );
            game->UpdateMenu ( );
            game->RenderMenu ( );
            
            frame_time = SDL_GetTicks ( ) - frame_start;
            
            if ( delay > frame_time )
                SDL_Delay ( delay - frame_time );
        }
        game->InitGame ( width, height );
        while ( Game::m_game_running )
        {
            frame_start = SDL_GetTicks ( );
            
            game->HandleGameEvents ( );
            game->Update ( );
            game->Render ( );
            
            frame_time = SDL_GetTicks ( ) - frame_start;
            
            if ( delay > frame_time )
                SDL_Delay ( delay - frame_time );
        }
        std::cout << "LOOP BROKE" << std::endl;
        game->CleanAfterLoop ( );
    }
    
    game->Clean ( );
    delete game;
}
