//
// Created by jan on 08.05.20.
//

#include "Stats.h"

void Stats::Render ( )
{
    for ( auto element : m_elements )
    {
        element->Render ( );
    }
}

void Stats::Add ( Element *element )
{
    m_elements.emplace_back ( element );
}

void Stats::Click ( int x, int y )
{
    for ( auto &element : m_elements )
        element->Click ( x, y );
}

Stats::~Stats ( )
{
    for ( auto &a : m_elements )
        delete a;
}
