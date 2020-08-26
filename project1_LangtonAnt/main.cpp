/************************************************************************
 * * Author: 		Benjamin Hillen
 * * Date: 		1 October 2019
 * * Description: 	Testing file to test Ant class, the menu, and
 * * 			user input validation.
************************************************************************/

#include "Ant.hpp"
#include "validateInt.hpp"
#include "menu.hpp"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
   const int PLAY = 1;

   const int QUIT = 2;

   int menuOption = QUIT;

   bool complete = false; //simulation has not run yet

   cout << "Please note that this program has chosen to participate in "; //text informing user about
   cout << "the extra credit option.\nThe user will be asked if they want "; //the program's specifications
   cout << "the ant to have a random starting location once the simulation"; //including extra credit,
   cout << " has begun to run.\n";					    //edge case handling,
									    //and the step limit
   cout << "Additionally, note that if the ant encounters the edge of the board,";
   cout << " it will turn according to the color of its space,\nbut it will not";
   cout << " advance on that step. It will then turn on the next step and advance";
   cout << " if it is able to.\n";

   cout << "\nFinally, the user should be aware that this program will produce the ";
   cout << "characteristic 'highways' of Langton's Ant\nbetter when over 100 rows and";
   cout << " columns are specified in the set up of the board.\nIt is also suggested ";
   cout << " that the user specify at least 12000 steps in order to see the beginning";
   cout << " of the highway.\n";

   cout << "Please note that the program will not allow you to enter of 300,000 steps";
   cout << " as per the restrictions placed by the rubric.\n";

   /***************************************************************
    * * 			menu(bool)		          *
    * * takes a boolean value indicating whether the main program *
    * * has been run before or not. The function will prompt the  *
    * * user to choose, in this case, to quit or to start the	  *
    * * Langton's Ant simulation. Quitting will return an int of  *
    * * 2, while playing will return an int of value 1, which     *
    * * is used in main() to set the response path of the program.*
   ***************************************************************/
   menuOption = menu(complete);

   if (menuOption == QUIT)
   {
      cout << "Quitting Langton's Ant simulation...\n";

      return 0;
   }

   do //continue to create and run a simulation of Langton's Ant until the
   {  //user decides to quit
      if (menuOption == PLAY)
      {
	 Ant simulation; //create an object from the Ant class

	 /**********************************************************
	  * * 			    startUp()			   *
	  * * informs user about the parameters of the simulation, *
	  * * then takes user input to set up the board by calling *
	  * * the getBoard() method, lets user choose if ant	   *
	  * * starting position is randomized, and how many        *
	  * * steps the ant will take.				   *
	 **********************************************************/ 
	 simulation.startUp();

	 /**********************************************************
	  * * 			    simulate()			   *
	  * * walks the ant through the parameters of Langton's	   *
	  * * Ant algorithm: the ant will advance and then rotate  *
	  * * depending on the color of the space it is on, then   *
	  * * flip the color of that space and advance again.      *
	  * * Edge cases are handled by skipping the advance part  *
	  * * of the step and rotating the ant again before moving *
	  * * to the next step. The board is printed after each    *
	  * * step.						   *
	 **********************************************************/
	 simulation.simulate();

	 complete = true; //mark that the simulation has been run

	 menuOption = menu(complete); //ask the user if the want to play again
      }				      //using a menu

      if (menuOption == QUIT)
      {
	 cout << "Quitting Langton's Ant simulation...\n";

	 return 0;
      }

   } while (menuOption == PLAY);

   return 0;
}
