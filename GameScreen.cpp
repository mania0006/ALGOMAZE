/*
 * GameScreen.cpp - Gameplay Screen Implementation
 */

#include "GameScreen.hpp"
#include "Common.hpp"
#include <algorithm>

using namespace std;
using namespace sf;

GameScreen::GameScreen(RenderWindow* win, Font* f, Maze& m, const string& name)
    : ScreenBase(win, f), maze(m), playerName(name), 
      lastPlayerRow(-1), lastPlayerCol(-1), cachedPath(nullopt) {
}

void GameScreen::draw() {
    const auto& mazeData = maze.getMazeData();
    int rows = maze.getRows();
    int cols = maze.getCols();
    
    // Draw background
    RectangleShape background(Vector2f(
        cols * CELL_SIZE + WINDOW_PADDING * 2,
        rows * CELL_SIZE + WINDOW_PADDING * 2 + 100
    ));
    background.setFillColor(GameColors::BackgroundColor);
    background.setPosition(Vector2f(0, 0));
    window->draw(background);
    
    // Draw each cell
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            RectangleShape cell(Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
            cell.setPosition(Vector2f(
                WINDOW_PADDING + j * CELL_SIZE + 1,
                WINDOW_PADDING + i * CELL_SIZE + 1
            ));
            
            if (mazeData[i][j] == '#') {
                // Wall
                cell.setFillColor(GameColors::WallColor);
            } else if (mazeData[i][j] == 'P') {
                // Player - draw as circle
                CircleShape playerCircle(CELL_SIZE / 2 - 2);
                playerCircle.setFillColor(GameColors::PlayerColor);
                playerCircle.setPosition(Vector2f(
                    WINDOW_PADDING + j * CELL_SIZE + 1,
                    WINDOW_PADDING + i * CELL_SIZE + 1
                ));
                window->draw(cell);
                window->draw(playerCircle);
                continue;
            } else if (mazeData[i][j] == 'G') {
                // Goal - draw with glow effect
                cell.setFillColor(GameColors::GoalColor);
                CircleShape glow(CELL_SIZE / 1.5f);
                glow.setFillColor(Color(GameColors::GoalColor.r, GameColors::GoalColor.g, GameColors::GoalColor.b, 100));
                glow.setPosition(Vector2f(
                    WINDOW_PADDING + j * CELL_SIZE + CELL_SIZE / 6,
                    WINDOW_PADDING + i * CELL_SIZE + CELL_SIZE / 6
                ));
                window->draw(cell);
                window->draw(glow);
            } else {
                // Path
                cell.setFillColor(GameColors::PathColor);
            }
            
            window->draw(cell);
        }
    }
    
    // Draw UI text
    int windowWidth = cols * CELL_SIZE + WINDOW_PADDING * 2;
    int textY = rows * CELL_SIZE + WINDOW_PADDING + 20;
    
    Text titleText(*font, "=== ALGOMAZE - Navigate to the Goal! ===", 20);
    titleText.setFillColor(Color::White);
    titleText.setPosition(Vector2f(20, textY));
    window->draw(titleText);
    
    // Display player name
    Text playerNameText(*font, "Player: " + playerName, 16);
    playerNameText.setFillColor(Color(200, 255, 200));
    playerNameText.setPosition(Vector2f(20, textY + 20));
    window->draw(playerNameText);
    
    Text controlsText(*font, "Controls: Arrow Keys or WASD to move | ESC to quit", 16);
    controlsText.setFillColor(Color(200, 200, 200));
    controlsText.setPosition(Vector2f(20, textY + 40));
    window->draw(controlsText);
    
    // Get shortest path (cache if needed)
    int currentPlayerRow = maze.getPlayerRow();
    int currentPlayerCol = maze.getPlayerCol();
    
    if (!cachedPath.has_value() || lastPlayerRow != currentPlayerRow || lastPlayerCol != currentPlayerCol) {
        cachedPath = maze.findShortestPath();
        lastPlayerRow = currentPlayerRow;
        lastPlayerCol = currentPlayerCol;
    }
    optional<vector<Cell>> pathOpt = cachedPath;
    
    // UI elements below maze
    Text levelText(*font, "Level " + to_string(maze.getCurrentLevel()) + " of 3", 16);
    levelText.setFillColor(Color(180, 200, 255));
    levelText.setPosition(Vector2f(20, textY + 60));
    window->draw(levelText);
    
    // Shortest Path
    if (pathOpt.has_value()) {
        int pathSteps = static_cast<int>(pathOpt.value().size()) - 1;
        Text pathText(*font, "Shortest Path: " + to_string(pathSteps) + " steps", 16);
        pathText.setFillColor(Color(150, 255, 150));
        pathText.setPosition(Vector2f(20, textY + 80));
        window->draw(pathText);
    } else {
        Text pathText(*font, "Goal is unreachable!", 16);
        pathText.setFillColor(Color(255, 150, 150));
        pathText.setPosition(Vector2f(20, textY + 80));
        window->draw(pathText);
    }
    
    // Display elapsed time
    float elapsed = maze.getElapsedTime();
    int seconds = static_cast<int>(elapsed);
    int minutes = seconds / 60;
    seconds = seconds % 60;
    
    string elapsedTimeStr = "Elapsed: ";
    if (minutes > 0) {
        elapsedTimeStr += to_string(minutes) + "m ";
    }
    elapsedTimeStr += to_string(seconds) + "s";
    
    Text timeText(*font, elapsedTimeStr, 16);
    timeText.setFillColor(Color(255, 200, 100));
    timeText.setPosition(Vector2f(20, textY + 100));
    window->draw(timeText);
    
    // Steps Taken
    Text stepsText(*font, "Steps Taken: " + to_string(maze.getStepsTaken()), 16);
    stepsText.setFillColor(Color(200, 200, 255));
    stepsText.setPosition(Vector2f(20, textY + 120));
    window->draw(stepsText);
    
    // Legend - positioned at bottom-right corner
    Vector2u windowSize = window->getSize();
    int legendX = static_cast<int>(windowSize.x) - 220;
    int legendY = static_cast<int>(windowSize.y) - 121;
    drawLegend(legendX, legendY);
}

void GameScreen::drawLegend(int x, int y) {
    Text legendTitle(*font, "Legend:", 16);
    legendTitle.setFillColor(Color::White);
    legendTitle.setPosition(Vector2f(x, y));
    window->draw(legendTitle);
    
    // Player
    CircleShape playerIcon(8);
    playerIcon.setFillColor(GameColors::PlayerColor);
    playerIcon.setPosition(Vector2f(x, y + 25));
    window->draw(playerIcon);
    
    Text playerText(*font, " = Player", 14);
    playerText.setFillColor(Color::White);
    playerText.setPosition(Vector2f(x + 20, y + 20));
    window->draw(playerText);
    
    // Goal - draw with glow effect
    RectangleShape goalIcon(Vector2f(16, 16));
    goalIcon.setFillColor(GameColors::GoalColor);
    goalIcon.setPosition(Vector2f(x, y + 50));
    window->draw(goalIcon);
    
    CircleShape goalGlow(10.0f);
    goalGlow.setFillColor(Color(GameColors::GoalColor.r, GameColors::GoalColor.g, GameColors::GoalColor.b, 100));
    goalGlow.setPosition(Vector2f(x + 3.0f, y + 53.0f));
    window->draw(goalGlow);
    
    Text goalText(*font, " = Goal", 14);
    goalText.setFillColor(Color::White);
    goalText.setPosition(Vector2f(x + 20, y + 47));
    window->draw(goalText);
    
    // Wall
    RectangleShape wallIcon(Vector2f(16, 16));
    wallIcon.setFillColor(GameColors::WallColor);
    wallIcon.setPosition(Vector2f(x, y + 75));
    window->draw(wallIcon);
    
    Text wallText(*font, " = Wall", 14);
    wallText.setFillColor(Color::White);
    wallText.setPosition(Vector2f(x + 20, y + 72));
    window->draw(wallText);
    
    // Path
    RectangleShape pathIcon(Vector2f(16, 16));
    pathIcon.setFillColor(GameColors::PathColor);
    pathIcon.setPosition(Vector2f(x, y + 100));
    window->draw(pathIcon);
    
    Text pathText(*font, " = Path", 14);
    pathText.setFillColor(Color::White);
    pathText.setPosition(Vector2f(x + 20, y + 97));
    window->draw(pathText);
}

void GameScreen::drawWinMessage(float finalElapsedTime) {
    window->clear(GameColors::BackgroundColor);
    
    int finalSeconds = static_cast<int>(finalElapsedTime);
    int finalMinutes = finalSeconds / 60;
    finalSeconds = finalSeconds % 60;
    
    string finalTimeStr = "";
    if (finalMinutes > 0) {
        finalTimeStr += to_string(finalMinutes) + "m ";
    }
    finalTimeStr += to_string(finalSeconds) + "s";
    
    // Draw win message
    Text winTitle(*font, "CONGRATULATIONS!", 48);
    winTitle.setFillColor(Color(50, 200, 50));
    winTitle.setStyle(Text::Style::Bold);
    
    FloatRect textRect = winTitle.getLocalBounds();
    winTitle.setOrigin(Vector2f(
        textRect.position.x + textRect.size.x / 2.0f,
        textRect.position.y + textRect.size.y / 2.0f
    ));
    winTitle.setPosition(Vector2f(
        window->getSize().x / 2.0f,
        window->getSize().y / 2.0f - 100
    ));
    window->draw(winTitle);
    
    Text winSubtitle(*font, "You successfully reached the goal!", 24);
    winSubtitle.setFillColor(Color::White);
    
    textRect = winSubtitle.getLocalBounds();
    winSubtitle.setOrigin(Vector2f(
        textRect.position.x + textRect.size.x / 2.0f,
        textRect.position.y + textRect.size.y / 2.0f
    ));
    winSubtitle.setPosition(Vector2f(
        window->getSize().x / 2.0f,
        window->getSize().y / 2.0f - 50
    ));
    window->draw(winSubtitle);
    
    // Display final time
    Text timeText(*font, "Time: " + finalTimeStr, 20);
    timeText.setFillColor(Color(255, 200, 100));
    
    textRect = timeText.getLocalBounds();
    timeText.setOrigin(Vector2f(
        textRect.position.x + textRect.size.x / 2.0f,
        textRect.position.y + textRect.size.y / 2.0f
    ));
    timeText.setPosition(Vector2f(
        window->getSize().x / 2.0f,
        window->getSize().y / 2.0f + 10
    ));
    window->draw(timeText);
    
    // Display total steps taken
    Text stepsText(*font, "Steps Taken: " + to_string(maze.getStepsTaken()), 20);
    stepsText.setFillColor(Color(200, 200, 255));
    
    textRect = stepsText.getLocalBounds();
    stepsText.setOrigin(Vector2f(
        textRect.position.x + textRect.size.x / 2.0f,
        textRect.position.y + textRect.size.y / 2.0f
    ));
    stepsText.setPosition(Vector2f(
        window->getSize().x / 2.0f,
        window->getSize().y / 2.0f + 40
    ));
    window->draw(stepsText);
    
    optional<vector<Cell>> pathOpt = maze.findShortestPath();
    if (pathOpt.has_value()) {
        int pathSteps = static_cast<int>(pathOpt.value().size()) - 1;
        Text pathText(*font, "Shortest Path: " + to_string(pathSteps) + " steps", 20);
        pathText.setFillColor(Color(200, 200, 200));
        
        textRect = pathText.getLocalBounds();
        pathText.setOrigin(Vector2f(
            textRect.position.x + textRect.size.x / 2.0f,
            textRect.position.y + textRect.size.y / 2.0f
        ));
        pathText.setPosition(Vector2f(
            window->getSize().x / 2.0f,
            window->getSize().y / 2.0f + 70
        ));
        window->draw(pathText);
    }
    
    Text exitText(*font, "Press ESC to exit", 18);
    exitText.setFillColor(Color(150, 150, 150));
    
    textRect = exitText.getLocalBounds();
    exitText.setOrigin(Vector2f(
        textRect.position.x + textRect.size.x / 2.0f,
        textRect.position.y + textRect.size.y / 2.0f
    ));
    exitText.setPosition(Vector2f(
        window->getSize().x / 2.0f,
        window->getSize().y / 2.0f + 110
    ));
    window->draw(exitText);
    
    window->display();
    
    // Window waiting loop - only responds to ESC key
    while (window->isOpen()) {
        optional<Event> eventOpt;
        while ((eventOpt = window->pollEvent())) {
            Event event = eventOpt.value();
            
            if (event.is<Event::Closed>()) {
                window->close();
                return;
            }
            
            if (event.is<Event::KeyPressed>()) {
                const auto* keyEvent = event.getIf<Event::KeyPressed>();
                if (keyEvent && keyEvent->code == Keyboard::Key::Escape) {
                    window->close();
                    return;
                }
            }
        }
        
        // Keep the window updated while waiting
        window->clear(GameColors::BackgroundColor);
        window->draw(winTitle);
        window->draw(winSubtitle);
        window->draw(timeText);
        window->draw(stepsText);
        if (pathOpt.has_value()) {
            int pathSteps = static_cast<int>(pathOpt.value().size()) - 1;
            Text pathText(*font, "Shortest Path: " + to_string(pathSteps) + " steps", 20);
            pathText.setFillColor(Color(200, 200, 200));
            textRect = pathText.getLocalBounds();
            pathText.setOrigin(Vector2f(
                textRect.position.x + textRect.size.x / 2.0f,
                textRect.position.y + textRect.size.y / 2.0f
            ));
            pathText.setPosition(Vector2f(
                window->getSize().x / 2.0f,
                window->getSize().y / 2.0f + 70
            ));
            window->draw(pathText);
        }
        window->draw(exitText);
        window->display();
    }
}

