//
//  Cell.cpp
//  cellSpread
//
//  Created by Minor, Steve on 12/12/14.
//
//

#include "Cell.h"

Cell::Cell(int _x, int _y, CellGrid* parent):x(_x), y(_y), isActive(false){
    //calculate neighbors
}

void Cell::flip(){
    isActive = !isActive;
}

