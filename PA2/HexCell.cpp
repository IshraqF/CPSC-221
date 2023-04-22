#include "HexCell.h"


#include <cmath>

HexCell::HexCell(int Q, int R) {
    this->q=Q;
    this->r=R;
    this->path_dist_from_start=0;
    for(int i=0;i<6;i++){
        neighbours[i]=nullptr;
        links[i]=nullptr;
    }
}

void HexCell::link(HexCell* cell) {
    /**
     * @todo Your code here!
     */
     if(cell){
        if(cell->q-this->q==1){
            if(cell->r-this->r==0) {
                links[SE]=cell;
                cell->links[NW]=this;
            }
            else if(cell->r-this->r==-1){
                links[NE]=cell;
                cell->links[SW]=this;
            } 
        }
        else if(cell->q-this->q==0){
            if(cell->r-this->r==1){
                links[S]=cell;
                cell->links[N]=this;
            }
            else if(cell->r-this->r==-1){
                links[N]=cell;
                cell->links[S]=this;
            }
        }
        else if(cell->q-this->q==-1){
            if(cell->r-this->r==0){
                links[NW]=cell;
                cell->links[SE]=this;
            }
            else if(cell->r-this->r==1){
                links[SW]=cell;
                cell->links[NE]=this;
            }
        }
     }
}

int HexCell::get_neighbour_side(const HexCell* cell) const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
        if(cell->q-this->q==1){
            if(cell->r-this->r==0) {
                return SE; 
            }
            else if(cell->r-this->r==-1){
                return NE;
            }
        }
        else if(cell->q-this->q==0){
            if(cell->r-this->r==-1){
                return N;
            }
            else if(cell->r-this->r==1){
                return S;
            }
        }
        else if(cell->q-this->q==-1){
            if(cell->r-this->r==0){
                return NW;
            }
            else if(cell->r-this->r==1){
                return SW;
            }
        }
        return 6;
}

bool HexCell::is_linked(const HexCell* cell) const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
     if(cell){
        for(int i =0;i<6;i++){
            if(links[i]==cell){
                return true;
            }
        }
     }
     
    return false;
}

int HexCell::distance(const HexCell* cell) const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
     if(cell){
        return (abs(cell->q - this->q) + abs(cell->q + cell->r - this->q - this->r)
          + abs(cell->r - this->r)) / 2;
     }
    return -1;
}

bool HexCell::is_edge() const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
     for(int i=0;i<6;i++){
       if(!(neighbours[i])) return true; 
     }
    return false;
}