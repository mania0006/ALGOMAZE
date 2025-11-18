/*
 * GameScreen.hpp - Gameplay Screen
 */

#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP

#include "ScreenBase.hpp"
#include "Maze.hpp"
#include "Common.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <optional>
#include <vector>

using namespace std;
using namespace sf;

class GameScreen : public ScreenBase {
private:
    Maze& maze;  // Reference to maze model
    const string& playerName;  // Reference to player name
    optional<vector<Cell>> cachedPath;  // Cached shortest path
    int lastPlayerRow, lastPlayerCol;  // Track player position for cache invalidation
    
public:
    GameScreen(RenderWindow* win, Font* f, Maze& m, const string& name);
    void draw() override;
    void drawLegend(int x, int y);
    void drawWinMessage(float finalElapsedTime);
};

#endif // GAMESCREEN_HPP

