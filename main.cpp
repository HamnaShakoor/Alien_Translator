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
    string text;
    while(true)
    {
      cout<<"Please enter the your word or string in Alien Language: ";
      getline(cin, text);
      cout<<endl;
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
          // alien lower check
         for(int j = 0; j < 26; j++)
         {
            if(c == alien_lower[j] || c == alien_upper[j])
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
        cout<<"Invalid input. Try Agian.";
     }
    }
    
    cout<<"Valid Input";
}