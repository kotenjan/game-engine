//
// Created by jan on 21.04.20.
//

#include "Game.h"
#include "../Objects/Heart.h"
#include "../Objects/Bullet.h"
#include "../Objects/PlayerIcon.h"
#include "../Objects/TextBox.h"

bool Game::m_game_running = false;
bool Game::m_menu_running = true;
bool Game::m_running = false;
bool Game::new_game = false;
int Game::m_window_y = 0;
int Game::m_window_x = 0;
int Game::m_gun_amount = 10;
int Game::m_sword_amount = 20;
int Game::m_speed = 2;
int Game::m_game_result = 0;

Game::Game ( )
{
}

Game::~Game ( )
{

}

bool Game::InitWindow ( const char *title, int xpos, int ypos, int width, int height, bool fullscreen )
{
    m_count = 0;
    int flags = 0;
    Game::m_window_x = width;
    Game::m_window_y = height;
    
    if ( fullscreen )
        flags = SDL_WINDOW_FULLSCREEN;
    
    if ( SDL_Init ( SDL_INIT_EVERYTHING ) < 0 )
        return PrintError ( "SDL could not initialize!" );
    else
    {
        m_window = SDL_CreateWindow ( title, xpos, ypos, width, height, flags );
        if ( !m_window )
            return PrintError ( "Window not created!" );
        
        m_renderer = SDL_CreateRenderer ( m_window, -1, 0 );
        if ( !m_renderer )
            return PrintError ( "Renderer not created!" );
        else
        {
            SDL_SetRenderDrawColor ( m_renderer, 70, 70, 70, 0 );
        }
    }
    
    return true;
}


void Game::InitMenu ( int width, int height )
{
    m_databank = new Databank ( m_renderer );
    m_objects = new Objects ( m_databank );
    m_map = new Map ( m_databank, 256, width, height, m_objects );
    auto a = m_map->GetRandomAccessible ( );
    m_player = new Player ( a.x, a.y, 64, 1, m_map );
    while ( !Centered ( ) )
    {
        a = m_map->GetRandomAccessible ( );
        m_player->SetPosition ( a.x, a.y );
    }
    m_stats = new Stats ( );
    
    m_menu_stats = new Stats ( );
    m_victory_bar = new TextBox ( new Texture ( m_databank->m_victory ), width / 2 - 256, height / 2 - 356, 512, 64,
                                  Game::m_game_result == 1 );
    m_game_over_bar = new TextBox ( new Texture ( m_databank->m_game_over ), width / 2 - 256, height / 2 - 356, 512, 64,
                                    Game::m_game_result == -1 );
    m_menu_stats->Add ( m_victory_bar );
    m_menu_stats->Add ( m_game_over_bar );
    m_menu_stats->Add ( new PlayerIcon ( new Texture ( m_databank->m_player ),
                                         width / 2 - 128, height / 2 - 192, 128, 128,
                                         true, m_player, 10, 10, 2, 0 ) );
    m_menu_stats->Add ( new PlayerIcon ( new Texture ( m_databank->m_enemy1 ),
                                         width / 2, height / 2 - 192, 128, 128,
                                         true, m_player, 10, 5, 3, 1 ) );
    m_menu_stats->Add ( new ContinueButton ( new Texture ( m_databank->m_continue ),
                                             width / 2 - 256, height / 2 + 32, 512, 64,
                                             true, new Texture ( m_databank->m_enemy1 ),
                                             new Texture ( m_databank->m_player ), m_player ) );
    m_menu_stats->Add (
            new TextBox ( new Texture ( m_databank->m_stat_a ),
                          width / 2 - 256,
                          height / 2 - 172,
                          128,
                          128,
                          true ) );
    m_menu_stats->Add (
            new TextBox ( new Texture ( m_databank->m_stat_b ),
                          width / 2 + 128,
                          height / 2 - 172,
                          128,
                          128,
                          true ) );
    m_menu_stats->Add (
            new TextBox ( new Texture ( m_databank->m_select_hero ),
                          width / 2 - 128,
                          height / 2 - 192 - 32,
                          256,
                          32,
                          true ) );
}

void Game::InitGame ( int width, int height )
{
    m_x = 0;
    m_y = 0;
    
    std::ifstream f1 ( "../Graphics/Savefile/result.txt" );
    if ( f1.good ( ) )
    {
        std::string g;
        getline ( f1, g );
        f1.close ( );
        if ( !Game::new_game )
            Game::new_game = g == "1";
    }
    
    std::ofstream myfile;
    myfile.open ( "../Graphics/Savefile/result.txt" );
    myfile << "0";
    myfile.close ( );
    
    if ( Game::new_game )
    {
        RandomEnemies ( );
    }
    else if ( PlayerFromFile ( ) )
    {
        MapFromFile ( );
        if ( !EnemiesFromFile ( ) )
            RandomEnemies ( );
    }
    else
    {
        m_player->ReplaceTexture ( new Texture ( m_databank->m_player ) );
        RandomEnemies ( );
    }
    m_objects->Add ( new Heart ( new Texture ( m_databank->m_health_bar ), 64, m_map ) );
    m_stats->Add ( new HealthBar ( new Texture ( m_databank->m_bar ), new Texture ( m_databank->m_health_bar ), 50,
                                   height - 20, 128, 16,
                                   true ) );
    m_stats->Add ( new StaminaBar ( new Texture ( m_databank->m_bar ), new Texture ( m_databank->m_stamina_bar ),
                                    width - 50 - 128, height - 20, 128, 16,
                                    true ) );
    m_stats->Add ( new Inventory ( new Texture ( m_databank->m_equipment ), new Texture ( m_databank->m_ok ),
                                   new Texture ( m_databank->m_nok ),
                                   width / 2 - m_databank->m_equipment->Width ( ) / 2, height - 68, 256, 64,
                                   true ) );
    Inventory::Key = m_owns_key;
    Inventory::Gun = Game::m_gun_amount;
    Inventory::Sword = Game::m_sword_amount;
}

void Game::Update ( )
{
    if ( !Player::fencing && !Player::protecting )
    {
        bool vertical =
                m_map->IsAccessible ( m_player->Width ( ), m_player->Height ( ) + m_y, m_player->Size ( ) ) && m_y != 0;
        bool horizontal =
                m_map->IsAccessible ( m_player->Width ( ) + m_x, m_player->Height ( ), m_player->Size ( ) ) && m_x != 0;
        if ( vertical || horizontal )
        {
            if ( !Centered ( ) )
            {
                int temp_x = m_x * horizontal;
                int temp_y = m_y * vertical;
                m_player->DecreaseStamina ( temp_x, temp_y );
                m_map->Update ( temp_x, temp_y );
                m_objects->Update ( m_player, temp_x, temp_y );
            }
            else
            {
                m_player->Update ( m_x * horizontal, m_y * vertical );
                m_objects->Update ( m_player );
            }
            m_player->UpdateMovement ( 1 );
        }
        else
        {
            m_player->UpdateMovement ( 0 );
            m_objects->Update ( m_player );
        }
    }
    else
    {
        m_objects->Update ( m_player );
    }
}

void Game::UpdateMenu ( )
{
    m_menu_stats->Click ( m_x_click, m_y_click );
    m_x_click = -1;
    m_y_click = -1;
}

void Game::Render ( )
{
    SDL_RenderClear ( m_renderer );
    m_map->Render ( );
    m_objects->Render ( m_player );
    m_stats->Render ( );
    SDL_RenderPresent ( m_renderer );
}

void Game::Clean ( )
{
    SDL_DestroyWindow ( m_window );
    SDL_DestroyRenderer ( m_renderer );
    SDL_Quit ( );
    std::cout << "Control Cleaned!" << std::endl;
}

void Game::HandleGameEvents ( )
{
    SDL_Event event;
    SDL_PollEvent ( &event );
    
    switch ( event.type )
    {
        case SDL_QUIT:
            EndGame ( );
            break;
        case SDL_KEYDOWN:
            KeyDown ( event );
            break;
        case SDL_KEYUP:
            KeyUp ( event );
            break;
        case SDL_MOUSEBUTTONDOWN:
            std::cout << event.button.x << " " << event.button.y << "\n";
        default:
            break;
    }
}

bool Game::PrintError ( const char *message )
{
    std::cerr << message << std::endl;
    Game::m_running = false;
    Game::m_game_running = false;
    Game::m_menu_running = false;
    return false;
}

bool Game::Centered ( )
{
    return ( !( m_player->Width ( ) + m_x <= Game::m_window_x / 5
                || m_player->Width ( ) + m_x >= Game::m_window_x - Game::m_window_x / 5
                || m_player->Height ( ) + m_y <= Game::m_window_y / 5
                || m_player->Height ( ) + m_y >= Game::m_window_y - Game::m_window_y / 5 ) );
}

void Game::RenderMenu ( )
{
    SDL_RenderClear ( m_renderer );
    m_menu_stats->Render ( );
    SDL_RenderPresent ( m_renderer );
}

void Game::HandleMenuEvents ( )
{
    SDL_Event event;
    SDL_PollEvent ( &event );
    
    switch ( event.type )
    {
        case SDL_QUIT:
            EndGame ( );
            break;
        case SDL_MOUSEBUTTONDOWN:
            m_x_click = event.button.x;
            m_y_click = event.button.y;
            break;
    }
}

bool Game::PlayerFromFile ( )
{
    std::ifstream myfile ( m_databank->m_player_txt );
    if ( myfile.good ( ) )
    {
        std::string w;
        std::string h;
        std::string health;
        std::string stamina;
        std::string key;
        getline ( myfile, w );
        getline ( myfile, h );
        getline ( myfile, health );
        getline ( myfile, stamina );
        getline ( myfile, key );
        if ( std::stoi ( health ) <= 0 )
        {
            return false;
        }
        getline ( myfile, stamina );
        myfile.close ( );
        m_player->SetPosition ( std::stoi ( w ), std::stoi ( h ) );
        Player::health = std::stoi ( health );
        Player::stamina = std::stoi ( stamina );
        m_owns_key = std::stoi ( key );
    }
    return true;
    
}

void Game::MapFromFile ( )
{
    std::ifstream myfile ( m_databank->m_map_txt );
    if ( myfile.good ( ) )
    {
        std::string w;
        std::string h;
        getline ( myfile, w );
        getline ( myfile, h );
        myfile.close ( );
        m_map->SetPosition ( std::stoi ( w ), std::stoi ( h ) );
    }
}

void Game::RandomEnemies ( )
{
    int tilecount = m_map->GetFreeTiles ( );
    for ( int i = 0; i < tilecount; ++i )
    {
        auto a = m_map->GetRandomAccessible ( );
        m_objects->Add ( new Pirate ( new Texture ( m_databank->m_enemy2 ),
                                      a.x + a.w / 2 + rand ( ) % 40 - rand ( ) % 20,
                                      a.y + a.h / 2 + rand ( ) % 40 - rand ( ) % 20,
                                      64,
                                      m_map, m_objects, m_databank ) );
    }
}

bool Game::EnemiesFromFile ( )
{
    std::string w;
    std::string h;
    std::ifstream myfile ( m_databank->m_enemies_txt );
    if ( myfile.is_open ( ) )
    {
        while ( getline ( myfile, w ) && getline ( myfile, h ) )
        {
            m_objects->Add ( new Pirate ( new Texture ( m_databank->m_enemy2 ),
                                          std::stoi ( w ),
                                          std::stoi ( h ),
                                          64,
                                          m_map, m_objects, m_databank ) );
        }
        myfile.close ( );
        return true;
    }
    return false;
}

void Game::CleanAfterLoop ( )
{
    std::ofstream myfile;
    myfile.open ( m_databank->m_player_txt );
    myfile << m_player->Width ( ) << std::endl
           << m_player->Height ( ) << std::endl
           << Player::health << std::endl
           << Player::stamina << std::endl
           << Inventory::Key;
    myfile.close ( );
    
    delete m_player;
    delete m_objects;
    delete m_stats;
    delete m_menu_stats;
    delete m_map;
    delete m_databank;
    m_owns_key = false;
    
}

void Game::EndGame ( )
{
    Game::m_running = false;
    Game::m_game_running = false;
    Game::m_menu_running = false;
}

void Game::SpeedUp ( )
{
    m_shift = true;
    if ( m_y == 1 || m_y == -1 || m_x == 1 || m_x == -1 )
    {
        m_x *= Game::m_speed;
        m_y *= Game::m_speed;
    }
}

void Game::Fight ( )
{
    if ( Inventory::Sword > 0 )
    {
        std::cout << Inventory::Sword << std::endl;
        if ( m_count != static_cast<int>(( SDL_GetTicks ( ) / 500 ) % 4) )
        {
            m_count = static_cast<int>(( SDL_GetTicks ( ) / 500 ) % 4);
            Inventory::Sword--;
        }
        Player::fencing = true;
        Player::protecting = false;
        m_player->UpdateMovement ( 2 );
    }
}

void Game::Protect ( )
{
    Player::protecting = true;
    Player::fencing = false;
    m_player->UpdateMovement ( 3 );
}

void Game::Shoot ( )
{
    if ( ( m_y || m_x ) && Inventory::Gun > 0 )
    {
        Player::protecting = false;
        Player::fencing = false;
        m_player->UpdateMovement ( 0 );
        m_objects->Add (
                new Bullet ( new Texture ( m_databank->m_coin ), m_player->Width ( ) + 32,
                             m_player->Height ( ) + 32,
                             16, m_map, m_x, m_y ) );
        Inventory::Gun--;
    }
}

void Game::KeyDown ( SDL_Event &event )
{
    switch ( event.key.keysym.sym )
    {
        case SDLK_a:
            m_x = m_shift ? -Game::m_speed : -1;
            break;
        case SDLK_d:
            m_x = m_shift ? Game::m_speed : 1;
            break;
        case SDLK_s:
            m_y = m_shift ? Game::m_speed : 1;
            break;
        case SDLK_w:
            m_y = m_shift ? -Game::m_speed : -1;
            break;
        case SDLK_k:
            SpeedUp ( );
            break;
        case SDLK_j:
            Fight ( );
            break;
        case SDLK_l:
            Protect ( );
            break;
        case SDLK_h:
            Shoot ( );
            break;
    }
}

void Game::SpeedDown ( )
{
    m_shift = false;
    m_x /= Game::m_speed;
    m_y /= Game::m_speed;
}

void Game::KeyUp ( SDL_Event &event )
{
    switch ( event.key.keysym.sym )
    {
        case SDLK_a:
            if ( m_x <= -1 )
                m_x = 0;
            break;
        case SDLK_d:
            if ( m_x >= 1 )
                m_x = 0;
            break;
        case SDLK_s:
            if ( m_y >= 1 )
                m_y = 0;
            break;
        case SDLK_w:
            if ( m_y <= -1 )
                m_y = 0;
            break;
        case SDLK_k:
            SpeedDown ( );
            break;
        case SDLK_j:
            Player::fencing = false;
            break;
        case SDLK_l:
            Player::protecting = false;
            break;
    }
}

