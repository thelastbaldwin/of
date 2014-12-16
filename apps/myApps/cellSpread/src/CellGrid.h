//
//  CellGrid.h
//  cellSpread
//
//  Created by Minor, Steve on 12/12/14.
//
//

#pragma once
#include <map>
#include "Cell.h"

namespace Virus{
    class CellGrid{
    public:
        CellGrid();
        CellGrid(int _x, int _y, int _width, int _height, int _cellSize);
        
        int getX();
        int getY();
        int getWidth();
        int getHeight();
        
        friend std::ostream& operator << (std::ostream& os, const Virus::CellGrid& cellGrid);
        
    private:
        int x, y, width, height, cellSize;
        std::map<Point, Cell> cells;
    };
}
