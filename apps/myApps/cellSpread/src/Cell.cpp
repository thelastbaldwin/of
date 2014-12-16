//
//  Cell.cpp
//  cellSpread
//
//  Created by Minor, Steve on 12/12/14.
//
//

#include "Cell.h"

namespace Virus{

    Cell::Cell(int _x, int _y): isActive(false), position(Point(_x,_y)){};

    void Cell::flip(){
        isActive = !isActive;
    };

    void Cell::setState(bool state){
        isActive = state;
    };

    void Cell::calculateNeighbors(int gridWidth, int gridHeight){
        //calculate neighbors
        //    x , x, x,
        //    x , 0, x,
        //    x , x, x
        for(int row = position.y - 1; row <= position.y + 1; ++row){
            for(int column = position.x - 1; column <= position.x + 1; ++column){
                    neighbors.push_back(Point(column, row));
            }
        }
    }

    std::ostream& operator << (std::ostream& os, const Virus::Cell& cell){
        os << "Location: " << cell.position.x << ", " << cell.position.y <<
        "\nNeighbors[" << cell.neighbors.size() << "]: " << std::endl;
        
        for(auto it = cell.neighbors.begin(); it != cell.neighbors.end(); ++it){
            if(it != cell.neighbors.begin()){
                os << ", ";
            }
            os << "(" << cell.position.x << ", " << cell.position.y << ")";
        }
        os << "\n";
        return os;
    };
}

