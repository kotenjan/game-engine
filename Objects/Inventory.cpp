//
// Created by jan on 09.05.20.
//

#include "Inventory.h"

int Inventory::Key = 0;
int Inventory::Gun = 0;
int Inventory::Sword = 0;

Inventory::Inventory ( Texture *texture, Texture *valid, Texture *invalid, int x, int y, int width, int height,
                       bool visible )
        : m_texture ( texture ), m_valid ( valid ), m_invalid ( invalid ), m_x_pos ( x ), m_y_pos ( y ),
          m_width ( width ), m_height ( height ), m_visible ( visible )
{
    m_dst_rectangle.x = m_x_pos;
    m_dst_rectangle.y = m_y_pos;
    m_dst_rectangle.w = m_width;
    m_dst_rectangle.h = m_height;
}

bool Inventory::Click ( int x, int y )
{
    return false;
}

void Inventory::Render ( )
{
    if ( m_visible )
    {
        int placement = m_width / 6 - m_valid->Width ( ) / 2;
        
        if ( Inventory::Key )
            m_valid->Draw ( { m_x_pos + placement, m_y_pos + m_height / 2, m_valid->Width ( ), m_valid->Height ( ) } );
        else
            m_invalid->Draw (
                    { m_x_pos + placement, m_y_pos + m_height / 2, m_invalid->Width ( ), m_invalid->Height ( ) } );
        
        placement += m_width / 3;
    
        if ( Inventory::Sword )
            m_valid->Draw ( { m_x_pos + placement, m_y_pos + m_height / 2, m_valid->Width ( ), m_valid->Height ( ) } );
        else
            m_invalid->Draw (
                    { m_x_pos + placement, m_y_pos + m_height / 2, m_invalid->Width ( ), m_invalid->Height ( ) } );
        
        placement += m_width / 3;
    
        if ( Inventory::Gun )
            m_valid->Draw ( { m_x_pos + placement, m_y_pos + m_height / 2, m_valid->Width ( ), m_valid->Height ( ) } );
        else
            m_invalid->Draw (
                    { m_x_pos + placement, m_y_pos + m_height / 2, m_invalid->Width ( ), m_invalid->Height ( ) } );
        
        m_texture->Draw ( m_dst_rectangle );
    }
}

void Inventory::Display ( )
{
    m_visible = true;
}

void Inventory::Hide ( )
{
    m_visible = false;
}

Inventory::~Inventory ( )
{
    delete m_texture;
    delete m_valid;
    delete m_invalid;
}
