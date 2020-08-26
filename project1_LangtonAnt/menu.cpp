/************************************************************************
 * * Author: 		Benjamin Hillen
 * * Date: 		1 October 2019
 * * Description: 	Declaration of Menu class	
************************************************************************/

#include "menu.hpp"
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;

int menu(bool complete)
{
   const std::string QUIT = "2";

   const std::string PLAY = "1";

   std::string userInput = ""; //used to validate user input

   int option = 0;

   if (!complete) //runs if simulation has not been previously run
   {
      cout << "1. Start Langton's Ant simulation" << endl;
      cout << "2. Quit" << endl;

      do //ask user to choose menu option, validate until option is 1 or 2
      {
	 getline(cin, userInput);

	 if (userInput != PLAY && userInput != QUIT)
	 {
	    cout << "Error: Please enter only 1 or 2.\n";
	 }
      } while (userInput != PLAY && userInput != QUIT);

      option = stoi(userInput);
      
      return option;
   }

   else if (complete) //runs if simulation has been run before
   {
     option = 0;

     cout << endl << "1. Play Again" << endl;
     cout << "2. Quit" << endl;

     do //ask user to choose menu option, validate until option is 1 or 2
     {
	getline(cin, userInput);

	if (userInput != PLAY && userInput != QUIT)
	{
	   cout << "Error: Please enter only 1 or 2.\n";
	}
     } while (userInput != PLAY && userInput != QUIT);

     option = stoi(userInput);

     return option;
   }

   else
   {
      cout << "Error: please choose to start the simulation or to quit the program.\n";

      menu(complete); //present the menu until user chooses to quit or play
   }
}
