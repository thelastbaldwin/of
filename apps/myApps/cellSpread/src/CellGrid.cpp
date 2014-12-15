//
//  CellGrid.cpp
//  cellSpread
//
//  Created by Minor, Steve on 12/12/14.
//
//

#include "CellGrid.h"

Virus::CellGrid::CellGrid(){}

Virus::CellGrid::CellGrid(int _x, int _y, int _width, int _height, int _cellSize):x(_x),y(_y),width(_width), height(_height), cellSize(_cellSize){
    for(int row = 0; row < height; row++){
        for(int column = 0; column < width; ++column){
            cells.insert(std::pair<Point, Cell>(Point(column, row), Cell(column,row)));
        }
    }
    
    for(auto it = cells.begin(); it != cells.end();++it){
        it->second.calculateNeighbors(width, height);
    }
};