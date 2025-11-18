/*
 * GameEngine.cpp - Main Controller Implementation
 */

#include "GameEngine.hpp"
#include "Common.hpp"
#include <iostream>

using namespace std;
using namespace sf;

GameEngine::GameEngine(RenderWindow* win)
    : window(win),
      currentState(GameState::NAME_INPUT),
      nameScreen(win, &font, playerName),
      levelScreen(win, &font, playerName),
      gameScreen(win, &font, maze, playerName) {
    
    // Load font
    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
        if (!font.openFromFile("arial.ttf")) {
            if (!font.openFromFile("C:/Windows/Fonts/calibri.ttf")) {
                if (!font.openFromFile("C:/Windows/Fonts/times.ttf")) {
                    // Font loading failed
                }
            }
        }
    }
}

void GameEngine::handleStateTransition(optional<GameState> newState) {
    if (newState.has_value()) {
        GameState nextState = newState.value();
        
        // Handle level selection transition
        if (currentState == GameState::LEVEL_SELECT && nextState == GameState::GAMEPLAY) {
            int selectedLevel = levelScreen.getSelectedLevel();
            if (selectedLevel >= 1 && selectedLevel <= 3) {
                maze.loadLevel(selectedLevel);
            }
        }
        
        currentState = nextState;
    }
}

void GameEngine::handleGameplayInput(const Event& event) {
    if (event.is<Event::KeyPressed>()) {
        const auto* keyEvent = event.getIf<Event::KeyPressed>();
        if (keyEvent) {
            // Arrow keys
            if (keyEvent->code == Keyboard::Key::Up) {
                maze.movePlayer(0);
            } else if (keyEvent->code == Keyboard::Key::Down) {
                maze.movePlayer(1);
            } else if (keyEvent->code == Keyboard::Key::Left) {
                maze.movePlayer(2);
            } else if (keyEvent->code == Keyboard::Key::Right) {
                maze.movePlayer(3);
            }
            
            // WASD keys
            if (keyEvent->code == Keyboard::Key::W) {
                maze.movePlayer(0);
            } else if (keyEvent->code == Keyboard::Key::S) {
                maze.movePlayer(1);
            } else if (keyEvent->code == Keyboard::Key::A) {
                maze.movePlayer(2);
            } else if (keyEvent->code == Keyboard::Key::D) {
                maze.movePlayer(3);
            }
            
            // Check for win condition
            if (maze.isGameWon()) {
                currentState = GameState::GAME_WON;
            }
        }
    }
}

void GameEngine::handleInput() {
    optional<Event> eventOpt;
    while ((eventOpt = window->pollEvent())) {
        Event event = eventOpt.value();
        
        if (event.is<Event::Closed>()) {
            window->close();
            return;
        }
        
        // ESC key handling
        if (event.is<Event::KeyPressed>()) {
            const auto* keyEvent = event.getIf<Event::KeyPressed>();
            if (keyEvent && keyEvent->code == Keyboard::Key::Escape) {
                if (currentState == GameState::GAMEPLAY) {
                    window->close();
                    return;
                }
            }
        }
        
        // Delegate input to current screen
        optional<GameState> newState = nullopt;
        
        if (currentState == GameState::NAME_INPUT) {
            newState = nameScreen.handleInput(event);
        } else if (currentState == GameState::LEVEL_SELECT) {
            newState = levelScreen.handleInput(event);
        } else if (currentState == GameState::GAMEPLAY) {
            handleGameplayInput(event);
        }
        // GAME_WON state handles its own input in drawWinMessage
        
        // Handle state transitions
        handleStateTransition(newState);
    }
}

void GameEngine::render() {
    window->clear(GameColors::BackgroundColor);
    
    if (currentState == GameState::NAME_INPUT) {
        nameScreen.draw();
    } else if (currentState == GameState::LEVEL_SELECT) {
        levelScreen.draw();
    } else if (currentState == GameState::GAMEPLAY) {
        gameScreen.draw();
    } else if (currentState == GameState::GAME_WON) {
        float finalElapsedTime = maze.getElapsedTime();
        gameScreen.drawWinMessage(finalElapsedTime);
        return;  // drawWinMessage handles its own loop
    }
    
    window->display();
}

void GameEngine::run() {
    while (window->isOpen() && currentState != GameState::GAME_WON) {
        handleInput();
        render();
    }
    
    // Handle GAME_WON state (drawWinMessage has its own loop)
    if (currentState == GameState::GAME_WON) {
        float finalElapsedTime = maze.getElapsedTime();
        gameScreen.drawWinMessage(finalElapsedTime);
    }
}

