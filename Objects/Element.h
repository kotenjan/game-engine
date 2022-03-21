//
// Created by jan on 07.05.20.
//

#pragma once

#include "../Graphics/Texture.h"

class Element
{

public:
    
    virtual ~Element ( );
    
    virtual bool Click ( int x, int y );
    virtual void Render ( );
    virtual void Display ( );
    virtual void Hide ( );
    
};
