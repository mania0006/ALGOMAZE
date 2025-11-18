/*
 * NameScreen.hpp - Name Input Screen
 */

#ifndef NAMESCREEN_HPP
#define NAMESCREEN_HPP

#include "ScreenBase.hpp"
#include "GameState.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <optional>

using namespace std;
using namespace sf;

class NameScreen : public ScreenBase {
private:
    string& playerName;  // Reference to player name (owned by GameEngine)
    Clock cursorBlinkClock;
    Text namePromptText;
    
public:
    NameScreen(RenderWindow* win, Font* f, string& name);
    void draw() override;
    optional<GameState> handleInput(const Event& event) override;
};

#endif // NAMESCREEN_HPP

