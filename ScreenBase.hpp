/*
 * ScreenBase.hpp - Abstract base class for all screens
 */

#ifndef SCREENBASE_HPP
#define SCREENBASE_HPP

#include <SFML/Graphics.hpp>
#include <optional>
#include <string>
#include "GameState.hpp"

using namespace std;
using namespace sf;

class ScreenBase {
protected:
    RenderWindow* window;
    Font* font;
    
public:
    ScreenBase(RenderWindow* win, Font* f) : window(win), font(f) {}
    virtual ~ScreenBase() = default;
    
    virtual void draw() = 0;
    virtual optional<GameState> handleInput(const Event& event) { return nullopt; }
};

#endif // SCREENBASE_HPP

