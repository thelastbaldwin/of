//
//  Cell.h
//  cellSpread
//
//  Created by Minor, Steve on 12/12/14.
//
//

#pragma once

#include <vector>
#include <iostream>
//can't use ofPoint.h because of issues with map and < operator

namespace Virus{
    //forward declaration
    class CellGrid;
    
    //ofPoint doesn't have a < operation which is necessary for the cellGrid map
    struct Point{
        Point():x(0),y(0){};
        Point(int _x, int _y):x(_x),y(_y){};
        int x, y;
        
        bool operator == (const Point rhs) const{
            return this->x == rhs.x && this->y == rhs.y;
        };
        
        bool operator < (const Point& rhs) const{
            if(this->y < rhs.y){
                return true;
            }else if(this->y == rhs.y && this->x < rhs.x){
                return true;
            }
            return false;
        };
    };
    
    class Cell{
    public:
        Cell();
        Cell(int _x, int _y);
        void flip();
        void setState(bool state);
        void calculateNeighbors(int gridWidth, int gridHeight);
        
        friend std::ostream& operator << (std::ostream& os, const Cell& cell);
        friend class CellGrid;
        
        bool isActive() const;
        
    private:
        Point position;
        bool bActive;
        std::vector<Point> neighbors;
    };

    std::ostream& operator << (std::ostream& os, const Point& p);
    std::ostream& operator << (std::ostream& os, const Cell& cell);
}
