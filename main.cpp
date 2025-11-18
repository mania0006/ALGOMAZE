/*
 * main.cpp - Entry Point
 */

#include "GameEngine.hpp"
#include "Common.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
    // Calculate window size based on largest maze dimensions (Level 3: 15x20)
    int mazeWidth = 20;   // Largest width (Level 3)
    int mazeHeight = 15;  // Largest height (Level 3)
    unsigned int windowWidth = mazeWidth * CELL_SIZE + WINDOW_PADDING * 2;
    unsigned int windowHeight = mazeHeight * CELL_SIZE + WINDOW_PADDING * 2 + 150;  // Extra for text
    
    // Create window (SFML 3.0 uses Vector2u)
    RenderWindow window(VideoMode(Vector2u(windowWidth, windowHeight)), 
                       "AlgoMaze - Graphics Edition");
    window.setFramerateLimit(60);  // 60 FPS
    
    // Create and run the game engine
    GameEngine game(&window);
    game.run();
    
    return 0;
}

