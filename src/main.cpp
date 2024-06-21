#include <iostream>
#include <stdlib.h>
#include "suggestion_system.hpp"
#include "SFML/Graphics.hpp"


void tryLoadFont(sf::Font& font, std::string path)
{
    if (!font.loadFromFile(path))
    {
        std::cout << "Error loading the font file" << std::endl;
        system("pause");
    }
}

void handleTextCompletion(sf::Text& regularText, sf::Text& suggestionText, std::string currentCommand, SuggestionSystem* suggestionSystem) {
    std::vector<std::string> suggestions = suggestionSystem->getSuggestions(
        currentCommand,
        true,
        false);

    if (suggestions.empty()) {
        suggestionText.setString("");
        return;
    }

    suggestionText.setString(suggestions[0]);
    suggestionText.setPosition(regularText.findCharacterPos(
        regularText.getString()[regularText.getString().getSize() - 1])
    );
}

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(800, 800),
        "Shapes");
    window.setFramerateLimit(60); // Set the framerate limit to 60 FPS
    sf::Event e;

    SuggestionSystem* suggestionSystem = new SuggestionSystem();
    std::vector<std::string> functions = { "test", "delete", "start_game", "destroy", "enter_zone", "deinitialize", "remove", "stop", "run" };
    suggestionSystem->insertMultipleWordsIntoTree(functions);

    sf::Text textHolder;
    sf::Text suggestionText;
    sf::Font font;
    
    tryLoadFont(font, "./8bitfont.ttf");

    textHolder.setFont(font);
    suggestionText.setFont(font);

    textHolder.setPosition(sf::Vector2f(50.f, 50.f));
    suggestionText.setFillColor(sf::Color(211, 211, 100));
   
    std::string currentCommandWritten;

    // Main loop
    while (window.isOpen()) {
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
            }

            if (e.type == sf::Event::TextEntered) {
                if (e.text.unicode < 128) {
                    char enteredChar = static_cast<char>(e.text.unicode);

                    if (enteredChar == '\b') { // Handle backspace
                        if (!currentCommandWritten.empty()) {
                            currentCommandWritten.pop_back();
                            textHolder.setString(currentCommandWritten);
                            handleTextCompletion(textHolder, suggestionText, currentCommandWritten, suggestionSystem);
                        }
                    }
                    else {
                        currentCommandWritten += enteredChar;
                        textHolder.setString(currentCommandWritten);

                        handleTextCompletion(textHolder, suggestionText, currentCommandWritten, suggestionSystem);
                    }
                }
            }
        }

        // ===== CLEAR =======
        window.clear(sf::Color::Black);

        // ===== DRAW ========
        window.draw(suggestionText);
        window.draw(textHolder);

        // ===== DISPLAY =====
        window.display();
    }

    return EXIT_SUCCESS;
}