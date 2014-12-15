//
//  Cell.cpp
//  cellSpread
//
//  Created by Minor, Steve on 12/12/14.
//
//

#include "Cell.h"

Virus::Cell::Cell(int _x, int _y): isActive(false), position(Point(_x,_y)){};

void Virus::Cell::flip(){
    isActive = !isActive;
};

void Virus::Cell::setState(bool state){
    isActive = state;
};

void Virus::Cell::calculateNeighbors(int gridWidth, int gridHeight){
    //calculate neighbors
    //    x , x, x,
    //    x , 0, x,
    //    x , x, x
    for(int row = position.y - 1; row <= position.y + 1; ++row){
        for(int column = position.x - 1; column <= position.x + 1; column++){
            if(row >= 0 && row < gridHeight  && column >= 0 && column < gridWidth && (row != position.y && column != position.x)){
                neighbors.push_back(Point(column, row));
            }
        }
    }
}

