/*
 * Maze.cpp - Game Model Implementation
 */

#include "Maze.hpp"
#include "Common.hpp"
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;
using namespace sf;

Maze::Maze() 
    : currentLevel(1),
      gameWon(false),
      hasKey(false),
      stepsTaken(0),
      lastPlayerRow(-1),
      lastPlayerCol(-1),
      lastMoveTime(0),
      cachedPath(nullopt) {
    
    // Initialize predefined level layouts
    levels = {
        {{
             "###############",
             "#.............#",
             "#.###########.#",
             "#.............#",
             "#.###########.#",
             "#.............#",
             "#.###########.#",
             "#.............#",
             "#.###########.#",
             "###############"
         }, 1, 1, 8, 13},
        {{
             "###############",
             "#...#......#..#",
             "###.#.####.#.##",
             "#........#....#",
             "#.######.####.#",
             "#......#......#",
             "#####.######.##",
             "#.............#",
             "#.###########.#",
             "###############"
         }, 1, 1, 8, 13},
        {{
             "###############",
             "#.............#",
             "#.###.#.#####.#",
             "#.#...#.....#.#",
             "#.#.#####.#.#.#",
             "#.#.....#.#.#.#",
             "#.#####.#.#.#.#",
             "#.....#.#...#.#",
             "#.###.#.#####.#",
             "###############"
         }, 1, 1, 8, 13}
    };
    
    loadLevel(currentLevel);
}

void Maze::generateDFSMaze(int mazeRows, int mazeCols) {
    // Initialize maze with all walls
    maze.assign(mazeRows, vector<char>(mazeCols, '#'));
    
    // Stack for recursive backtracking
    vector<pair<int, int>> stack;
    
    // Visited cells tracking
    vector<vector<bool>> visited(mazeRows, vector<bool>(mazeCols, false));
    
    // Random number generator
    static random_device rd;
    static mt19937 gen(rd());
    
    // Start from a random cell (must be odd row/col for proper maze structure)
    int startR = 1;
    int startC = 1;
    
    // Mark start as visited and push to stack
    visited[startR][startC] = true;
    maze[startR][startC] = '.';
    stack.push_back({startR, startC});
    
    // Recursive backtracking algorithm
    while (!stack.empty()) {
        pair<int, int> current = stack.back();
        int r = current.first;
        int c = current.second;
        
        // Find unvisited neighbors (cells 2 steps away)
        vector<pair<int, int>> neighbors;
        
        // Check all 4 directions
        for (int i = 0; i < 4; i++) {
            int nr = r + dx[i] * 2;  // 2 steps away
            int nc = c + dy[i] * 2;
            
            // Check if neighbor is valid and unvisited
            if (nr >= 1 && nr < mazeRows - 1 && nc >= 1 && nc < mazeCols - 1 && !visited[nr][nc]) {
                neighbors.push_back({nr, nc});
            }
        }
        
        if (!neighbors.empty()) {
            // Choose random neighbor
            uniform_int_distribution<> dis(0, neighbors.size() - 1);
            int choice = dis(gen);
            pair<int, int> next = neighbors[choice];
            int nextR = next.first;
            int nextC = next.second;
            
            // Determine direction
            int dir = 0;
            if (nextR > r) dir = 1;      // Down
            else if (nextR < r) dir = 0; // Up
            else if (nextC > c) dir = 3; // Right
            else if (nextC < c) dir = 2; // Left
            
            // Carve the wall cell
            int midR = r + dx[dir];
            int midC = c + dy[dir];
            maze[midR][midC] = '.';
            
            // Mark next as visited and carve path
            visited[nextR][nextC] = true;
            maze[nextR][nextC] = '.';
            
            // Push next to stack
            stack.push_back({nextR, nextC});
        } else {
            // No unvisited neighbors, backtrack
            stack.pop_back();
        }
    }
    
    // Ensure border walls remain
    for (int r = 0; r < mazeRows; r++) {
        maze[r][0] = '#';
        maze[r][mazeCols - 1] = '#';
    }
    for (int c = 0; c < mazeCols; c++) {
        maze[0][c] = '#';
        maze[mazeRows - 1][c] = '#';
    }
}

void Maze::loadLevel(int level) {
    if (levels.empty()) {
        return;
    }

    int index = max(1, min(level, static_cast<int>(levels.size()))) - 1;
    currentLevel = index + 1;

    // Special handling for Level 3: Generate using DFS algorithm
    if (level == 3) {
        rows = 15;
        cols = 20;
        
        // Generate the maze using recursive backtracking
        generateDFSMaze(rows, cols);
        
        // Random number generator for wall removal
        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<> rowDist(1, rows - 2);
        uniform_int_distribution<> colDist(1, cols - 2);
        
        // Remove 10-15 random walls between path cells to create loops
        uniform_int_distribution<> loopCount(10, 15);
        int numLoops = loopCount(gen);
        
        for (int i = 0; i < numLoops; i++) {
            int attempts = 0;
            bool found = false;
            
            // Try to find a wall that separates two path cells
            while (!found && attempts < 100) {
                int r = rowDist(gen);
                int c = colDist(gen);
                
                // Check if it's a wall
                if (maze[r][c] == '#') {
                    // Check if this wall separates two path cells
                    // Check horizontal neighbors (left and right)
                    if (c >= 2 && c < cols - 2) {
                        if (maze[r][c - 1] == '.' && maze[r][c + 1] == '.') {
                            maze[r][c] = '.';  // Remove wall to create horizontal loop
                            found = true;
                        }
                    }
                    
                    // Check vertical neighbors (up and down) if horizontal didn't work
                    if (!found && r >= 2 && r < rows - 2) {
                        if (maze[r - 1][c] == '.' && maze[r + 1][c] == '.') {
                            maze[r][c] = '.';  // Remove wall to create vertical loop
                            found = true;
                        }
                    }
                }
                attempts++;
            }
        }
        
        // Set start and goal positions far apart
        playerRow = 1;
        playerCol = 1;
        goalRow = rows - 2;
        goalCol = cols - 2;
        
        // Ensure start and goal are paths
        maze[playerRow][playerCol] = '.';
        maze[goalRow][goalCol] = '.';
        
    } else {
        // Levels 1 and 2 use hardcoded layouts
        const auto& data = levels[index];

        rows = static_cast<int>(data.layout.size());
        cols = rows > 0 ? static_cast<int>(data.layout[0].size()) : 0;

        maze.assign(rows, vector<char>(cols, '#'));
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                maze[r][c] = data.layout[r][c];
            }
        }

        playerRow = data.startRow;
        playerCol = data.startCol;
        goalRow = data.goalRow;
        goalCol = data.goalCol;
    }

    gameWon = false;
    hasKey = false;
    stepsTaken = 0;
    lastPlayerRow = playerRow;
    lastPlayerCol = playerCol;
    cachedPath = nullopt;
    gameClock.restart();

    if (playerRow >= 0 && playerRow < rows && playerCol >= 0 && playerCol < cols) {
        maze[playerRow][playerCol] = 'P';
    }
    if (goalRow >= 0 && goalRow < rows && goalCol >= 0 && goalCol < cols) {
        maze[goalRow][goalCol] = 'G';
    }
}

bool Maze::isValidCell(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return false;
    }
    if (maze[row][col] == '#') {
        return false;  // Wall is blocking
    }
    // Allow '.' (PATH), 'G' (GOAL), 'P' (PLAYER) cells
    return true;
}

optional<vector<Cell>> Maze::findShortestPath() {
    queue<Cell> q;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<Cell>> parent(rows, vector<Cell>(cols, Cell(-1, -1, -1)));
    
    // Safety check for invalid dimensions
    if (rows <= 0 || cols <= 0 || playerRow < 0 || playerRow >= rows || 
        playerCol < 0 || playerCol >= cols || goalRow < 0 || goalRow >= rows || 
        goalCol < 0 || goalCol >= cols) {
        return nullopt;
    }
    
    q.push(Cell(playerRow, playerCol, 0));
    visited[playerRow][playerCol] = true;
    parent[playerRow][playerCol] = Cell(-1, -1, -1);
    
    while (!q.empty()) {
        Cell current = q.front();
        q.pop();
        
        if (current.row == goalRow && current.col == goalCol) {
            // Goal found - backtrack to build the path
            vector<Cell> path;
            Cell backtrack = current;
            int maxPathLength = rows * cols;
            int pathLength = 0;
            
            while (backtrack.row != -1 && backtrack.col != -1 && pathLength < maxPathLength) {
                path.push_back(backtrack);
                Cell next = parent[backtrack.row][backtrack.col];
                
                if (next.row == -1 && next.col == -1) {
                    break;
                }
                
                backtrack = next;
                pathLength++;
            }
            
            reverse(path.begin(), path.end());
            return path;
        }
        
        for (int i = 0; i < 4; i++) {
            int newRow = current.row + dx[i];
            int newCol = current.col + dy[i];
            
            if (isValidCell(newRow, newCol) && !visited[newRow][newCol]) {
                visited[newRow][newCol] = true;
                parent[newRow][newCol] = current;
                q.push(Cell(newRow, newCol, current.distance + 1));
            }
        }
    }
    
    return nullopt;
}

bool Maze::movePlayer(int direction) {
    // Check if we can move (basic movement delay)
    int currentTime = static_cast<int>(movementClock.getElapsedTime().asMilliseconds());
    int moveDelay = 50;
    
    if (currentTime - lastMoveTime < moveDelay) {
        return false;
    }
    
    int newRow = playerRow + dx[direction];
    int newCol = playerCol + dy[direction];
    
    if (!isValidCell(newRow, newCol)) {
        return false;
    }
    
    // Clear old player position
    char oldCell = maze[playerRow][playerCol];
    if (oldCell == 'G') {
        maze[playerRow][playerCol] = 'G';
    } else {
        maze[playerRow][playerCol] = '.';
    }
    
    // Update player position
    playerRow = newRow;
    playerCol = newCol;
    
    // Check if player reached the goal
    if (maze[playerRow][playerCol] == 'G') {
        gameWon = true;
        maze[playerRow][playerCol] = 'P';
    } else {
        maze[playerRow][playerCol] = 'P';
    }
    
    lastMoveTime = currentTime;
    stepsTaken++;
    cachedPath = nullopt;
    return true;
}

