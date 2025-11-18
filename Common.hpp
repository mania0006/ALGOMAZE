/*
 * Common.hpp - Shared constants, structs, and definitions
 */

#ifndef COMMON_HPP
#define COMMON_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using namespace std;
using namespace sf;

// Constants for maze representation
const int CELL_SIZE = 40;        // Size of each cell in pixels
const int WINDOW_PADDING = 50;   // Padding around the maze

// Direction vectors for movement (up, down, left, right)
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

// Structure to represent a cell in the maze
struct Cell {
    int row, col;
    int distance;
    
    Cell(int r = 0, int c = 0, int d = 0) : row(r), col(c), distance(d) {}
};

// Structure to represent a level definition
struct LevelDefinition {
    vector<string> layout;
    int startRow;
    int startCol;
    int goalRow;
    int goalCol;
};

// Game color constants
namespace GameColors {
    const Color WallColor(40, 40, 60);        // Dark blue-gray
    const Color PathColor(220, 220, 220);     // Light gray
    const Color PlayerColor(50, 200, 50);      // Green
    const Color GoalColor(200, 50, 50);       // Red
    const Color BackgroundColor(30, 30, 40);  // Dark background
    const Color MudColor(101, 67, 33);        // Brown color for mud
    const Color ObstacleColor(180, 50, 50);   // Red color for obstacles
}

#endif // COMMON_HPP

