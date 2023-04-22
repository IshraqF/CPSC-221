#include <iostream>

#include "DrawMaze.h"
#include "cs221util/catch.hpp"

using namespace std;

TEST_CASE("HexCell::constructor", "[weight=1][part=hexcell]") {
    HexCell cell(5, 7);
    REQUIRE(cell.q == 5);
    REQUIRE(cell.r == 7);

    for (int i = 0; i < 6; i++) {
        REQUIRE(cell.links[i] == nullptr);
        REQUIRE(cell.neighbours[i] == nullptr);
    }

    REQUIRE(cell.path_dist_from_start == 0);
}

TEST_CASE("HexCell::link null", "[weight=1][part=hexcell]") {
    HexCell cell(1, 2);
    cell.link(nullptr);

    for (int i = 0; i < 6; i++) {
        REQUIRE(cell.links[i] == nullptr);
    }
}

TEST_CASE("HexCell::link not neighbour", "[weight=1][part=hexcell]") {
    HexCell cell1(1, 2);
    HexCell cell2(2, 4);
    cell1.link(&cell2);

    for (int i = 0; i < 6; i++) {
        REQUIRE(cell1.links[i] == nullptr);
        REQUIRE(cell2.links[i] == nullptr);
    }

    REQUIRE_FALSE(cell1.is_linked(&cell2));
    REQUIRE_FALSE(cell2.is_linked(&cell1));
}

TEST_CASE("HexCell::link neighbour", "[weight=1][part=hexcell]") {
    HexCell cell1(1, 0);
    HexCell cell2(2, -1);
    cell1.link(&cell2);

    for (int i = 0; i < 6; i++) {
        if (i == NE) {
            REQUIRE(cell1.links[i] == &cell2);
            REQUIRE(cell2.links[i] == nullptr);
        } else if (i == SW) {
            REQUIRE(cell2.links[i] == &cell1);
            REQUIRE(cell1.links[i] == nullptr);
        } else {
            REQUIRE(cell1.links[i] == nullptr);
            REQUIRE(cell2.links[i] == nullptr);
        }
    }

    REQUIRE(cell1.is_linked(&cell2));
    REQUIRE(cell2.is_linked(&cell1));
}

TEST_CASE("HexCell::distance", "[weight=1][part=hexcell]") {
    vector<HexCell*> cells = {new HexCell(-2, -2), new HexCell(-2, 1), new HexCell(3, -3), new HexCell(1, 1), new HexCell(0, -2)};

    // distance of cell to itself should be 0
    for (size_t i = 0; i < cells.size(); ++i) {
        REQUIRE(cells[i]->distance(cells[i]) == 0);
    }

    REQUIRE(cells[0]->distance(cells[1]) == 3);
    REQUIRE(cells[0]->distance(cells[2]) == 5);
    REQUIRE(cells[0]->distance(cells[3]) == 6);
    REQUIRE(cells[0]->distance(cells[4]) == 2);

    REQUIRE(cells[1]->distance(cells[0]) == 3);
    REQUIRE(cells[1]->distance(cells[2]) == 5);
    REQUIRE(cells[1]->distance(cells[3]) == 3);
    REQUIRE(cells[1]->distance(cells[4]) == 3);

    REQUIRE(cells[2]->distance(cells[0]) == 5);
    REQUIRE(cells[2]->distance(cells[1]) == 5);
    REQUIRE(cells[2]->distance(cells[3]) == 4);
    REQUIRE(cells[2]->distance(cells[4]) == 3);

    REQUIRE(cells[3]->distance(cells[0]) == 6);
    REQUIRE(cells[3]->distance(cells[1]) == 3);
    REQUIRE(cells[3]->distance(cells[2]) == 4);
    REQUIRE(cells[3]->distance(cells[4]) == 4);

    REQUIRE(cells[4]->distance(cells[0]) == 2);
    REQUIRE(cells[4]->distance(cells[1]) == 3);
    REQUIRE(cells[4]->distance(cells[2]) == 3);
    REQUIRE(cells[4]->distance(cells[3]) == 4);

    for (const auto& cell : cells) delete cell;
}

TEST_CASE("HexBoard::create_board r = 1::correct number of cells created", "[weight=1][part=hexboard]") {
    HexBoard board(1);
    REQUIRE(board.cells.size() == 1);
}

TEST_CASE("HexBoard::create_board r = 1::correct base board image", "[weight=1][part=hexboard]") {
    HexBoard board(1);
    PNG output = DrawMaze::draw_maze(board, 20, "none");
    output.writeToFile("soln_images/debug_r1.png");
    PNG expected;
    expected.readFromFile("soln_images/board_r1.png");
    REQUIRE(output == expected);
}

TEST_CASE("HexBoard::create_board r = 2::correct number of cells created", "[weight=1][part=hexboard]") {
    HexBoard board(2);
    REQUIRE(board.cells.size() == 7);
}

TEST_CASE("HexBoard::create_board r = 2::correct base board image", "[weight=1][part=hexboard]") {
    HexBoard board(2);
    PNG output = DrawMaze::draw_maze(board, 20, "none");
    output.writeToFile("soln_images/debug_r2.png");
    PNG expected;
    expected.readFromFile("soln_images/board_r2.png");
    REQUIRE(output == expected);
}

TEST_CASE("HexBoard::create_board r = 5::correct number of cells created", "[weight=1][part=hexboard]") {
    HexBoard board(5);
    REQUIRE(board.cells.size() == 61);
}

TEST_CASE("HexBoard::create_board r = 5::correct base board image", "[weight=1][part=hexboard]") {
    HexBoard board(5);
    PNG output = DrawMaze::draw_maze(board, 20, "none");
    // output.writeToFile("soln_images/board_r5.png");
    PNG expected;
    expected.readFromFile("soln_images/board_r5.png");
    REQUIRE(output == expected);
}

TEST_CASE("HexBoard::configure_cells::HexCell::is_edge", "[weight=1][part=hexboard]") {
    HexBoard board(3);
    REQUIRE(board.cells[{0, -2}]->is_edge());
    REQUIRE(board.cells[{1, -2}]->is_edge());
    REQUIRE(board.cells[{2, -2}]->is_edge());
    REQUIRE(board.cells[{2, -1}]->is_edge());
    REQUIRE(board.cells[{2, 0}]->is_edge());
    REQUIRE(board.cells[{1, 1}]->is_edge());
    REQUIRE(board.cells[{0, 2}]->is_edge());
    REQUIRE(board.cells[{-1, 2}]->is_edge());
    REQUIRE(board.cells[{-2, 2}]->is_edge());
    REQUIRE(board.cells[{-2, 1}]->is_edge());
    REQUIRE(board.cells[{-2, 0}]->is_edge());
    REQUIRE(board.cells[{-1, -1}]->is_edge());
}

TEST_CASE("HexBoard::configure_cells::correct neighbours assigned", "[weight=1][part=hexboard]") {
    HexBoard board(5);
    REQUIRE(board.cells[{0, 0}]->neighbours[N] == board.cells[{0, -1}]);
    REQUIRE(board.cells[{-2, 0}]->neighbours[NE] == board.cells[{-1, -1}]);
    REQUIRE(board.cells[{-1, -2}]->neighbours[SE] == board.cells[{0, -2}]);
    REQUIRE(board.cells[{2, 2}]->neighbours[S] == nullptr);
    REQUIRE(board.cells[{-4, 2}]->neighbours[SW] == nullptr);
    REQUIRE(board.cells[{1, 1}]->neighbours[NW] == board.cells[{0, 1}]);
}

TEST_CASE("HexBoard::generate_maze::correct links assigned", "[weight=1][part=hexboard]") {
    srand(7);  // random seed for choosing neighbours
    HexBoard board(5);
    board.generate_maze({0, 0}, 0.5);
    PNG output = DrawMaze::draw_maze(board, 20, "none");
    output.writeToFile("soln_images/debug_maze_r5.png");
    REQUIRE(board.cells[{0, 0}]->links[N] == nullptr);

    REQUIRE(board.cells[{-2, 0}]->links[NE] == board.cells[{-1, -1}]);
    REQUIRE(board.cells[{-1, -1}]->links[SW] == board.cells[{-2, 0}]);

    REQUIRE(board.cells[{-1, -2}]->links[SE] == board.cells[{0, -2}]);
    REQUIRE(board.cells[{0, -2}]->links[NW] == board.cells[{-1, -2}]);

    REQUIRE(board.cells[{1, 2}]->links[S] == board.cells[{1, 3}]);
    REQUIRE(board.cells[{1, 3}]->links[N] == board.cells[{1, 2}]);

    REQUIRE(board.cells[{3, -2}]->links[SW] == nullptr);

    REQUIRE(board.cells[{1, 1}]->links[NW] == nullptr);
    PNG expected;
    expected.readFromFile("soln_images/maze_r5.png");
    REQUIRE(output == expected);
}

TEST_CASE("HexBoard::generate_maze::correct longest path length stored", "[weight=1][part=hexboard]") {
    srand(10);
    HexBoard board(5);
    board.generate_maze({0, 0}, 0.5);
    REQUIRE(board.longest_path_dist == 46);
}

TEST_CASE("HexBoard::generate_maze::correct path distance from start for each cell", "[weight=1][part=hexboard]") {
    srand(221);
    HexBoard board(5);
    board.generate_maze({0, 0}, 0.5);
    PNG output = DrawMaze::draw_maze(board, 20, "path");
    output.writeToFile("soln_images/debug_maze_colour_r5.png");
    PNG expected;
    expected.readFromFile("soln_images/maze_colour_r5.png");
    REQUIRE(output == expected);
}

TEST_CASE("HexBoard::generate_maze::correct path distance from start for each cell, different start", "[weight=1][part=hexboard]") {
    srand(221);
    HexBoard board(5);
    board.generate_maze({3, -2}, 0.5);
    PNG output = DrawMaze::draw_maze(board, 20, "path");
    output.writeToFile("soln_images/debug_maze_colour_r5_(3,-2).png");
    PNG expected;
    expected.readFromFile("soln_images/maze_colour_r5_(3,-2).png");
    REQUIRE(output == expected);
}

TEST_CASE("HexBoard::solve_maze::correct solution length", "[weight=1][part=hexboard]") {
    srand(10);
    HexBoard board(5);
    board.generate_maze({0, 0}, 0.5);
    PNG output = DrawMaze::draw_maze(board, 20, "path");
    output.writeToFile("soln_images/debug_solve1.png");
    board.solve_maze();
    REQUIRE(board.solution.size() == 41);
}

TEST_CASE("HexBoard::solve_maze::correct solution vector", "[weight=1][part=hexboard]") {
    srand(42);
    HexBoard board(3);
    board.generate_maze({0, 0}, 1);
    board.solve_maze();
    vector<pair<int, int>> soln_path = {{0, 0}, {0, -1}, {-1, -1}, {-1, 0}, {-2, 0}, {-2, 1}, {-1, 1}, {-2, 2}, {-1, 2}, {0, 1}, {1, 1}, {1, 0}, {2, 0}, {2, -1}, {1, -1}, {2, -2}, {1, -2}, {0, -2}};
    REQUIRE(board.solution == soln_path);
}

TEST_CASE("HexBoard::solve_maze::correct solution image", "[weight=1][part=hexboard]") {
    srand(99);
    HexBoard board(5);
    board.generate_maze({0, 0}, 0.5);
    board.solve_maze();
    PNG output = DrawMaze::draw_solution(board, 20, "none");
    // output.writeToFile("soln_images/maze_sol_r5.png");
    PNG expected;
    expected.readFromFile("soln_images/maze_sol_r5.png");
    REQUIRE(output == expected);
}

TEST_CASE("HexBoard::solve_maze::correct solution image with path colour", "[weight=1][part=hexboard]") {
    srand(1337);
    HexBoard board(5);
    board.generate_maze({0, 0}, 0.5);
    board.solve_maze();
    PNG output = DrawMaze::draw_solution(board, 20, "path");
    // output.writeToFile("soln_images/maze_sol_colour_r5.png");
    PNG expected;
    expected.readFromFile("soln_images/maze_sol_colour_r5.png");
    REQUIRE(output == expected);
}