//
//  CellGrid.h
//  cellSpread
//
//  Created by Minor, Steve on 12/12/14.
//
//

#pragma once
#include <vector>
#include <Cell.h>

class CellGrid{
public:
    CellGrid(int _x, int _y, int _width, int _height, int _cellSize);
    
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    
private:
    int x, y, width, height, cellSize;
    std::vector< std::vector<Cell> > Cells;
};