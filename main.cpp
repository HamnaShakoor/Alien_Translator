#include <SFML/Graphics.hpp>
#include<iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "The Translator Quest");
    
    std::vector<std::string> alienDialogue = {"Zorp", "Gleep", "Bork"};
    std::map<std::string, std::string> dictionary = {
        {"Zorp", "Hello"}, {"Gleep", "Danger"}, {"Bork", "Food"}
    };
    
    bool hasTranslationChip = false;

    sf::Font font;
    // Make sure arial.ttf is in your folder!
    if (!font.loadFromFile("arial.ttf")) {
        return -1; 
    }

    sf::Text displayBoard;
    displayBoard.setFont(font);
    displayBoard.setCharacterSize(30);
    displayBoard.setFillColor(sf::Color::Green);
    displayBoard.setPosition(50, 100);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                hasTranslationChip = true;
            }
        }

        std::string fullSentence = "";
        for (const std::string& word : alienDialogue) {
            fullSentence += (hasTranslationChip ? dictionary[word] : word) + " ";
        }

        displayBoard.setString("Alien says: " + fullSentence + "\n\n(Press Space to translate!)");

        window.clear();
        window.draw(displayBoard);
        window.display();
    }
    return 0;
}