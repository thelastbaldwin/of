//
//  Cell.h
//  cellSpread
//
//  Created by Minor, Steve on 12/12/14.
//
//

#pragma once

#include <vector>
//can't use ofPoint.h because of issues with map

//forward declaration
namespace Virus{
    class CellGrid;
}

namespace Virus{
    struct Point{
        Point(int _x, int _y):x(_x),y(_y){};
        int x, y;
        
        bool operator < (const Virus::Point& rhs) const{
            if(this->y < rhs.y){
                return true;
            }else if(this->y == rhs.y && this->x < rhs.x){
                return true;
            }
            return false;
        };
        
    };
    
    class Cell{
        friend class CellGrid;
    public:
        Cell(int _x, int _y);
        void flip();
        void setState(bool state);
        void calculateNeighbors(int gridWidth, int gridHeight);
        
    private:
        Point position;
        bool isActive;
        std::vector<Point> neighbors;
    };

}
