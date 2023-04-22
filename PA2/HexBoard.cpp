#include "HexBoard.h"

#include <iostream>

#include "queue.h"
#include "stack.h"

HexBoard::HexBoard(int radius) {
    /**
     * @todo Your code here!
     */
    this->radius = radius;
    this->start_coord = make_pair(0, 0);
    this->longest_path_dist = 0;
    create_board();
    
    if (cells.empty()){
        HexCell* cell = new HexCell(0, 0);
        this->cells[make_pair(0, 0)] = cell;
    }

    configure_cells();
}

void HexBoard::create_board() {
    /**
     * @todo Your code here!
     */
    for (int q = -radius+1; q < radius; q++) {
        int r1 = max(-radius+1, -q-radius);
        int r2 = min(radius-1, -q+radius);
        if (q < 0) {
            r1 += 1;
            r2 += 1;
        }
        if (q == 0) {
            r2+=1;
        }
        for (int r = r1; r < r2; r++){
            HexCell* cell = new HexCell(q, r);
            this->cells[make_pair(q, r)] = cell;
        }
    }
}

void HexBoard::configure_cells() {
    for(auto kv:this->cells){
        pair<int,int> coords=kv.first;
        HexCell * cell = kv.second;
        cell->neighbours[S] = this->cells.find(make_pair(coords.first, coords.second+1)) == this->cells.end() ? nullptr:cells.find(make_pair(coords.first, coords.second+1))->second;
        cell->neighbours[SE] = this->cells.find(make_pair(coords.first+1, coords.second)) == this->cells.end() ? nullptr:cells.find(make_pair(coords.first+1, coords.second))->second;
        cell->neighbours[SW] = this->cells.find(make_pair(coords.first-1, coords.second+1)) == this->cells.end() ? nullptr:cells.find(make_pair(coords.first-1, coords.second+1))->second;
        cell->neighbours[N] = this->cells.find(make_pair(coords.first, coords.second-1)) == this->cells.end() ? nullptr:cells.find(make_pair(coords.first, coords.second-1))->second;
        cell->neighbours[NE] = this->cells.find(make_pair(coords.first+1, coords.second-1)) == this->cells.end() ? nullptr:cells.find(make_pair(coords.first+1, coords.second-1))->second;
        cell->neighbours[NW] = this->cells.find(make_pair(coords.first-1, coords.second)) == this->cells.end() ? nullptr:cells.find(make_pair(coords.first-1, coords.second))->second;
    }
}

void HexBoard::generate_maze(pair<int, int> start_coord, double branch_prob) {
    this->longest_path_dist=0;
    int edgeDist=0;
    Stack <pair<int,int>> coordStack;
    std::map<std::pair<int, int>, bool> visitedDict;
    coordStack.push(start_coord);
    HexCell * startCell=cells.find(coordStack.peek())->second;
    startCell->path_dist_from_start=0;
    visitedDict.insert(std::make_pair(start_coord, true));
    HexCell * currCell;
    HexCell * neighCell;
    this->start_coord=start_coord;

    while(!coordStack.isEmpty()){
        currCell=cells.find(coordStack.peek())->second;
        neighCell=this->chooseNeighbour(currCell, 
        visitedDict, branch_prob);

        if(neighCell){
            currCell->link(neighCell);
            visitedDict.insert(make_pair(make_pair(neighCell->q,neighCell->r),true));
            neighCell->path_dist_from_start=(currCell->path_dist_from_start)+1;
            if(this->longest_path_dist<neighCell->path_dist_from_start){
                this->longest_path_dist=neighCell->path_dist_from_start;
            }
            if(neighCell->is_edge()){
                if(edgeDist<neighCell->path_dist_from_start){
                    edgeDist=neighCell->path_dist_from_start;
                    this->end_coord=std::make_pair(neighCell->q,neighCell->r);
                }
            }
            coordStack.push(std::make_pair(neighCell->q,neighCell->r));
        } else {
            coordStack.pop();
        }
    }
}

void HexBoard::solve_maze() {
    /**
     * @todo Your code here!
     */
     map<pair<int,int>,bool> visited;
     visited.insert(make_pair(this->start_coord, true));
     vector<pair<int,int>> path;
     solution=findPath(start_coord, visited, path);
     int i=0;
     i++;
}

vector<pair<int,int>> HexBoard::findPath(pair<int,int> start_coord,  map<pair<int, int>, bool>& visited, vector<pair<int,int>> path){
    vector<pair<int,int>> possiblePath;
    path.push_back(start_coord);
    HexCell * start_cell=this->cells.find(start_coord)->second;
    for(int i=0;i<6;i++){
        if(start_cell->links[i] && visited.find(make_pair(start_cell->links[i]->q,start_cell->links[i]->r))==visited.end()){
            visited.insert(make_pair(make_pair(start_cell->links[i]->q,start_cell->links[i]->r),true));
            possiblePath=findPath(make_pair(start_cell->links[i]->q, start_cell->links[i]->r), visited, path);
            if(possiblePath[possiblePath.size()-1]==this->end_coord){
                return possiblePath;
            } 
        }
    }
    return path;
}