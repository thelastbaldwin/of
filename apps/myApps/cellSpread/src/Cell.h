//
//  Cell.h
//  cellSpread
//
//  Created by Minor, Steve on 12/12/14.
//
//

#pragma once

#include <vector>
#include "CellGrid.h"

class Cell{
public:
    Cell(int _x, int _y, CellGrid* parent);
    void flip();
    
private:
    int x;
    int y;
    bool isActive;
    //vector of pointers to cell. This will allow direct operations on neighbors
    std::vector<Cell*> neighbors;
};
