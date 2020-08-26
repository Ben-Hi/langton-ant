/***************************************************************************
 * * Program name: 	Lab1
 * * Author: 		Benjamin Hillen
 * * Date: 		30 September 2019
 * * Description: 	Takes by value a string, then iterates over each
 * * 			character in the string and provides an error 
 * * 			message if any character is not a digit from 0 to 9,
 * * 			then prompts the user to re-enter their input until
 * * 			an all integer input string is provided.
***************************************************************************/

#include "validateInt.hpp"
#include <iostream>
#include <string>
#include <cctype>

void validateInt(std::string& userInput)
{
   bool notAllInts = false;

   do
   {
      notAllInts = false; //assume user entered only integers

      for (char& data : userInput) //check if any entered characters are not integers
      {
         if (!std::isdigit(data) || data == ' ')
         {
   	    notAllInts = true;
         }
      }

      if (notAllInts || userInput == "") //if the input was not only integers, ask for input again
      {
	 std::cout << "Error, please enter only positive integers\n";

         getline(std::cin, userInput);

	 notAllInts = true;
      }
   } while(notAllInts); //continue to validate input until it consists of only integers
}
