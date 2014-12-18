//
//  CellGrid.h
//  cellSpread
//
//  Created by Minor, Steve on 12/12/14.
//
//

#pragma once
#include <map>
#include <algorithm>
#include "ofMain.h"
#include "Cell.h"
#include "CellDisplay.h"

namespace Virus{
   
    class CellGrid{
    public:
        CellGrid();
        CellGrid(int _x, int _y, int _width, int _height, int _cellSize, ofImage* tile);
        
        Cell getRandomCell();
        
        //draws the grid, calling CellDisplay.draw
        void draw();
        
        //return the latest additions to the spread
        void spread();
        friend std::ostream& operator << (std::ostream& os, const Virus::CellGrid& cellGrid);
        
    private:
        int width, height;
        CellDisplay cellDisplay;
        bool isSpreading;
        std::map<Point, Cell> cells;
        std::vector<Point> activeSet;
    };
    
    bool isActiveCell(const Point p);
}
