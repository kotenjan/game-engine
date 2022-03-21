//
// Created by jan on 09.05.20.
//

#include "ContinueButton.h"
#include "TextBox.h"


TextBox::TextBox ( Texture *texture, int x, int y, int width, int height, bool visible )
        : m_texture ( texture ), m_x_pos ( x ), m_y_pos ( y ), m_width ( width ), m_height ( height ),
          m_visible ( visible )
{
    m_dst_rectangle.x = m_x_pos;
    m_dst_rectangle.y = m_y_pos;
    m_dst_rectangle.w = m_width;
    m_dst_rectangle.h = m_height;
    m_texture->SetFrame(0, 0);
}

bool TextBox::Click ( int x, int y )
{
    return false;
}

void TextBox::Render ( )
{
    if ( m_visible )
        m_texture->Draw ( m_dst_rectangle );
}

void TextBox::Display ( )
{
    m_visible = true;
}

void TextBox::Hide ( )
{
    m_visible = false;
}

TextBox::~TextBox ( )
{
    delete m_texture;
}
