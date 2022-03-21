//
// Created by jan on 22.04.20.
//

#include "UnlockedTile.h"
#include "../Init/Game.h"

UnlockedTile::UnlockedTile ( Texture *texture, SDL_Rect destination, bool accessible )
        : Tile(texture, destination, accessible)
{
}

bool UnlockedTile::IsAccessible ( )
{
    if (Inventory::Key){
        Game::m_game_result = 1;
        Game::m_game_running = false;
        Game::m_menu_running = true;
    
        std::ofstream myfile;
        myfile.open ( "../Graphics/Savefile/result.txt" );
        myfile << "1";
        myfile.close ( );
    }
    return Inventory::Key;
}

void UnlockedTile::Draw ( int x_pos, int y_pos )
{
    Tile::Draw ( x_pos, y_pos );
}

Position UnlockedTile::GetPosition ( )
{
    return Tile::GetPosition ( );
}
