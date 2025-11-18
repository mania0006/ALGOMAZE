
/*
 * LevelScreen.hpp - Level Selection Screen
 */

#ifndef LEVELSCREEN_HPP
#define LEVELSCREEN_HPP

#include "ScreenBase.hpp"
#include "GameState.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <optional>

using namespace std;
using namespace sf;

class LevelScreen : public ScreenBase {
private:
    const string& playerName;  // Reference to player name
    
public:
    LevelScreen(RenderWindow* win, Font* f, const string& name);
    void draw() override;
    optional<GameState> handleInput(const Event& event) override;
    
    // Returns selected level (1-3) when level is selected
    int getSelectedLevel() const { return selectedLevel; }
    
private:
    int selectedLevel = 0;  // 0 means no selection yet
};

#endif // LEVELSCREEN_HPP

