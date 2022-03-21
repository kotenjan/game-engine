//
// Created by jan on 22.04.20.
//

#include "Map.h"
#include "UnlockedTile.h"

Map::Map ( Databank *databank, int tile_size, int width, int height, Objects *objects )
        : m_x_pos ( 0 ), m_y_pos ( 0 ), m_tile_size ( tile_size ), m_screen_size_x ( width ),
          m_screen_size_y ( height ), m_databank ( databank ), m_objects ( objects )
{
    char ch;
    int x = 0;
    int y = 0;
    std::fstream fin ( databank->m_map, std::fstream::in );
    while ( fin >> std::noskipws >> ch )
    {
        switch ( ch )
        {
            case '#':
                m_tiles.emplace_back (
                        new Tile ( new Texture ( databank->m_wall ),
                                   SDL_Rect { x * tile_size, y * tile_size, tile_size, tile_size }, false ) );
                ++x;
                break;
            case 'H':
                m_tiles.emplace_back ( new UnlockedTile ( new Texture ( databank->m_locked_tile ),
                                                          SDL_Rect { x * tile_size, y * tile_size, tile_size,
                                                                     tile_size }, false ) );
                ++x;
                break;
            case '\n':
                m_length = x;
                x = 0;
                ++y;
                break;
            default:
                if ( ch == 'K' )
                {
                    m_key = new Key ( new Texture ( databank->m_key ), x * tile_size + tile_size / 2,
                                         y * tile_size + tile_size / 2,
                                         64 );
                    objects->Add ( m_key );
                }
                
                m_tiles.emplace_back (
                        new Tile ( new Texture ( databank->m_ground ),
                                   SDL_Rect { x * tile_size, y * tile_size, tile_size, tile_size } ) );
                ++x;
        }
    }
    m_height = y;
    std::cout << "MAP HEIGHT: " << m_height << " MAP LENGTH: " << m_length << std::endl;
    
    
}

Map::~Map ( )
{
    std::ofstream myfile;
    myfile.open ( m_databank->m_map_txt );
    myfile << m_x_pos << std::endl << m_y_pos;
    myfile.close ( );
    
    for ( auto &a : m_tiles )
        delete a;
}

void Map::Render ( )
{
    for ( auto &tile : m_tiles )
        tile->Draw ( m_x_pos, m_y_pos );
}

bool Map::IsAccessible ( int x, int y, int size )
{
    x -= m_x_pos;
    y -= m_y_pos;
    
    int width_top = x / m_tile_size;
    int height_top = y / m_tile_size;
    int width_btm = ( x + size ) / m_tile_size;
    int height_btm = ( y + size ) / m_tile_size;
    
    if ( width_top < 0 || height_top < 0 || width_top >= m_length || height_top >= m_height )
        return false;
    
    return GetTile ( width_top, height_top )->IsAccessible ( )
           && GetTile ( width_btm, height_btm )->IsAccessible ( )
           && GetTile ( width_top, height_btm )->IsAccessible ( )
           && GetTile ( width_btm, height_top )->IsAccessible ( );
}

Tile *Map::GetTile ( int x, int y )
{
    return m_tiles[y * m_length + x];
}

void Map::Update ( int x, int y )
{
    m_x_pos -= x;
    m_y_pos -= y;
}

SDL_Rect Map::GetRandomAccessible ( )
{
    int v1 = rand ( ) % m_tiles.size ( );
    while ( !m_tiles[v1]->IsAccessible ( ) )
        v1 = rand ( ) % m_tiles.size ( );
    SDL_Rect r = m_tiles[v1]->GetPosition ( ).Get ( );
    r.y += m_y_pos;
    r.x += m_x_pos;
    return r;
}

int Map::GetFreeTiles ( )
{
    int count = 0;
    for ( auto &a : m_tiles )
        if ( a->IsAccessible ( ) )
            count++;
    return count;
}

void Map::SetPosition ( int x, int y )
{
    m_y_pos = y;
    m_x_pos = x;
    
    m_key->Update(x, y);
}
