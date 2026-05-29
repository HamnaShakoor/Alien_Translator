#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
const char english_lower[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
const char english_upper[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
const char alien_lower[26]={'k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f','g','h','i','j'};
const char alien_upper[26]={'K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J'};
int main()
{
  sf::RenderWindow window(sf::VideoMode(1100, 800), "StellaCode - Earth to Alien");
  enum State { MENU, TRANSLATE, EXIT_SCREEN };
  State currentState = MENU;
  sf::Font font;
  if (!font.loadFromFile("Tangerine-Regular.ttf")) 
  {
    cout << "Error: Font file nahi mili!" << endl;
  }
  sf::Texture backgroundPic;
  if (!backgroundPic.loadFromFile("alienBackground.png")) 
  {
    cout << "Error: bg.png nahi mili!" << endl;
  }
  sf::Sprite backgroundSprite(backgroundPic);
  sf::Texture humanPic;
  humanPic.loadFromFile("human.png");
  sf::Sprite humanSprite(humanPic);
  sf::Texture alienPic;
  alienPic.loadFromFile("alien.png");
  sf::Sprite alienSprite(alienPic);
  string userInput = "";   
  string alienOutput = "";
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
              if (currentState == MENU)
              {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (mousePos.x > 400 && mousePos.x < 600 && mousePos.y > 450 && mousePos.y < 510)
                {
                  currentState = TRANSLATE; 
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
            mainTitle.setStyle(sf::Text::Bold);            
            mainTitle.setPosition(400, 150);              
            window.draw(mainTitle);                        

            sf::Text subTitle;
            subTitle.setFont(font);
            subTitle.setString("Earth to Alien Language Translator");
            subTitle.setCharacterSize(50);
            subTitle.setFillColor(sf::Color(75, 60, 130)); 
            subTitle.setStyle(sf::Text::Bold);
            subTitle.setPosition(300, 280);             
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
            buttonText.setStyle(sf::Text::Bold);
            buttonText.setPosition(450, 430);
            window.draw(buttonText);
        }
        else if (currentState == TRANSLATE)
        {
            // 👉 Agle step mein hum yahan translation screen draw karenge!
        }
        window.display();

    }
  char choice;
  do
    {
    string text;
    while(true)
    {
      cout<<" Please enter the your word or string in English Language: ";
      getline(cin, text);
      bool correctInput=true;
      if(text.length()==0)
      {
        cout<<"You entered nothing. Enter Again: ";
        continue;
      }
      for (int i = 0; i < text.length(); i++)
      {
         char c=text[i];
         if(c==' ')
         {
           continue;
         }
         bool found = false;
         for(int j = 0; j < 26; j++)
         {
            if(c == english_lower[j] || c == english_upper[j])
            {
                found = true;
                break;
            }
        }
        if(!found)
        {
            correctInput = false;
            break;
        }
     }
     if(correctInput==true)
     {
        break;
     }
     else
     {
        cout<<endl;
        cout<<"Invalid input. Try Agian."<<endl;
     }
    }
    cout<<"Valid Input";
    cout<<endl;
    cout<<"Translated in Alien's Language: "<<endl;
    string translation;
    int length=text.length();
    for (int i=0; i<length; i++)
      {
         char c=text[i];
         if(c==' ')
         { 
          translation +=' ';
          continue;
         }
         bool translated = false;
         for(int j = 0; j < 26; j++)
         {
            if(c == english_lower[j])
            {
              translation +=alien_lower[j];
              translated = true;
              break;
            }
         }
         if(translated==false)
         {
          for(int j = 0; j < 26; j++)
          {
            if(c == english_upper[j])
            {
              translation+=alien_upper[j];
              translated = true;
              break;
            }
          }
         }
      }
      cout<<translation;
      cout<<endl<<endl;
      cout << "\n\nDo you want to continue? (Y/N): ";
      cin >> choice;
      if(choice == 'N' || choice == 'n')
       {
         break;
       }
      cin.ignore();
      } 
       while(choice == 'Y' || choice == 'y');
        cout << "\nProgram Ended.";
        return 0;
}