/*
 * NameScreen.cpp - Name Input Screen Implementation
 */

#include "NameScreen.hpp"
#include "Common.hpp"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

NameScreen::NameScreen(RenderWindow* win, Font* f, string& name)
    : ScreenBase(win, f), playerName(name), namePromptText(*f, "Enter Your Name (Max 15 Chars):", 28) {
    namePromptText.setFillColor(Color::White);
}

void NameScreen::draw() {
    Vector2u size = window->getSize();
    
    // Draw gradient-like background overlay
    RectangleShape shade(Vector2f(static_cast<float>(size.x), static_cast<float>(size.y)));
    shade.setFillColor(Color(15, 15, 25, 245));
    shade.setPosition(Vector2f(0.f, 0.f));
    window->draw(shade);
    
    // Draw decorative border/pattern at top
    RectangleShape topBorder(Vector2f(static_cast<float>(size.x), 4.f));
    topBorder.setFillColor(Color(50, 200, 100));
    topBorder.setPosition(Vector2f(0.f, 0.f));
    window->draw(topBorder);
    
    // Draw decorative pattern lines
    for (int i = 0; i < 3; i++) {
        RectangleShape line(Vector2f(static_cast<float>(size.x), 1.f));
        line.setFillColor(Color(50, 200, 100, 50));
        line.setPosition(Vector2f(0.f, 10.f + i * 15.f));
        window->draw(line);
    }
    
    // Draw game title/logo text
    Text gameTitle(*font, "ALGOMAZE", 56);
    gameTitle.setFillColor(Color(50, 200, 100));
    gameTitle.setStyle(Text::Style::Bold);
    FloatRect titleBounds = gameTitle.getLocalBounds();
    gameTitle.setOrigin(Vector2f(
        titleBounds.position.x + titleBounds.size.x / 2.f,
        titleBounds.position.y + titleBounds.size.y / 2.f
    ));
    gameTitle.setPosition(Vector2f(size.x / 2.f, size.y / 2.f - 200.f));
    window->draw(gameTitle);
    
    // Draw subtitle
    Text subtitle(*font, "Welcome, Player", 24);
    subtitle.setFillColor(Color(200, 200, 220));
    FloatRect subtitleBounds = subtitle.getLocalBounds();
    subtitle.setOrigin(Vector2f(
        subtitleBounds.position.x + subtitleBounds.size.x / 2.f,
        subtitleBounds.position.y + subtitleBounds.size.y / 2.f
    ));
    subtitle.setPosition(Vector2f(size.x / 2.f, size.y / 2.f - 140.f));
    window->draw(subtitle);
    
    // Draw name prompt text
    FloatRect promptBounds = namePromptText.getLocalBounds();
    namePromptText.setOrigin(Vector2f(
        promptBounds.position.x + promptBounds.size.x / 2.f,
        promptBounds.position.y + promptBounds.size.y / 2.f
    ));
    namePromptText.setPosition(Vector2f(size.x / 2.f, size.y / 2.f - 80.f));
    namePromptText.setFillColor(Color(180, 200, 255));
    window->draw(namePromptText);
    
    // Draw professional input box
    float boxWidth = 450.f;
    float boxHeight = 70.f;
    float boxX = size.x / 2.f - boxWidth / 2.f;
    float boxY = size.y / 2.f - 10.f;
    
    // Shadow
    RectangleShape shadow(Vector2f(boxWidth + 6.f, boxHeight + 6.f));
    shadow.setFillColor(Color(0, 0, 0, 150));
    shadow.setPosition(Vector2f(boxX + 3.f, boxY + 3.f));
    window->draw(shadow);
    
    // Input box background
    RectangleShape inputBox(Vector2f(boxWidth, boxHeight));
    inputBox.setFillColor(Color(30, 35, 45));
    inputBox.setOutlineThickness(2.f);
    inputBox.setOutlineColor(Color(50, 200, 100));
    inputBox.setPosition(Vector2f(boxX, boxY));
    window->draw(inputBox);
    
    // Inner glow effect
    RectangleShape innerGlow(Vector2f(boxWidth - 4.f, boxHeight - 4.f));
    innerGlow.setFillColor(Color::Transparent);
    innerGlow.setOutlineThickness(1.f);
    innerGlow.setOutlineColor(Color(50, 200, 100, 100));
    innerGlow.setPosition(Vector2f(boxX + 2.f, boxY + 2.f));
    window->draw(innerGlow);
    
    // Draw player name text inside the box
    string displayName = playerName;
    Text nameText(*font, displayName, 32);
    nameText.setFillColor(Color(220, 255, 220));
    nameText.setStyle(Text::Style::Bold);
    FloatRect nameBounds = nameText.getLocalBounds();
    nameText.setOrigin(Vector2f(
        nameBounds.position.x,
        nameBounds.position.y + nameBounds.size.y / 2.f
    ));
    nameText.setPosition(Vector2f(boxX + 20.f, boxY + boxHeight / 2.f));
    window->draw(nameText);
    
    // Animated blinking cursor
    float cursorBlinkTime = cursorBlinkClock.getElapsedTime().asSeconds();
    bool showCursor = (static_cast<int>(cursorBlinkTime * 2) % 2) == 0;
    
    if (showCursor) {
        float cursorX = boxX + 20.f + nameBounds.size.x;
        if (displayName.empty()) {
            cursorX = boxX + 20.f;
        }
        
        RectangleShape cursor(Vector2f(3.f, 36.f));
        cursor.setFillColor(Color(50, 200, 100));
        cursor.setPosition(Vector2f(cursorX, boxY + (boxHeight - 36.f) / 2.f));
        window->draw(cursor);
    }
    
    // Character count indicator
    string charCount = to_string(playerName.length()) + " / 15";
    Text countText(*font, charCount, 16);
    countText.setFillColor(Color(150, 150, 170));
    FloatRect countBounds = countText.getLocalBounds();
    countText.setOrigin(Vector2f(
        countBounds.position.x + countBounds.size.x,
        countBounds.position.y + countBounds.size.y / 2.f
    ));
    countText.setPosition(Vector2f(boxX + boxWidth - 15.f, boxY + boxHeight / 2.f));
    window->draw(countText);
    
    // Draw instruction text
    Text instructionText(*font, "Press ENTER to continue", 20);
    instructionText.setFillColor(Color(150, 180, 200));
    instructionText.setStyle(Text::Style::Italic);
    FloatRect instructionBounds = instructionText.getLocalBounds();
    instructionText.setOrigin(Vector2f(
        instructionBounds.position.x + instructionBounds.size.x / 2.f,
        instructionBounds.position.y + instructionBounds.size.y / 2.f
    ));
    instructionText.setPosition(Vector2f(size.x / 2.f, size.y / 2.f + 100.f));
    window->draw(instructionText);
    
    // Draw hint text
    Text hintText(*font, "Tip: Use letters, numbers, and spaces only", 16);
    hintText.setFillColor(Color(100, 120, 140));
    FloatRect hintBounds = hintText.getLocalBounds();
    hintText.setOrigin(Vector2f(
        hintBounds.position.x + hintBounds.size.x / 2.f,
        hintBounds.position.y + hintBounds.size.y / 2.f
    ));
    hintText.setPosition(Vector2f(size.x / 2.f, size.y / 2.f + 130.f));
    window->draw(hintText);
    
    // Draw decorative bottom border
    RectangleShape bottomBorder(Vector2f(static_cast<float>(size.x), 4.f));
    bottomBorder.setFillColor(Color(50, 200, 100));
    bottomBorder.setPosition(Vector2f(0.f, size.y - 4.f));
    window->draw(bottomBorder);
}

optional<GameState> NameScreen::handleInput(const Event& event) {
    if (event.is<Event::TextEntered>()) {
        const auto* textEvent = event.getIf<Event::TextEntered>();
        if (textEvent) {
            char c = static_cast<char>(textEvent->unicode);
            
            // Handle Enter key
            if (c == '\r' || c == '\n') {
                if (!playerName.empty()) {
                    return GameState::LEVEL_SELECT;
                }
                return nullopt;
            }
            
            // Handle Backspace
            if (c == '\b' || c == 8) {
                if (!playerName.empty()) {
                    playerName.pop_back();
                }
                return nullopt;
            }
            
            // Handle valid characters
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || 
                (c >= '0' && c <= '9') || c == ' ') {
                if (playerName.length() < 15) {
                    playerName += c;
                }
                return nullopt;
            }
        }
    }
    
    return nullopt;
}

