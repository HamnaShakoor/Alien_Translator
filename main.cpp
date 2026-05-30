#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
const char english_lower[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
const char english_upper[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
const char alien_lower[26]={'d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c'};
const char alien_upper[26]={'D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C'};
int main()
{
  sf::RenderWindow window(sf::VideoMode(1100, 800), "StellaCode - Earth to Alien");
  enum State { MENU, TRANSLATE, EXIT_SCREEN };
  State currentState = MENU;
  sf::Font font;
  if (!font.loadFromFile("bubbleFont.ttf")) 
  {
    cout << "Error: Font file not found!" << endl;
  }
  sf::Texture backgroundPic;
  if (!backgroundPic.loadFromFile("alienBackground.png")) 
  {
    cout << "Error: background not found!" << endl;
  }
  sf::Sprite backgroundSprite(backgroundPic);
  sf::SoundBuffer bgBuffer;
    sf::Sound bgSound;
    if (!bgBuffer.loadFromFile("gameSound.wav"))
    {
        cout << "Error: gameSound.wav not found!" << endl;
    }
    else
    {
        bgSound.setBuffer(bgBuffer);
        bgSound.setLoop(true);   
        bgSound.setVolume(35);   
        bgSound.play();          
    }
sf::SoundBuffer clickBuffer;
    sf::Sound clickSound;
    if (!clickBuffer.loadFromFile("btnClick.wav"))
    {
        cout << "Error: btnClick.wav not found!" << endl;
    }
    else
    {
        clickSound.setBuffer(clickBuffer);
        clickSound.setVolume(100); 
    }
    sf::Image humanImage;
    if (humanImage.loadFromFile("human.jpg"))
    { 
        sf::Color topLeftColor = humanImage.getPixel(10, 10);
        humanImage.createMaskFromColor(topLeftColor);
        humanImage.createMaskFromColor(sf::Color::White);
    }
    sf::Texture humanPic;
    humanPic.loadFromImage(humanImage);
    sf::Sprite humanSprite(humanPic);
    humanSprite.setScale(0.15f, 0.15f); 
    sf::Image alienImage;
    if (alienImage.loadFromFile("alien.jpg")) 
    { 
        sf::Color topLeftColor = alienImage.getPixel(10, 10);
        alienImage.createMaskFromColor(topLeftColor);
        alienImage.createMaskFromColor(sf::Color::White);
    }
    sf::Texture alienPic;
    alienPic.loadFromImage(alienImage);
    sf::Sprite alienSprite(alienPic);
    alienSprite.setScale(0.04f, 0.04f); 
sf::Texture byeByePic;
if (!byeByePic.loadFromFile("alienBackground.png")) 
{
    cout << "Error: bye_bye_screen not found!" << endl;
}
sf::Sprite byeByeSprite(byeByePic);
  string englishText = "";   
  string translation = "";
  while (window.isOpen())
    {
      sf::Event event; 
      while (window.pollEvent(event))
      {
        if (event.type == sf::Event::Closed)
        {
          window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed)
            {
              sf::Vector2i mousePos = sf::Mouse::getPosition(window);
              if (currentState == MENU)
              {
                if (mousePos.x > 400 && mousePos.x < 640 && mousePos.y > 420 && mousePos.y < 480)
                {
                  clickSound.play();
                  currentState = TRANSLATE; 
                }
              }
              else if (currentState == TRANSLATE)
              {
                 if (mousePos.x > 410 && mousePos.x < 690 && mousePos.y > 550 && mousePos.y < 610)
                 {
                  clickSound.play();
                  englishText = "";    
                  translation = "";   
                 }
                 else if (mousePos.x > 410 && mousePos.x < 690 && mousePos.y > 630 && mousePos.y < 690)
                 {
                    clickSound.play();
                    currentState = EXIT_SCREEN; 
                 }
              }
            }
        if (event.type == sf::Event::TextEntered)
        {
            if (currentState == TRANSLATE)
            {
                char typedChar = static_cast<char>(event.text.unicode);
                if (event.text.unicode == 8) 
                {
                    if (!englishText.empty()) 
                    {
                        englishText.pop_back();
                    }
                }
                else if((typedChar >= 'a' && typedChar <= 'z') || (typedChar >= 'A' && typedChar <= 'Z') || typedChar == ' ' || typedChar==',' || typedChar=='.' || typedChar=='!' || typedChar=='?' ) 
                {
                  if (englishText.length() < 30) 
                 {
                    englishText += typedChar;
                 }
                 else 
                 {
                    cout << "Validation Error: Max 30 characters allowed!" << endl;
                 }
                }
                else 
                {
                    cout << "Invalid Character! Enter again." << endl;
                } 
                translation= ""; 
                for (size_t i = 0; i < englishText.length(); i++) 
                {
                    char c = englishText[i];
                    if (c == ' ') 
                    { 
                        translation += ' ';
                        continue;
                    }
                    if (c == ',') 
                    { 
                        translation += ',';
                        continue;
                    }
                    if (c == '.') 
                    { 
                        translation += '.';
                        continue;
                    }
                    if (c == '!') 
                    { 
                        translation += '!';
                        continue;
                    }
                    if (c == '?') 
                    { 
                        translation += '?';
                        continue;
                    }
                    bool found = false;
                    for (int j = 0; j < 26; j++)
                    {
                        if (c == english_lower[j])
                        {
                            translation += alien_lower[j];
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                    {
                        for (int j = 0; j < 26; j++) 
                        {
                            if (c == english_upper[j]) 
                            {
                                translation += alien_upper[j];
                                break;
                            }
                        }
                    }
                }   
            }
          }
      }
      window.clear();
      window.draw(backgroundSprite);
        if (currentState == MENU)
        {
            sf::Text mainTitle;
            mainTitle.setFont(font);                       
            mainTitle.setString("StellaCode");             
            mainTitle.setCharacterSize(90);                
            mainTitle.setFillColor(sf::Color(45, 30, 95)); 
            mainTitle.setPosition(380, 150);              
            window.draw(mainTitle);                        

            sf::Text subTitle;
            subTitle.setFont(font);
            subTitle.setString("Earth to Alien Language Translator");
            subTitle.setCharacterSize(50);
            subTitle.setFillColor(sf::Color(75, 60, 130)); 
            subTitle.setPosition(250, 280);             
            window.draw(subTitle);

            sf::RectangleShape startButton(sf::Vector2f(240.f, 60.f));
            startButton.setPosition(400, 420);
            startButton.setFillColor(sf::Color(75, 60, 130));
            startButton.setOutlineThickness(3);
            startButton.setOutlineColor(sf::Color::White);
            window.draw(startButton);

            sf::Text buttonText;
            buttonText.setFont(font);
            buttonText.setString("Start Game");
            buttonText.setCharacterSize(36);
            buttonText.setFillColor(sf::Color::White);
            buttonText.setPosition(450, 430);
            window.draw(buttonText);
        }
        else if (currentState == TRANSLATE)
        {
            sf::RectangleShape plainBg(sf::Vector2f(1100.f, 800.f));
            plainBg.setFillColor(sf::Color(230, 220, 245)); 
            window.draw(plainBg);

            sf::Text topHeading;
            topHeading.setFont(font);
            topHeading.setString("Please enter your word or string in English:");
            topHeading.setCharacterSize(40);
            topHeading.setFillColor(sf::Color(45, 30, 95)); // Dark purple text clear dikhne ke liye
            topHeading.setStyle(sf::Text::Bold);
            topHeading.setPosition(240, 50); 
            window.draw(topHeading);

            humanSprite.setPosition(30, 140); 
            window.draw(humanSprite);

            sf::RectangleShape humanBox(sf::Vector2f(550.f, 80.f));
            humanBox.setPosition(310, 200); 
            humanBox.setFillColor(sf::Color(203, 195, 227)); 
            humanBox.setOutlineThickness(3);
            humanBox.setOutlineColor(sf::Color(75, 60, 130)); 
            window.draw(humanBox);

            sf::Text textToShow(englishText + "|", font, 35);
            textToShow.setFillColor(sf::Color::Black);
            textToShow.setPosition(315, 210);
            window.draw(textToShow);


            // --- 4. ALIEN CHARACTER & OUTPUT BOX (RIGHT SIDE) ---
            alienSprite.setPosition(800, 300); 
            window.draw(alienSprite);

            // Alien Output Box (Sketch ke mutabiq thoda cream/light color)
            sf::RectangleShape alienBox(sf::Vector2f(550.f, 80.f));
            alienBox.setPosition(310, 360); 
            alienBox.setFillColor(sf::Color(203, 195, 227));
            alienBox.setOutlineThickness(3);
            alienBox.setOutlineColor(sf::Color(75, 60, 130));
            window.draw(alienBox);

            // Translated output text alien ke box me
            sf::Text translationToShow(translation, font, 35);
            translationToShow.setFillColor(sf::Color(45, 30, 95)); 
            translationToShow.setPosition(315, 370);
            window.draw(translationToShow);


            // --- 5. BUTTONS (CENTER BOTTOM) ---
            // A. CONTINUE BUTTON
            sf::RectangleShape continueBtn(sf::Vector2f(280.f, 60.f));
            continueBtn.setPosition(410, 550); 
            continueBtn.setFillColor(sf::Color(203, 195, 227)); 
            continueBtn.setOutlineThickness(3);
            continueBtn.setOutlineColor(sf::Color(75, 60, 130));
            window.draw(continueBtn);

            sf::Text continueText("CONTINUE", font, 35);
            continueText.setFillColor(sf::Color(45, 30, 95));
            continueText.setStyle(sf::Text::Bold);
            continueText.setPosition(480, 560);
            window.draw(continueText);

            // B. END BUTTON
            sf::RectangleShape endBtn(sf::Vector2f(280.f, 60.f));
            endBtn.setPosition(410, 650); 
            endBtn.setFillColor(sf::Color(203, 195, 227));
            endBtn.setOutlineThickness(3);
            endBtn.setOutlineColor(sf::Color(75, 60, 130));
            window.draw(endBtn);

            sf::Text endText("END", font, 35);
            endText.setFillColor(sf::Color(45, 30, 95));
            endText.setStyle(sf::Text::Bold);
            endText.setPosition(520, 660);
            window.draw(endText);
        }
        else if (currentState == EXIT_SCREEN)
{
    // Sketch ke mutabiq background ko bilkul plain off-white/cream rang diya
    window.draw(backgroundSprite);

    // 1. "BYE BYE!" Text Setup
    sf::Text byeText;
    byeText.setFont(font);
    byeText.setString("BYE BYE!");
    byeText.setCharacterSize(80); // Bada size sketch ki tarah
    byeText.setFillColor(sf::Color(30, 45, 110)); // Sketch jaisa dark blue color
    byeText.setStyle(sf::Text::Bold);
    
    // Center alignment position
    byeText.setPosition(390, 250);
    window.draw(byeText);

    // 2. "Translator is off" Text Setup
    sf::Text offText;
    offText.setFont(font);
    offText.setString("Translator is off");
    offText.setCharacterSize(45); 
    offText.setFillColor(sf::Color(30, 45, 110)); 
    
    // "BYE BYE!" ke bilkul niche center position
    offText.setPosition(400, 370);
    window.draw(offText);

    // Screen ko display karein taake user dekh sake
    window.display();

    // 3. 3 seconds tak screen hold hogi, phir game automatically band ho jayega
    sf::sleep(sf::seconds(5.0f)); 
    window.close();
}
        window.display();

    }
  
}
