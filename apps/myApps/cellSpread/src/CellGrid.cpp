//
//  CellGrid.cpp
//  cellSpread
//
//  Created by Minor, Steve on 12/12/14.
//
//

#include "CellGrid.h"

namespace Virus{
    CellGrid::CellGrid():x(0),y(0),width(0), height(0), cellSize(0), isSpreading(true){};
    
    
    CellGrid::CellGrid(int _x, int _y, int _width, int _height, int _cellSize):x(_x),y(_y),width(_width), height(_height), cellSize(_cellSize), isSpreading(true){
        for(int row = 0; row < height; row++){
            for(int column = 0; column < width; ++column){
                cells.insert(std::pair<Point, Cell>(Point(column, row), Cell(column,row)));
            }
        }
        
        for(auto it = cells.begin(); it != cells.end();++it){
            it->second.calculateNeighbors(width, height);
        }
    };
    
    Cell CellGrid::getRandomCell(){
        int randX = int(ofRandom(0, float(getWidth())));
        int randY = int(ofRandom(0, float(getHeight())));
        
        return cells[Point(randX, randY)];
    };

    std::vector<Point> spread(){
        
    };
    
    int CellGrid::getX(){ return x;}
    int CellGrid::getY(){ return y;}
    int CellGrid::getWidth(){ return width;}
    int CellGrid::getHeight(){ return height;}
    int CellGrid::getCellSize(){ return cellSize;}
    
    std::ostream& operator << (std::ostream& os, const Virus::CellGrid& cellGrid){
        for(auto it = cellGrid.cells.begin(); it != cellGrid.cells.end();++it){
            os << it->second;
        }
        return os;
    }
}
