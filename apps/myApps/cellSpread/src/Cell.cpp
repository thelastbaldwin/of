//
//  Cell.cpp
//  cellSpread
//
//  Created by Minor, Steve on 12/12/14.
//
//

#include "Cell.h"

namespace Virus{

    Cell::Cell(): bActive(false), position(Point(0, 0)){};
    Cell::Cell(int _x, int _y): bActive(false), position(Point(_x,_y)){};

    void Cell::flip(){
        bActive = !bActive;
    };

    void Cell::setState(bool state){
        bActive = state;
    };

    void Cell::calculateNeighbors(int gridWidth, int gridHeight){
        //calculate neighbors
        //    x , x, x,
        //    x , 0, x,
        //    x , x, x
        for(int row = position.y - 1; row <= position.y + 1; ++row){
            for(int column = position.x - 1; column <= position.x + 1; ++column){
                if(!(column < 0) && !(row < 0) && column < gridWidth && row < gridHeight && !(position.x == column && position.y == row)){
                    Point p(column, row);
                    neighbors.push_back(p);
                }
            }
        }
    }
    
    bool Cell::isActive() const{
        return bActive;
    }
    
    std::ostream& operator << (std::ostream& os, const Point& p){
        os << p.x << ", " << p.y;
        return os;
    };

    std::ostream& operator << (std::ostream& os, const Virus::Cell& cell){
        os << "Location: " << cell.position.x << ", " << cell.position.y <<
        "\nNeighbors[" << cell.neighbors.size() << "]: " << std::endl;
        
        for(auto it = cell.neighbors.begin(); it != cell.neighbors.end(); ++it){
            if(it != cell.neighbors.begin()){
                os << ", ";
            }
            os << "(" << *it << ")";
        }
        os << "\n";
        return os;
    };
}

