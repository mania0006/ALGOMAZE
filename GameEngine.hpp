/*
 * GameEngine.hpp - Main Controller (MVC Pattern)
 */

#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include "GameState.hpp"
#include "Maze.hpp"
#include "NameScreen.hpp"
#include "LevelScreen.hpp"
#include "GameScreen.hpp"
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

class GameEngine {
private:
    RenderWindow* window;
    Font font;
    GameState currentState;
    
    // Game model
    Maze maze;
    
    // Game data
    string playerName;
    
    // Screen instances
    NameScreen nameScreen;
    LevelScreen levelScreen;
    GameScreen gameScreen;
    
    // Helper methods
    void handleStateTransition(optional<GameState> newState);
    void handleGameplayInput(const Event& event);
    
public:
    GameEngine(RenderWindow* win);
    ~GameEngine() = default;
    
    void run();
    void handleInput();
    void render();
};

#endif // GAMEENGINE_HPP

