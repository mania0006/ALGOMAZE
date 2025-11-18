/*
 * LevelScreen.cpp - Level Selection Screen Implementation
 */

#include "LevelScreen.hpp"
#include "Common.hpp"
#include <SFML/Graphics.hpp>
#include <tuple>

using namespace std;
using namespace sf;

LevelScreen::LevelScreen(RenderWindow* win, Font* f, const string& name)
    : ScreenBase(win, f), playerName(name), selectedLevel(0) {
}

void LevelScreen::draw() {
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
    
    // Draw game title
    Text gameTitle(*font, "ALGOMAZE", 56);
    gameTitle.setFillColor(Color(50, 200, 100));
    gameTitle.setStyle(Text::Style::Bold);
    FloatRect titleBounds = gameTitle.getLocalBounds();
    gameTitle.setOrigin(Vector2f(
        titleBounds.position.x + titleBounds.size.x / 2.f,
        titleBounds.position.y + titleBounds.size.y / 2.f
    ));
    gameTitle.setPosition(Vector2f(size.x / 2.f, 80.f));
    window->draw(gameTitle);
    
    // Display player name
    Text playerGreeting(*font, "Welcome, " + playerName + "!", 28);
    playerGreeting.setFillColor(Color(200, 220, 255));
    playerGreeting.setStyle(Text::Style::Bold);
    FloatRect greetingBounds = playerGreeting.getLocalBounds();
    playerGreeting.setOrigin(Vector2f(
        greetingBounds.position.x + greetingBounds.size.x / 2.f,
        greetingBounds.position.y + greetingBounds.size.y / 2.f
    ));
    playerGreeting.setPosition(Vector2f(size.x / 2.f, 140.f));
    window->draw(playerGreeting);
    
    // Draw subtitle
    Text subtitle(*font, "Choose Your Challenge", 24);
    subtitle.setFillColor(Color(180, 200, 220));
    FloatRect subtitleBounds = subtitle.getLocalBounds();
    subtitle.setOrigin(Vector2f(
        subtitleBounds.position.x + subtitleBounds.size.x / 2.f,
        subtitleBounds.position.y + subtitleBounds.size.y / 2.f
    ));
    subtitle.setPosition(Vector2f(size.x / 2.f, 180.f));
    window->draw(subtitle);
    
    // Level card dimensions
    float cardWidth = 280.f;
    float cardHeight = 200.f;
    float cardSpacing = 30.f;
    float totalWidth = 3 * cardWidth + 2 * cardSpacing;
    float startX = size.x / 2.f - totalWidth / 2.f;
    float cardY = size.y / 2.f - 20.f;
    
    // Level data: [difficulty name, color, description]
    vector<tuple<string, Color, string>> levelData = {
        {"EASY", Color(100, 200, 100), "Simple maze layout\nPerfect for beginners"},
        {"MEDIUM", Color(200, 180, 100), "Complex pathfinding\nMore challenging"},
        {"HARD", Color(200, 100, 100), "Dynamic generation\nComplex maze\nExpert level"}
    };
    
    // Draw level selection cards
    for (int i = 0; i < 3; i++) {
        float cardX = startX + i * (cardWidth + cardSpacing);
        
        // Card shadow
        RectangleShape shadow(Vector2f(cardWidth + 6.f, cardHeight + 6.f));
        shadow.setFillColor(Color(0, 0, 0, 150));
        shadow.setPosition(Vector2f(cardX + 3.f, cardY + 3.f));
        window->draw(shadow);
        
        // Card background
        RectangleShape card(Vector2f(cardWidth, cardHeight));
        card.setFillColor(Color(25, 30, 40));
        card.setOutlineThickness(2.f);
        auto levelColor = get<1>(levelData[i]);
        card.setOutlineColor(levelColor);
        card.setPosition(Vector2f(cardX, cardY));
        window->draw(card);
        
        // Inner glow
        RectangleShape innerGlow(Vector2f(cardWidth - 4.f, cardHeight - 4.f));
        innerGlow.setFillColor(Color::Transparent);
        innerGlow.setOutlineThickness(1.f);
        innerGlow.setOutlineColor(Color(levelColor.r, levelColor.g, levelColor.b, 100));
        innerGlow.setPosition(Vector2f(cardX + 2.f, cardY + 2.f));
        window->draw(innerGlow);
        
        // Level number badge
        CircleShape badge(25.f);
        badge.setFillColor(levelColor);
        badge.setPosition(Vector2f(cardX + cardWidth / 2.f - 25.f, cardY + 15.f));
        window->draw(badge);
        
        Text levelNum(*font, to_string(i + 1), 32);
        levelNum.setFillColor(Color::White);
        levelNum.setStyle(Text::Style::Bold);
        FloatRect numBounds = levelNum.getLocalBounds();
        levelNum.setOrigin(Vector2f(
            numBounds.position.x + numBounds.size.x / 2.f,
            numBounds.position.y + numBounds.size.y / 2.f
        ));
        levelNum.setPosition(Vector2f(cardX + cardWidth / 2.f, cardY + 40.f));
        window->draw(levelNum);
        
        // Difficulty name
        Text difficultyText(*font, get<0>(levelData[i]), 22);
        difficultyText.setFillColor(levelColor);
        difficultyText.setStyle(Text::Style::Bold);
        FloatRect diffBounds = difficultyText.getLocalBounds();
        difficultyText.setOrigin(Vector2f(
            diffBounds.position.x + diffBounds.size.x / 2.f,
            diffBounds.position.y + diffBounds.size.y / 2.f
        ));
        difficultyText.setPosition(Vector2f(cardX + cardWidth / 2.f, cardY + 85.f));
        window->draw(difficultyText);
        
        // Description (split into lines)
        string desc = get<2>(levelData[i]);
        vector<string> descLines;
        size_t pos = 0;
        while ((pos = desc.find('\n')) != string::npos) {
            descLines.push_back(desc.substr(0, pos));
            desc = desc.substr(pos + 1);
        }
        descLines.push_back(desc);
        
        for (size_t j = 0; j < descLines.size(); j++) {
            Text descText(*font, descLines[j], 16);
            descText.setFillColor(Color(180, 200, 220));
            FloatRect descBounds = descText.getLocalBounds();
            descText.setOrigin(Vector2f(
                descBounds.position.x + descBounds.size.x / 2.f,
                descBounds.position.y + descBounds.size.y / 2.f
            ));
            descText.setPosition(Vector2f(
                cardX + cardWidth / 2.f,
                cardY + 115.f + j * 22.f
            ));
            window->draw(descText);
        }
        
        // Key number indicator
        Text keyPrompt(*font, "Press " + to_string(i + 1), 18);
        keyPrompt.setFillColor(Color(150, 180, 200));
        keyPrompt.setStyle(Text::Style::Italic);
        FloatRect keyPromptBounds = keyPrompt.getLocalBounds();
        keyPrompt.setOrigin(Vector2f(
            keyPromptBounds.position.x + keyPromptBounds.size.x / 2.f,
            keyPromptBounds.position.y + keyPromptBounds.size.y / 2.f
        ));
        keyPrompt.setPosition(Vector2f(cardX + cardWidth / 2.f, cardY + cardHeight + 15.f));
        window->draw(keyPrompt);
    }
    
    // Draw instruction text at bottom
    Text instructionText(*font, "Select a level to begin your journey", 20);
    instructionText.setFillColor(Color(150, 180, 200));
    instructionText.setStyle(Text::Style::Italic);
    FloatRect instructionBounds = instructionText.getLocalBounds();
    instructionText.setOrigin(Vector2f(
        instructionBounds.position.x + instructionBounds.size.x / 2.f,
        instructionBounds.position.y + instructionBounds.size.y / 2.f
    ));
    instructionText.setPosition(Vector2f(size.x / 2.f, size.y - 80.f));
    window->draw(instructionText);
    
    // Draw hint text
    Text hintText(*font, "Tip: You can change level anytime with keys 1-3", 16);
    hintText.setFillColor(Color(100, 120, 140));
    FloatRect hintBounds = hintText.getLocalBounds();
    hintText.setOrigin(Vector2f(
        hintBounds.position.x + hintBounds.size.x / 2.f,
        hintBounds.position.y + hintBounds.size.y / 2.f
    ));
    hintText.setPosition(Vector2f(size.x / 2.f, size.y - 50.f));
    window->draw(hintText);
    
    // Draw decorative bottom border
    RectangleShape bottomBorder(Vector2f(static_cast<float>(size.x), 4.f));
    bottomBorder.setFillColor(Color(50, 200, 100));
    bottomBorder.setPosition(Vector2f(0.f, size.y - 4.f));
    window->draw(bottomBorder);
}

optional<GameState> LevelScreen::handleInput(const Event& event) {
    if (event.is<Event::KeyPressed>()) {
        const auto* keyEvent = event.getIf<Event::KeyPressed>();
        if (keyEvent) {
            if (keyEvent->code == Keyboard::Key::Num1 || keyEvent->code == Keyboard::Key::Numpad1) {
                selectedLevel = 1;
                return GameState::GAMEPLAY;
            }
            if (keyEvent->code == Keyboard::Key::Num2 || keyEvent->code == Keyboard::Key::Numpad2) {
                selectedLevel = 2;
                return GameState::GAMEPLAY;
            }
            if (keyEvent->code == Keyboard::Key::Num3 || keyEvent->code == Keyboard::Key::Numpad3) {
                selectedLevel = 3;
                return GameState::GAMEPLAY;
            }
        }
    }
    return nullopt;
}

