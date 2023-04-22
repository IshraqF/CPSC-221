#include <algorithm>
#include <cmath>
#include <map>
#include <random>
#include <vector>

#include "HexCell.h"

using std::map;
using std::pair;
using std::vector;
using namespace cs221util;

class HexBoard {
public:
    // variables

    // Longest path distance from the centre to any cell.
    int longest_path_dist;

    // Radius of the maze
    int radius;

    // The start coordinate of the maze
    pair<int, int> start_coord;

    // The end coordinate of the maze
    pair<int, int> end_coord;

    // Solution of the maze. Contains pairs representing the path from the centre to the exit
    vector<pair<int, int>> solution;

    // A mapping from the coordinates of the cells to a pointer to the cell.
    map<pair<int, int>, HexCell*> cells;

    // functions

    /**
     * Constructor. Creates a board with given radius, creating new HexCells and inserting them into this->cells by calling createBoard()
     * and setting cells to have the appropriate neighbours by calling configure_cells(). The default start_coord is (0, 0).
     * @note There is no maze yet! The board is just a beehive for now.
     * @param radius The radius of the board
     */
    HexBoard(int radius);

    /**
      * Traverses the board via dfs to generate the maze, updating and keeping track of:
      * A. The length of the longest path to an edge in the maze

      * The algorithm goes as follows:
      * 1. Add the start_coord to the stack, and mark as visited
      * 2. While the stack is not empty do:

      *   a. Peek the top of the stack (call it curr_cell)
      *   c. Use chooseNeighbour to choose the neighbour to visit
      *   d. If the neighbour exists, for that neighbour (call it neigh_cell) do:

      *     i. Link curr_cell with neigh_cell
      *     ii. Set neigh_coord to be visited
      *     iii. Update the neigh_cell's path distance
      *     iv. If necessary, update length of longest path so far (longest_path_dist)
      *     v. Update the end coordinate only if its path distance to start is strictly greater
      *     vi. Push neigh_cell into the stack

      *   e. Otherwise (if chooseNeighbour returns nullptr), pop the stack.

      * @param start_coord The {q, r} coordinate of the start of the maze.
      * @param branch_prob Specifies how often it should "branch out" when choosing neighbours.
      *                    A small branch_prob means neighbours of the same radius (same dist from the centre) are preferred
      *                    A large branch_prob means neighbours of a different radius (diff dist from the centre) are preferred
      * REQUIRE: create_board() is already called
      */
    void generate_maze(pair<int, int> start_coord, double branch_prob);

    /**
      * Populate (member variable) solution as a list of coordinates from start_coord to end_coord, represented as {q, r} pairs.

      * REQUIRE: generate_maze must be called already
      */
    void solve_maze();
    
    vector<pair<int,int>> findPath(pair<int,int> start_coord,  map<pair<int, int>, bool>& visited, vector<pair<int,int>> path);

    // Frees all dynamically allocated memory associated with the board.
    ~HexBoard();

private:
    /**
     * Creates all neccessary HexCells up to the given radius and insert them into this->cells.
     */
    void create_board();

    /**
     * Set all cells in this->cells to have the appropriate neighbours.
     */
    void configure_cells();

    /**
     * Gets the coordinates of the six neighbours of coord.
     * @param coord The input coordinate.
     */
    vector<pair<int, int>> get_neigh_coords(const pair<int, int>& coord) const;

    /**
     * Choose a random unvisited neighbour of cell, and returns either
     *    a. a neighbour in the same ring as cell (with probability 1 - branch_prob)
     *    b. a neighbour in a different ring as cell (with probability branch_prob)
     *
     * If all neighbours are in the same ring as cell, then returned neighbour will be
     * in the same ring. Similarly, if all neighbours are in different ring(s) as cell,
     * then returned neighbour will be in a different ring.
     *
     * If there are no unvisited neighbours, returns nullptr.
     *
     * @param cell The cell to choose a random neighbour from.
     * @param visited A map from coordinate to boolean indicating whether a cell has been visited.
     * @param branch_prob The probability that a random neighbour from a different ring
     * is chosen, if there are neighbours both in the same ring and different rings.
     * @note rings are centred at the *start* coordinate, not (0, 0).
     */
    HexCell* chooseNeighbour(HexCell* cell, const map<pair<int, int>, bool>& visited, double branch_prob) const;
};