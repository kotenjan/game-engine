//
// Created by jan on 08.05.20.
//

#pragma once
#include "Element.h"
#include "list"

class Stats
{
public:
    
    Stats() = default;
    
    ~Stats();
    
    void Render ( );
    void Add ( Element *element );
    void Click ( int x, int y);

private:
    
    std::list<Element*> m_elements;
    
};
