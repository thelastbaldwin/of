//
//  CellGrid.cpp
//  cellSpread
//
//  Created by Minor, Steve on 12/12/14.
//
//

#include "CellGrid.h"

namespace Virus{
    CellGrid::CellGrid(): isSpreading(true), cellDisplay(){};
    
    
    CellGrid::CellGrid(int _x, int _y, int _width, int _height, int _cellSize, ofImage* tile):width(_width), height(_height), isSpreading(true), cellDisplay(_x, _y, _width, _height, _cellSize, tile){
        for(int row = 0; row < height; row++){
            for(int column = 0; column < width; ++column){
                cells.insert(std::pair<Point, Cell>(Point(column, row), Cell(column,row)));
            }
        }
        
        for(auto it = cells.begin(); it != cells.end();++it){
            it->second.calculateNeighbors(_width, _height);
        }

    };
    
    void CellGrid::draw(){
        cellDisplay.draw(cells.begin(), cells.end());
    };

    
    Cell CellGrid::getRandomCell(){
        int randX = int(ofRandom(0, float(width)));
        int randY = int(ofRandom(0, float(height)));
        
        return cells[Point(randX, randY)];
    };
    
    void CellGrid::spread(){
        //determine next generation depending on isSpreading
        if(isSpreading){
            //spreading
            if(activeSet.size() == 0){
                Cell rCell = getRandomCell();
                rCell.flip();
                activeSet.push_back(rCell.position);
            }else{
                for(auto it = cells.begin(); it != cells.end();++it){
                    //copy all neighbor cells that are inactive
                    std::vector<Cell> inactiveNeighbors;
                    for(auto pointIter = it->second.neighbors.begin(); pointIter != it->second.neighbors.end(); ++pointIter){
                        //add inactive neighbors to set
                        if(!cells[it->first].isActive()){
                            inactiveNeighbors.push_back(it->second);
                        }
                    }
                    
                    //pick a random inactive cell
                    if(inactiveNeighbors.size() > 0){
                        int index = int(ofRandom(inactiveNeighbors.size() + 1));
                        Point nextActivePoint = inactiveNeighbors[index].position;
                        cells[nextActivePoint].flip();
                        activeSet.push_back(nextActivePoint);
                        
                    }
                    //add that to the active set
                }
            }
        }else{
            //contracting
        }
    };
    
    std::ostream& operator << (std::ostream& os, const Virus::CellGrid& cellGrid){
        for(auto it = cellGrid.cells.begin(); it != cellGrid.cells.end();++it){
            os << it->second;
        }
        return os;
    }
}
