//
//  CellDisplay.cpp
//  cellSpread
//
//  Created by Minor, Steve on 12/17/14.
//
//

#include "CellDisplay.h"

namespace Virus{
    CellDisplay::CellDisplay():x(0), y(0), height(0), cellSize(0),tile(NULL){};
    
    CellDisplay::CellDisplay(int _x, int _y, int _width, int _height, int _cellSize, ofImage* _tile):
    x(_x), y(_y), width(_width),height(_height), cellSize(_cellSize), tile(_tile){
        tile->resize(cellSize, cellSize);
    };
    
    void CellDisplay::draw(std::map<Point, Cell>::const_iterator begin, std::map<Point, Cell>::const_iterator end) const{
        for(auto it = begin; it != end; ++it){
            if(it->second.isActive()){
                tile->draw(x + it->first.x * cellSize,y + it->first.y * cellSize);
            }
        }
    }
}