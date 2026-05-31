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
{ //setting window size
  sf::RenderWindow window(sf::VideoMode(1100, 800), "StellaCode - Earth to Alien");
  //total number and name of screens
  enum State { MENU, CHOICE, TRANSLATE_H2A, TRANSLATE_A2H, MANUAL, EXIT_SCREEN };
  State currentState = MENU;
  //setting the font
  sf::Font font;
  if (!font.loadFromFile("bubbleFont.ttf")) 
  {
    cout << "Error: Font file not found!" << endl;
  }
  //setting bg pic
  sf::Texture backgroundPic;
  if (!backgroundPic.loadFromFile("alienBackground.png")) 
  {
    cout << "Error: background not found!" << endl;
  }
  sf::Sprite backgroundSprite(backgroundPic);
  //adding sound for game
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
//adding sound for clicking btns
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
//adding human image
sf::Image humanImage;
if (humanImage.loadFromFile("human.jpg"))
{ 
    //removing bg of pic
    sf::Color topLeftColor = humanImage.getPixel(10, 10);
    humanImage.createMaskFromColor(topLeftColor);
    humanImage.createMaskFromColor(sf::Color::White);
}
sf::Texture humanPic;
humanPic.loadFromImage(humanImage);
sf::Sprite humanSprite(humanPic);
humanSprite.setScale(0.15f, 0.15f); 
//adding alien pic
sf::Image alienImage;
if (alienImage.loadFromFile("alien.jpg")) 
{ 
    //removing bg of pic
    sf::Color topLeftColor = alienImage.getPixel(10, 10);
    alienImage.createMaskFromColor(topLeftColor);
    alienImage.createMaskFromColor(sf::Color::White);
}
sf::Texture alienPic;
alienPic.loadFromImage(alienImage);
sf::Sprite alienSprite(alienPic);
alienSprite.setScale(0.04f, 0.04f); 
//adding bg pic for last screen same as start screen
sf::Texture byeByePic;
if (!byeByePic.loadFromFile("alienBackground.png")) 
{
    cout << "Error: bye_bye_screen not found!" << endl;
}
sf::Sprite byeByeSprite(byeByePic);
//initializing some variables
string typedText = "";   
string translation = "";
string manualContent = ""; 
//open txt file and read from it
ifstream file("manual.txt");
if (file.is_open()) 
{
    string lineText;
    while (getline(file, lineText)) 
    {
        manualContent += lineText + "\n"; 
    }
    file.close();
} 
else 
{
    cout << "Error: manual.txt file not found!" << endl;
    manualContent = "Manual file loading failed!";
}
//opening window
while (window.isOpen())
{
    sf::Event event; 
    //setting the events of mouse and keyboard
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
          window.close();
        }
        //mouse events
        if (event.type == sf::Event::MouseButtonPressed)
            {
              sf::Vector2i mousePos = sf::Mouse::getPosition(window);
              //event 1 for start game btn
              if (currentState == MENU)
              {
                if (mousePos.x > 400 && mousePos.x < 640 && mousePos.y > 420 && mousePos.y < 480)
                {
                  clickSound.play();
                  currentState = CHOICE; 
                }
              }
              //event 2 for choices btn
              else if(currentState == CHOICE)
              {
                if (mousePos.x > 410 && mousePos.x < 710 && mousePos.y > 450 && mousePos.y < 530) {
                        clickSound.play();
                        typedText = "";
                        translation = "";
                        currentState = TRANSLATE_A2H;
                    }
                    else if (mousePos.x > 410 && mousePos.x < 710 && mousePos.y > 350 && mousePos.y < 430) {
                        clickSound.play();
                        typedText = ""; 
                        translation = "";
                        currentState = TRANSLATE_H2A;
                    }
              }
              //event 3 for btns on H2A screen
              else if (currentState == TRANSLATE_H2A)
              {
                 if (mousePos.x > 410 && mousePos.x < 690 && mousePos.y > 550 && mousePos.y < 610)
                 {
                  clickSound.play();
                  typedText = "";    
                  translation = "";   
                 }
                 else if (mousePos.x > 410 && mousePos.x < 710 && mousePos.y > 630 && mousePos.y < 690)
                 {
                   clickSound.play();
                   currentState = CHOICE; 
                 }
                 else if (mousePos.x > 410 && mousePos.x < 690 && mousePos.y > 710 && mousePos.y < 770)
                 {
                    clickSound.play();
                    currentState = EXIT_SCREEN; 
                 }
              }
              //event 4 for btns on A2H screen
              else if (currentState == TRANSLATE_A2H)
              {
                 if (mousePos.x > 410 && mousePos.x < 690 && mousePos.y > 550 && mousePos.y < 610)
                 {
                  clickSound.play();
                  typedText = "";    
                  translation = "";   
                 }
                 else if (mousePos.x > 410 && mousePos.x < 690 && mousePos.y > 630 && mousePos.y < 690)
                 {
                    clickSound.play();
                    currentState = CHOICE; 
                 }
                 else if (mousePos.x > 410 && mousePos.x < 690 && mousePos.y > 710 && mousePos.y < 770)
                 {
                    clickSound.play();
                    currentState = EXIT_SCREEN; 
                 }
                 else if (mousePos.x > 50 && mousePos.x < 330 && mousePos.y > 700 && mousePos.y < 760)
                 {
                   clickSound.play();
                   currentState = MANUAL;
                 }
            }
            //event 5 for back btn on manual screen
            else if (currentState == MANUAL)
            {
              if (mousePos.x > 50 && mousePos.x < 250 && mousePos.y > 710 && mousePos.y < 760)
              {
                clickSound.play();
                currentState = TRANSLATE_A2H; 
              }
            }
        }
        //keyboards events
        if (event.type == sf::Event::TextEntered)
        {
            //event 1 for entering text on screen H2A
            if (currentState == TRANSLATE_H2A)
            {
                char typedChar = static_cast<char>(event.text.unicode);
                if (event.text.unicode == 8) 
                {
                    if (!typedText.empty()) 
                    {
                        typedText.pop_back();
                    }
                }
                else if((typedChar >= 'a' && typedChar <= 'z') || (typedChar >= 'A' && typedChar <= 'Z') || typedChar == ' ' || typedChar==',' || typedChar=='.' || typedChar=='!' || typedChar=='?' ) 
                {
                  if (typedText.length() < 30) 
                 {
                    typedText += typedChar;
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
                for (size_t i = 0; i < typedText.length(); i++) 
                {
                    char c = typedText[i];
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
            //event 2 for entering text on screen A2H
            if (currentState == TRANSLATE_A2H)
            {
                char typedChar = static_cast<char>(event.text.unicode);
                if (event.text.unicode == 8) 
                {
                    if (!typedText.empty()) 
                    {
                        typedText.pop_back();
                    }
                }
                else if((typedChar >= 'a' && typedChar <= 'z') || (typedChar >= 'A' && typedChar <= 'Z') || typedChar == ' ' || typedChar==',' || typedChar=='.' || typedChar=='!' || typedChar=='?' ) 
                {
                  if (typedText.length() < 30) 
                 {
                    typedText += typedChar;
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
                for (size_t i = 0; i < typedText.length(); i++) 
                {
                    char c = typedText[i];
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
                        if (c == alien_lower[j])
                        {
                            translation += english_lower[j];
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                    {
                        for (int j = 0; j < 26; j++) 
                        {
                            if (c == alien_upper[j]) 
                            {
                                translation += english_upper[j];
                                break;
                            }
                        }
                    }
                }   
            }
        }
      }
      window.clear();
      //setting the pics, text boxes and text on each screen
      //setting bg for start screen
      window.draw(backgroundSprite);
      //screen 1 objects
        if (currentState == MENU)
        {
            //main text
            sf::Text mainTitle;
            mainTitle.setFont(font);                       
            mainTitle.setString("StellaCode");             
            mainTitle.setCharacterSize(90);                
            mainTitle.setFillColor(sf::Color(45, 30, 95)); 
            mainTitle.setPosition(380, 150);              
            window.draw(mainTitle);                        

            //sub text
            sf::Text subTitle;
            subTitle.setFont(font);
            subTitle.setString("Earth to Alien Language Translator");
            subTitle.setCharacterSize(50);
            subTitle.setFillColor(sf::Color(75, 60, 130)); 
            subTitle.setPosition(250, 280);             
            window.draw(subTitle);

            //btn designing
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
        //screen 2 objects
        else if(currentState == CHOICE)
        {  
            //bg pic
            window.draw(backgroundSprite);

            //btns designing 
            sf::RectangleShape choiceH2ABtn(sf::Vector2f(300.f, 80.f));
            choiceH2ABtn.setPosition(410, 350); 
            choiceH2ABtn.setFillColor(sf::Color(75, 60, 130)); 
            choiceH2ABtn.setOutlineThickness(3);
            choiceH2ABtn.setOutlineColor(sf::Color::White);
            window.draw(choiceH2ABtn);

            sf::Text choiceH2AText("Human TO Alien", font, 36);
            choiceH2AText.setFillColor(sf::Color::White);
            choiceH2AText.setPosition(440, 370);
            window.draw(choiceH2AText);

            sf::RectangleShape choiceA2HBtn(sf::Vector2f(300.f, 80.f));
            choiceA2HBtn.setPosition(410, 450); 
            choiceA2HBtn.setFillColor(sf::Color(75, 60, 130)); 
            choiceA2HBtn.setOutlineThickness(3);
            choiceA2HBtn.setOutlineColor(sf::Color::White);
            window.draw(choiceA2HBtn);

            sf::Text choiceA2HText("Alien To Human", font, 36);
            choiceA2HText.setFillColor(sf::Color::White);
            choiceA2HText.setPosition(440, 470);
            window.draw(choiceA2HText);

        }
        //screen 3 objects when click on H2A
        else if (currentState == TRANSLATE_H2A)
        {
            //bg setting
            sf::RectangleShape plainBg(sf::Vector2f(1100.f, 800.f));
            plainBg.setFillColor(sf::Color(230, 220, 245)); 
            window.draw(plainBg);

            //heading text 
            sf::Text topHeading;
            topHeading.setFont(font);
            topHeading.setString("Please enter your word or string in English:");
            topHeading.setCharacterSize(40);
            topHeading.setFillColor(sf::Color(45, 30, 95)); 
            topHeading.setStyle(sf::Text::Bold);
            topHeading.setPosition(240, 50); 
            window.draw(topHeading);

            //human pic setting
            humanSprite.setPosition(30, 140); 
            window.draw(humanSprite);

            //human text box setting
            sf::RectangleShape humanBox(sf::Vector2f(550.f, 80.f));
            humanBox.setPosition(310, 200); 
            humanBox.setFillColor(sf::Color(203, 195, 227)); 
            humanBox.setOutlineThickness(3);
            humanBox.setOutlineColor(sf::Color(75, 60, 130)); 
            window.draw(humanBox);

            sf::Text textToShow(typedText + "|", font, 35);
            textToShow.setFillColor(sf::Color::Black);
            textToShow.setPosition(315, 210);
            window.draw(textToShow);

            //line showing translated text setting
            sf::Text line;
            line.setFont(font);
            line.setString("Translated text:");
            line.setCharacterSize(25);
            line.setFillColor(sf::Color(45, 30, 95)); 
            line.setStyle(sf::Text::Bold);
            line.setPosition(290, 310); 
            window.draw(line);

            //alien pic setting
            alienSprite.setPosition(800, 300); 
            window.draw(alienSprite);

            //alien text box setting
            sf::RectangleShape alienBox(sf::Vector2f(550.f, 80.f));
            alienBox.setPosition(310, 360); 
            alienBox.setFillColor(sf::Color(203, 195, 227));
            alienBox.setOutlineThickness(3);
            alienBox.setOutlineColor(sf::Color(75, 60, 130));
            window.draw(alienBox);

            sf::Text translationToShow(translation, font, 35);
            translationToShow.setFillColor(sf::Color(45, 30, 95)); 
            translationToShow.setPosition(315, 370);
            window.draw(translationToShow);

            //three btns continue, back and end settings
            sf::RectangleShape continueBtn(sf::Vector2f(280.f, 60.f));
            continueBtn.setPosition(410, 550); 
            continueBtn.setFillColor(sf::Color(203, 195, 227)); 
            continueBtn.setOutlineThickness(3);
            continueBtn.setOutlineColor(sf::Color(75, 60, 130));
            window.draw(continueBtn);

            sf::Text continueText("CONTINUE", font, 35);
            continueText.setFillColor(sf::Color(45, 30, 95));
            continueText.setStyle(sf::Text::Bold);
            continueText.setPosition(470, 560);
            window.draw(continueText);

            sf::RectangleShape backBtn(sf::Vector2f(280.f, 60.f));
            backBtn.setPosition(410, 620); 
            backBtn.setFillColor(sf::Color(203, 195, 227)); 
            backBtn.setOutlineThickness(3);
            backBtn.setOutlineColor(sf::Color(75, 60, 130));
            window.draw(backBtn);

            sf::Text backText("BACK", font, 35);
            backText.setFillColor(sf::Color(45, 30, 95));
            backText.setStyle(sf::Text::Bold);
            backText.setPosition(510, 625);
            window.draw(backText);

            sf::RectangleShape endBtn(sf::Vector2f(280.f, 60.f));
            endBtn.setPosition(410, 690); 
            endBtn.setFillColor(sf::Color(203, 195, 227));
            endBtn.setOutlineThickness(3);
            endBtn.setOutlineColor(sf::Color(75, 60, 130));
            window.draw(endBtn);

            sf::Text endText("END", font, 35);
            endText.setFillColor(sf::Color(45, 30, 95));
            endText.setStyle(sf::Text::Bold);
            endText.setPosition(520, 700);
            window.draw(endText);
        }
        //screen 4 objects when A2h btn click
        else if (currentState == TRANSLATE_A2H)
        {
            //bg pic setting
            sf::RectangleShape plainBg(sf::Vector2f(1100.f, 800.f));
            plainBg.setFillColor(sf::Color(230, 220, 245)); 
            window.draw(plainBg);

            //top heading setting
            sf::Text topHeading;
            topHeading.setFont(font);
            topHeading.setString("Please enter your word or string in Alien's Language:");
            topHeading.setCharacterSize(40);
            topHeading.setFillColor(sf::Color(45, 30, 95)); 
            topHeading.setStyle(sf::Text::Bold);
            topHeading.setPosition(200, 50); 
            window.draw(topHeading);

            //alien pic setting
            alienSprite.setPosition(30, 140); 
            window.draw(alienSprite);

            // alien text box setting
            sf::RectangleShape alienBox(sf::Vector2f(550.f, 80.f));
            alienBox.setPosition(310, 200); 
            alienBox.setFillColor(sf::Color(203, 195, 227)); 
            alienBox.setOutlineThickness(3);
            alienBox.setOutlineColor(sf::Color(75, 60, 130)); 
            window.draw(alienBox);

            sf::Text textToShow(typedText + "|", font, 35);
            textToShow.setFillColor(sf::Color::Black);
            textToShow.setPosition(315, 210);
            window.draw(textToShow);

            //line showing translated text setting
            sf::Text line;
            line.setFont(font);
            line.setString("Translated text:");
            line.setCharacterSize(25);
            line.setFillColor(sf::Color(45, 30, 95)); 
            line.setStyle(sf::Text::Bold);
            line.setPosition(290, 310); 
            window.draw(line);

            //human pic setting
            humanSprite.setPosition(820, 300); 
            window.draw(humanSprite);

            //human text box setting
            sf::RectangleShape humanBox(sf::Vector2f(550.f, 80.f));
            humanBox.setPosition(310, 360); 
            humanBox.setFillColor(sf::Color(203, 195, 227));
            humanBox.setOutlineThickness(3);
            humanBox.setOutlineColor(sf::Color(75, 60, 130));
            window.draw(humanBox);

            sf::Text translationToShow(translation, font, 35);
            translationToShow.setFillColor(sf::Color(45, 30, 95)); 
            translationToShow.setPosition(315, 370);
            window.draw(translationToShow);

            //four btns continue, back, manual and end settings
            sf::RectangleShape continueBtn(sf::Vector2f(280.f, 60.f));
            continueBtn.setPosition(410, 550); 
            continueBtn.setFillColor(sf::Color(203, 195, 227)); 
            continueBtn.setOutlineThickness(3);
            continueBtn.setOutlineColor(sf::Color(75, 60, 130));
            window.draw(continueBtn);

            sf::Text continueText("CONTINUE", font, 35);
            continueText.setFillColor(sf::Color(45, 30, 95));
            continueText.setStyle(sf::Text::Bold);
            continueText.setPosition(470, 560);
            window.draw(continueText);

            sf::RectangleShape backBtn(sf::Vector2f(280.f, 60.f));
            backBtn.setPosition(410, 620); 
            backBtn.setFillColor(sf::Color(203, 195, 227)); 
            backBtn.setOutlineThickness(3);
            backBtn.setOutlineColor(sf::Color(75, 60, 130));
            window.draw(backBtn);

            sf::Text backText("BACK", font, 35);
            backText.setFillColor(sf::Color(45, 30, 95));
            backText.setStyle(sf::Text::Bold);
            backText.setPosition(510, 625);
            window.draw(backText);

            sf::RectangleShape manualBtn(sf::Vector2f(280.f, 60.f));
            manualBtn.setPosition(50, 700); 
            manualBtn.setFillColor(sf::Color(203, 195, 227)); 
            manualBtn.setOutlineThickness(3);
            manualBtn.setOutlineColor(sf::Color(75, 60, 130));
            window.draw(manualBtn);

            sf::Text manualText("MANUAL", font, 35);
            manualText.setFillColor(sf::Color(45, 30, 95));
            manualText.setStyle(sf::Text::Bold);
            manualText.setPosition(120, 710);
            window.draw(manualText);

            sf::RectangleShape endBtn(sf::Vector2f(280.f, 60.f));
            endBtn.setPosition(410, 690); 
            endBtn.setFillColor(sf::Color(203, 195, 227));
            endBtn.setOutlineThickness(3);
            endBtn.setOutlineColor(sf::Color(75, 60, 130));
            window.draw(endBtn);

            sf::Text endText("END", font, 35);
            endText.setFillColor(sf::Color(45, 30, 95));
            endText.setStyle(sf::Text::Bold);
            endText.setPosition(520, 700);
            window.draw(endText);
        }
        //screen 5 when manual btn is clicked
        else if (currentState == MANUAL)
        {
            //bg pic setting
            sf::RectangleShape plainBg(sf::Vector2f(1100.f, 800.f));
            plainBg.setFillColor(sf::Color(230, 220, 245)); 
            window.draw(plainBg);

            //main heading text
            sf::Text manualTitle("ALIEN DICTIONARY & MANUAL", font, 45);
            manualTitle.setFillColor(sf::Color(45, 30, 95));
            manualTitle.setStyle(sf::Text::Bold);
            manualTitle.setPosition(250, 40);
            window.draw(manualTitle);

            //sunb text heading
            sf::Text subTitle("Use these meaningful alien words for translation:", font, 24);
            subTitle.setFillColor(sf::Color(75, 60, 130));
            subTitle.setPosition(280, 100);
            window.draw(subTitle);

            //file data which we read settings
            sf::Text fileDataText(manualContent, font, 22);
            fileDataText.setFillColor(sf::Color::Black);
            fileDataText.setPosition(270, 170); 
            fileDataText.setLineSpacing(1.2f);
            window.draw(fileDataText);

            //back by=tn setting
            sf::RectangleShape manualBackBtn(sf::Vector2f(200.f, 50.f));
            manualBackBtn.setPosition(50, 710);
            manualBackBtn.setFillColor(sf::Color(75, 60, 130));
            manualBackBtn.setOutlineThickness(2);
            manualBackBtn.setOutlineColor(sf::Color::White);
            window.draw(manualBackBtn);

            sf::Text mBackText("BACK", font, 28);
            mBackText.setFillColor(sf::Color::White);
            mBackText.setStyle(sf::Text::Bold);
            mBackText.setPosition(110, 718);
            window.draw(mBackText);
        }
        //screen 6 when end btn is clicked
        else if (currentState == EXIT_SCREEN)
        {
            //bg setting
            window.draw(backgroundSprite);

            //text setting
            sf::Text byeText;
            byeText.setFont(font);
            byeText.setString("BYE BYE!");
            byeText.setCharacterSize(80); 
            byeText.setFillColor(sf::Color(30, 45, 110)); 
            byeText.setStyle(sf::Text::Bold);
            byeText.setPosition(390, 250);
            window.draw(byeText);

            //sub text setting
            sf::Text offText;
            offText.setFont(font);
            offText.setString("Translator is off");
            offText.setCharacterSize(45); 
            offText.setFillColor(sf::Color(30, 45, 110)); 
            offText.setPosition(400, 370);

            //closing window after 5 sec
            window.draw(offText);
            window.display();
            sf::sleep(sf::seconds(5.0f)); 
            window.close();
        }
        window.display();
    }
}


