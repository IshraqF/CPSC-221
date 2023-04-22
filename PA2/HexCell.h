#include <vector>

#include "cs221util/RGBAPixel.h"

// Sides
const int N = 0;
const int NE = 1;
const int SE = 2;
const int S = 3;
const int SW = 4;
const int NW = 5;

class HexCell {
public:
    // Axial coordinates of the cell
    int q, r;

    // Path distance between the cell and the start coordinate in the maze
    int path_dist_from_start;

    // Neighbours are adjacent cells
    HexCell* neighbours[6];

    // Links are connected neighbours, i.e. there are no walls between them
    HexCell* links[6];

    /**
     * HexCell constructor. Initializes all neighbours and links to be nullptrs,
     * and path_dist_from_start to 0.
     * @param Q Axial coordinates
     * @param R of the hex cell
     */
    HexCell(int Q, int R);

    /**
     * Link with a neighbouring cell.
     * @param cell A HexCell to link. If cell is nullptr or is not a neighbour of this cell, do nothing.
     * @note remember to link both directions!
     */
    void link(HexCell* cell);

    /**
     * Gets the side of a neighbour. Each side is represented with an int in [0,5].
     * See above for the definition of the sides
     * @param cell A neighbouring HexCell
     * @return The side of cell
     * REQUIRE: cell is a neighbour of this cell
     */
    int get_neighbour_side(const HexCell* cell) const;

    /**
     * Determines if a given cell is linked with this cell.
     * @param cell A HexCell to check
     * @return True if this is linked with cell, false otherwise
     */
    bool is_linked(const HexCell* cell) const;

    /**
     * @param cell A HexCell to calculate the distance to
     * @return The cell distance (ignoring walls in the maze) between this cell and another cell.
     * @return -1 if cell is nullptr.
     * @note use the q and r private members of two cells to determine the distance.
     */
    int distance(const HexCell* cell) const;

    /**
     * @return true, if any neighbour is nullptr.
     * @return false, if all neighbours are non empty.
     * REQUIRE: HexBoard's configure_cells is called
     */
    bool is_edge() const;
};