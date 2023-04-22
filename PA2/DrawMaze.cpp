#include "DrawMaze.h"

#include <cmath>
#include <iostream>

using std::pair;
using std::vector;

namespace DrawMaze {
    MazeParams get_draw_params(int size) {
        double a_size = size / 2.0;
        double height = size * sqrt(3);
        double b_size = height / 2.0;
        return {a_size, b_size, height};
    }

    CellParams get_cell_params(int size, int maze_radius, MazeParams maze_params, HexCell* cell) {
        pair<int, int> offset_coords = axial_to_offset({cell->q, cell->r});
        int x = offset_coords.first;
        int y = offset_coords.second;

        double cx = size + 3 * (x + maze_radius) * maze_params.a_size;
        double cy = maze_params.b_size + (y + maze_radius) * maze_params.height;

        if (x % 2 != 0) {
            cy += maze_params.b_size;
        }

        // f/n = far/near
        // n/s/e/w = north/south/east/west
        int x_fw = (cx - size);
        int x_nw = (cx - maze_params.a_size);
        int x_ne = (cx + maze_params.a_size);
        int x_fe = (cx + size);

        // m = middle
        int y_n = (cy - maze_params.b_size);
        int y_m = cy;
        int y_s = (cy + maze_params.b_size);

        return {cx, cy, x_fw, x_nw, x_ne, x_fe, y_n, y_m, y_s};
    }

    PNG draw_maze(const HexBoard& maze, int size, string colour_mode) {
        if (colour_mode != "none" && colour_mode != "path") {
            std::cerr << "Colour mode must be one of \"none\" or \"path\"." << std::endl;
            return PNG();
        }

        MazeParams params = get_draw_params(size);

        int rows = 2 * maze.radius + 1;
        int columns = 2 * maze.radius + 1;

        int img_width = 3 * params.a_size * columns + params.a_size + 0.5;
        int img_height = params.height * rows + params.b_size + 0.5;

        RGBAPixel cell_colour;
        RGBAPixel wall_colour(0, 0, 0);

        PNG img(img_width, img_height);

        vector<RGBAPixel> colours = spectrum(maze.longest_path_dist + 1);

        // draw backgrounds
        for (const auto& kv : maze.cells) {
            HexCell* cell = kv.second;
            CellParams cell_params = get_cell_params(size, maze.radius, params, cell);
            vector<pair<int, int>> points = {{cell_params.x_fw, cell_params.y_m}, {cell_params.x_nw, cell_params.y_n}, {cell_params.x_ne, cell_params.y_n}, {cell_params.x_fe, cell_params.y_m}, {cell_params.x_ne, cell_params.y_s}, {cell_params.x_nw, cell_params.y_s}};

            if (colour_mode == "none" && make_pair(cell->q, cell->r) != maze.start_coord) cell_colour = RGBAPixel(255, 255, 255);
            else cell_colour = colours[cell->path_dist_from_start];
            img.drawHexagon(points, cell_colour, cell_colour);
        }

        if (colour_mode == "none") {
            RGBAPixel start_colour = RGBAPixel(255, 0, 0);
            RGBAPixel end_colour = RGBAPixel(0, 0, 255);

            HexCell* start_cell = maze.cells.at(maze.start_coord);
            CellParams cell_params = get_cell_params(size, maze.radius, params, start_cell);
            vector<pair<int, int>> points = {{cell_params.x_fw, cell_params.y_m}, {cell_params.x_nw, cell_params.y_n}, {cell_params.x_ne, cell_params.y_n}, {cell_params.x_fe, cell_params.y_m}, {cell_params.x_ne, cell_params.y_s}, {cell_params.x_nw, cell_params.y_s}};

            img.drawHexagon(points, start_colour, start_colour);

            HexCell* end_cell = maze.cells.at(maze.end_coord);
            cell_params = get_cell_params(size, maze.radius, params, end_cell);
            points = {{cell_params.x_fw, cell_params.y_m}, {cell_params.x_nw, cell_params.y_n}, {cell_params.x_ne, cell_params.y_n}, {cell_params.x_fe, cell_params.y_m}, {cell_params.x_ne, cell_params.y_s}, {cell_params.x_nw, cell_params.y_s}};

            img.drawHexagon(points, end_colour, end_colour);
        }

        // draw walls
        for (const auto& kv : maze.cells) {
            HexCell* cell = kv.second;
            CellParams cell_params = get_cell_params(size, maze.radius, params, cell);

            if (!cell->is_linked(cell->neighbours[SW])) img.drawLine({cell_params.x_fw, cell_params.y_m}, {cell_params.x_nw, cell_params.y_s}, wall_colour);

            if (!cell->is_linked(cell->neighbours[NW])) img.drawLine({cell_params.x_fw, cell_params.y_m}, {cell_params.x_nw, cell_params.y_n}, wall_colour);

            if (!cell->is_linked(cell->neighbours[N])) img.drawLine({cell_params.x_nw, cell_params.y_n}, {cell_params.x_ne, cell_params.y_n}, wall_colour);

            if (!cell->is_linked(cell->neighbours[NE])) img.drawLine({cell_params.x_ne, cell_params.y_n}, {cell_params.x_fe, cell_params.y_m}, wall_colour);

            if (!cell->is_linked(cell->neighbours[SE])) img.drawLine({cell_params.x_fe, cell_params.y_m}, {cell_params.x_ne, cell_params.y_s}, wall_colour);

            if (!cell->is_linked(cell->neighbours[S])) img.drawLine({cell_params.x_ne, cell_params.y_s}, {cell_params.x_nw, cell_params.y_s}, wall_colour);
        }

        return img;
    }

    PNG draw_solution(const HexBoard& maze, int size, string colour_mode) {
        PNG img = draw_maze(maze, size, colour_mode);

        MazeParams params = get_draw_params(size);

        RGBAPixel sol_colour = RGBAPixel(0, 0, 0);

        // draw out the solution path
        int sol_length = maze.solution.size();

        for (int i = 0; i < sol_length - 1; i++) {
            // get centre coorindates of cell
            HexCell* cell = maze.cells.at(maze.solution[i]);
            CellParams cell_params = get_cell_params(size, maze.radius, params, cell);

            // get centre coorindates of next cell
            HexCell* next_cell = maze.cells.at(maze.solution[i + 1]);
            CellParams next_cell_params = get_cell_params(size, maze.radius, params, next_cell);

            // draw line to connect the centre of cell with next cell
            img.drawLine({cell_params.cx, cell_params.cy}, {next_cell_params.cx, next_cell_params.cy}, sol_colour);
        }
        return img;
    }

    pair<int, int> axial_to_offset(pair<int, int> axial_coord) {
        int q = axial_coord.first;
        int r = axial_coord.second;

        int x = q;
        int y = r + (q - (q & 1)) / 2;
        return {x, y};
    }

    vector<RGBAPixel> spectrum(int n) {
        vector<RGBAPixel> ret(n);

        for (int i = 0; i < n; ++i) {
            ret[i].from_hsl(240.0 * i / n, 1.0, 0.5);
        }

        return ret;
    }
}