//
//  CellDisplay.h
//  cellSpread
//
//  Created by Minor, Steve on 12/17/14.
//
//

#pragma once
#include "ofMain.h"
#include <map>
#include "Cell.h"

namespace Virus{
    class CellDisplay{
        public:
        CellDisplay();
        CellDisplay(int _x, int _y, int _width, int _height, int _cellSize, ofImage* _tile);
        
        void draw(std::map<Point, Cell>::const_iterator begin, std::map<Point, Cell>::const_iterator end) const;
        
        private:
            int x, y, width, height, cellSize;
            ofImage* tile;
    };
}
