//
// Created by jan on 02.05.20.
//

#include "Objects.h"
#include "Pirate.h"

void Objects::Update ( Entity *player, int x, int y )
{
    for ( auto entity : m_entities )
        entity->Update ( -x, -y );
    
    auto b = m_entities.begin ( );
    auto a = b++;
    auto e = m_entities.end ( );
    
    for ( auto ref_entity = m_entities.begin ( ); ref_entity != e; ref_entity++ )
    {
        for ( auto dst_entity = m_entities.begin ( ); dst_entity != e; dst_entity++ )
        {
            if ( *ref_entity != *dst_entity )
                if ( !( *ref_entity )->ProximityAction ( *dst_entity ) )
                {
                    if ( ref_entity != m_entities.begin ( ) )
                    {
                        auto temp_entity = ref_entity--;
                        m_entities.erase ( temp_entity );
                    }
                    else
                    {
                        m_entities.erase ( ref_entity );
                        ref_entity = m_entities.begin ( );
                    }
                }
        }
        if ( !( *ref_entity )->ProximityAction ( player ) )
        {
            if ( ref_entity != m_entities.begin ( ) )
            {
                auto temp_entity = ref_entity--;
                m_entities.erase ( temp_entity );
            }
            else
            {
                m_entities.erase ( ref_entity );
                ref_entity = m_entities.begin ( );
            }
        }
        player->ProximityAction ( *ref_entity );
    }
    
    b = m_entities.begin ( );
    a = b++;
    e = m_entities.end ( );
    
    while ( b != e )
    {
        if ( **a > **b )
            std::swap ( *a, *b );
        a++;
        b++;
    }
}

void Objects::Render ( Entity *player )
{
    auto it_s = m_entities.begin ( );
    auto it_e = m_entities.end ( );
    
    while ( it_s != it_e )
        if ( ( **it_s ) < ( *player ) )
            ( *it_s++ )->Render ( );
        else
            break;
    
    player->Render ( );
    
    while ( it_s != it_e )
        ( *it_s++ )->Render ( );
    
}

void Objects::Add ( Entity *entity )
{
    m_entities.emplace_back ( entity );
    
}

Objects::Objects ( Databank *databank )
        : m_databank ( databank )
{
}

Objects::~Objects ( )
{
    std::ofstream myfile;
    myfile.open ( m_databank->m_enemies_txt );
    
    for ( auto &a : m_entities )
        if ( dynamic_cast<Pirate *> (a) != NULL )
            myfile << a->Width ( ) << std::endl << a->Height ( ) << std::endl;
    myfile.close ( );
    
    for ( auto &a : m_entities )
        delete a;
}
