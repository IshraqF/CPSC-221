#include "HexBoard.h"

HexBoard::~HexBoard() {
    for (auto kv : cells) {
        HexCell* cell = kv.second;
        delete cell;
    }
}

vector<pair<int, int>> HexBoard::get_neigh_coords(const pair<int, int>& coord) const {
    return {
        {coord.first, coord.second - 1},
        {coord.first + 1, coord.second - 1},
        {coord.first + 1, coord.second},
        {coord.first, coord.second + 1},
        {coord.first - 1, coord.second + 1},
        {coord.first - 1, coord.second}};
}

HexCell* HexBoard::chooseNeighbour(HexCell* cell, const map<pair<int, int>, bool>& visited, double branch_prob) const {
    vector<HexCell*> neigh_same_dist;
    vector<HexCell*> neigh_diff_dist;

    for (HexCell* neigh_cell : cell->neighbours) {
        if (neigh_cell && visited.find({neigh_cell->q, neigh_cell->r}) == visited.end()) {
            if (neigh_cell->distance(cells.at(start_coord)) == cell->distance(cells.at(start_coord))) {
                neigh_same_dist.push_back(neigh_cell);
            } else {
                neigh_diff_dist.push_back(neigh_cell);
            }
        }
    }

    if (neigh_same_dist.empty() && neigh_diff_dist.empty()) {
        return nullptr;
    } else if (neigh_same_dist.empty()) {
        int idx = rand() % neigh_diff_dist.size();
        return neigh_diff_dist[idx];
    } else if (neigh_diff_dist.empty()) {
        int idx = rand() % neigh_same_dist.size();
        return neigh_same_dist[idx];
    } else {
        std::discrete_distribution<int> dist({branch_prob, 1 - branch_prob});
        std::mt19937 gen(rand());

        int choice = dist(gen);

        if (choice == 0) {
            int idx = rand() % neigh_diff_dist.size();
            return neigh_diff_dist[idx];
        } else {
            int idx = rand() % neigh_same_dist.size();
            return neigh_same_dist[idx];
        }
    }
}