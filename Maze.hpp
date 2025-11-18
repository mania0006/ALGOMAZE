/*
 * Maze.hpp - Game Model (Maze Logic)
 */

#ifndef MAZE_HPP
#define MAZE_HPP

#include "Common.hpp"
#include <SFML/Graphics.hpp>
#include <queue>
#include <optional>
#include <vector>

using namespace std;
using namespace sf;

class Maze {
private:
    vector<vector<char>> maze;        // 2D grid representing the maze
    int rows, cols;                   // Dimensions of the maze
    int playerRow, playerCol;         // Player's current position
    int goalRow, goalCol;            // Goal position
    bool gameWon;                     // Game state flag
    int currentLevel;                 // Selected level index (1-based)
    vector<LevelDefinition> levels;   // Predefined level layouts
    
    Clock gameClock;                   // Game timer
    int stepsTaken;                    // Number of steps taken
    optional<vector<Cell>> cachedPath;  // Cached shortest path
    int lastPlayerRow, lastPlayerCol;   // Track player position for cache invalidation
    
    // Game state
    bool hasKey;                       // Player has collected the key
    
    // Movement timing
    Clock movementClock;               // Clock to track movement timing
    int lastMoveTime;                  // Last time player moved (ms)
    
    // Private helper methods
    void generateDFSMaze(int mazeRows, int mazeCols);
    bool isValidCell(int row, int col);
    
public:
    Maze();
    
    // Level management
    void loadLevel(int level);
    int getCurrentLevel() const { return currentLevel; }
    
    // Game state getters
    const vector<vector<char>>& getMazeData() const { return maze; }
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    int getPlayerRow() const { return playerRow; }
    int getPlayerCol() const { return playerCol; }
    int getGoalRow() const { return goalRow; }
    int getGoalCol() const { return goalCol; }
    int getStepsTaken() const { return stepsTaken; }
    float getElapsedTime() const { return gameClock.getElapsedTime().asSeconds(); }
    bool isGameWon() const { return gameWon; }
    
    // Game logic
    bool movePlayer(int direction);
    optional<vector<Cell>> findShortestPath();
};

#endif // MAZE_HPP

