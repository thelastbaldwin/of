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
    
    void CellGrid::changeDirection(){
        activeSet.clear();
        activeSet.resize(0);
        isSpreading = !isSpreading;
    };
    
    int CellGrid::getRemainingCellCount() const{
        return width * height - activeSet.size();
    };
    
    void CellGrid::spread(){
        if(getRemainingCellCount() > 0){
            std::cout << activeSet.size() << "\n";
            if(activeSet.size() == 0){
                //random seed
                Cell rCell = getRandomCell();
                rCell.flip();
                activeSet.push_back(rCell.position);
            }else{
                for(int i = 0, size = activeSet.size(); i < size; ++i){
                    std::vector<Point> neighbors;
                    
                    for(auto pointIter = cells[activeSet[i]].neighbors.begin(); pointIter != cells[activeSet[i]].neighbors.end(); ++pointIter){
                        //add relevant neighbors to set depending on direction
                        if((isSpreading && !cells[*pointIter].isActive()) || (!isSpreading && cells[*pointIter].isActive())){
                            neighbors.push_back(*pointIter);
                        }
                    }
                    
                    //pick a random cell from the set
                    if(neighbors.size() > 0){
                        int index = int(ofRandom (neighbors.size()));
                        Point nextActivePoint = neighbors[index];
                        cells[nextActivePoint].flip();
                        activeSet.push_back(nextActivePoint);
                    }
                }
            }
        }
    };
    
    std::ostream& operator << (std::ostream& os, const Virus::CellGrid& cellGrid){
        for(auto it = cellGrid.cells.begin(); it != cellGrid.cells.end();++it){
            os << it->second;
        }
        return os;
    }
}
