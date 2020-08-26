/**************************************************************************
 * * Program name: 	Project1
 * * Author: 		Benjamin Hillen
 * * Date: 		7 October 2019
 * * Description: 	Definition of public member functions of the Ant
 * * 			class.
**************************************************************************/

#include "Ant.hpp"
#include "validateInt.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#define STEPLIMIT 300000 //program won't allow user to go over 300,000 steps

using std::cout;
using std::cin;
using std::endl;
using std::string;

Ant::Ant()
{
   const int UP = 0;

   antXCoord = 0;

   antYCoord = 0;

   rows = 0;

   columns = 0;

   antOrientation = UP;

   steps = 0;

   board = nullptr;
}

/************************************************
 * * ~Ant() destructor deallocates memory 
 * * assigned to the board pointer array upon
 * * execution.
************************************************/
Ant::~Ant()
{
   for (int i = 0; i < rows; i++)
   {
      delete [] board[i];
   }

   delete [] board;
}

/**************************************************
 * *		     void setBoard()
 * * Prompts the user to define the rows and 
 * * columns of the board and validates the input
 * * by calling validateInt().
**************************************************/
void Ant::setBoard()
{
   const char WHITE = ' ';

   string userInput = "";

   do //force user to enter valid row and column integers
   {
      cout << "How many rows would you like?\n"; //user inputs rows

      getline(cin, userInput);

      validateInt(userInput); //input must only consist of integers

      rows = stoi(userInput);

      cout << "And how many columns would you like?\n"; //user inputs columns

      getline(cin, userInput);

      validateInt(userInput);

      columns = stoi(userInput);

      if (rows == 0 || columns == 0) //provide error message if user enters 0 for either
      {				     //rows or columns of the board
	 cout << "Error: you tried to create a board with either 0 rows or 0";
	 cout << " columns. Please enter at least 1 when asked for rows and";
	 cout << " columns.\n";
      }
   } while (rows == 0 || columns == 0); //prevents a core dump if user enters in 0

   board = new char*[rows];

   for (int i = 0; i < rows; i++) //create a dynamic 2D board
   {
      board[i] = new char[columns];
   }

   for (int i = 0; i < rows; i++) //start the board as all white
   {
      for (int j = 0; j < columns; j++)
      {
	 board[i][j] = WHITE;
      }
   }

   cout << "The board has been setup.\n";
}

/***********************************************************
 * * 			void startUp()
 * * Asks if user wants to randomize ant starting position,
 * * makes a call to setBoard() to create the board, then
 * * either generates a random integer for the ant's 
 * * X coordinate starting column and Y coordinate starting
 * * row, then makes a call to getBoard() to print out the
 * * board with the ant designated as a *.
***********************************************************/
void Ant::startUp()
{
   const char ANT = '*';

   const int RANDOM = 1;

   const int CHOOSE = 2;

   int location = CHOOSE; //holds user decision to randomize or choose ant start position

   string userInput = ""; //used to validate user input

   cout << "Before setting up the simulation, would you "; //extra credit message
   cout << "like the starting position of the ant to be ";
   cout << "randomized?\n";
   
   cout << "1. Random Ant starting location\n"; //extra credit menu options
   cout << "2. Let me choose Ant starting location\n";

   do //extra credit option: choose random or chosen start location
   {
      getline(cin, userInput);

      if (userInput != "1" && userInput != "2")
      {
	 cout << "Error: please enter 1 to randomize ant ";
	 cout << "start location or 2 to choose ant start ";
	 cout << "location.\n";
      }
   } while (userInput != "1" && userInput != "2");

   location = stoi(userInput);

   if (location == CHOOSE)
   {
      cout << "Ok, you will be able to choose the ant's starting position.\n";
   }

   if (location == RANDOM)
   {
      cout << "Ok, the ant's starting position will be randomized.\n";
   }

   /***********************************
    * * setBoard will create a dynamic
    * * 2D array of characters using
    * * user input to construct the
    * * simulation board.
   ***********************************/
   setBoard();

   if (location == CHOOSE) //allows user to choose where the ant starts on the board
   {
      cout << "Where would you like the ant to start on the board? ";
      cout << "Please note that the ant's initial orientation is up.\n"; //ant starts facing up

      do //if user chooses to, choose starting row
      {
	 cout << "To choose the starting row, enter an integer between 1 and " << rows << endl;

	 getline(cin, userInput);

	 validateInt(userInput);

	 antYCoord = stoi(userInput);

	 antYCoord -= 1; //corrects user input to match index of board, see next do-while loop for example

	 if (antYCoord >= rows || antYCoord < 0)
	 {
	    cout << "Error: cannot place ant outside of board.\n";
	 }
      } while (antYCoord >= rows || antYCoord < 0); //prevent user from placing ant out of board bounds

      do //choose starting column
      {
	 cout << "To choose the starting column, enter an integer between 1 and " << columns << endl;

	 getline(cin, userInput);

	 validateInt(userInput);

	 antXCoord = stoi(userInput);

	 antXCoord -= 1; //corrects user input to match index of board, Ex. user wants ant at the first col,
			 //enters 1, this correctly matches the ant's column to board[antYCoord][0]
	 if (antXCoord >= columns || antXCoord < 0)
	 {
	    cout << "Error: cannot place ant outside of board.\n";
	 }
      } while (antXCoord >= columns || antXCoord < 0);

      cout << "Ok, you have placed the ant at row " << antYCoord + 1;
      cout << " and at column " << antXCoord + 1 << endl;
   }

   if (location == RANDOM) //if user chooses to, randomize the ant's starting location
   {
      cout << "Randomizing starting row...\n";

      srand(time(NULL)); //used to generate random numbers for the ant's start row and column

      do //randomize ant's starting row
      {
	 antYCoord = rand() % rows;
      } while (antYCoord >= rows || antYCoord < 0);

      cout << "Randomizing starting column...\n";

      do //randomize ant's starting column
      {
	 antXCoord = rand() % columns;
      } while (antXCoord >= columns || antXCoord < 0);

      cout << "The ant will start at row " << antYCoord + 1;
      cout << " and column " << antXCoord + 1 << endl;
   }

   board[antYCoord][antXCoord] = ANT; //place the ant at the starting location

   cout << "How many steps would you like the ant to take?\n";

   do //prevent the user from exceeding 300,000 steps
   {
      getline(cin, userInput); //get the number of steps the ant should take

      validateInt(userInput);

      steps = stoi(userInput);

      if (steps >= STEPLIMIT)
      {
	 cout << "Error: too many steps, please enter fewer than " << STEPLIMIT << " steps.\n";
      }
   } while (steps >= STEPLIMIT);

   cout << "Ok, the ant will take " << steps << " steps.\n";
   cout << "Here is the board before the simulation begins running.\n";

   getBoard();

   cout << "There are " << steps << " steps remaining. The ant is facing up.\n";
}

/*****************************************************************
 * * 			  void simulate()
*****************************************************************/
void Ant::simulate()
{
   const char WHITE = ' '; //legend for board colors

   const char BLACK = '#';

   const int UP = 0; //legend for orientation

   const int RIGHT = 1;

   const int DOWN = 2;

   const int LEFT = 3;

   char nextSpace = ' '; //assume the first space to move to is white

   char currentSpace = WHITE; //ant always starts on a white space

   for (int i = steps; i > 0; i--)
   {
      if (currentSpace == WHITE) //ant is on white
      {
	 if (antOrientation == UP) //ant is on white facing up
	 {
	    antOrientation = RIGHT; //turn the ant 90 degrees to face right

	    if (antXCoord + 1 > columns - 1) //ant would go off right side of board
	    {
	       antOrientation = DOWN; //skip the forward move and continue to the next step
	    }

	    else
	    {
	       moveRight(currentSpace, nextSpace); 
	    }
	 }

	 else if (antOrientation == RIGHT) //ant is on white facing right
	 {
	    antOrientation = DOWN;

	    if (antYCoord + 1 > rows - 1)
	    {
	       antOrientation = LEFT;
	    }

	    else
	    {
	       moveDown(currentSpace, nextSpace);
	    }
	 }

	 else if (antOrientation == DOWN) //ant is on white facing down
	 {
	    antOrientation = LEFT;

	    if (antXCoord - 1 == -1)
	    {
	       antOrientation = UP;
	    }

	    else
	    {
	       moveLeft(currentSpace, nextSpace);
	    }
	 }

	 else if (antOrientation == LEFT) //ant is on white facing left
	 {
	    antOrientation = UP;

	    if (antYCoord - 1 == -1)
	    {
	       antOrientation = RIGHT;
	    }

	    else
	    {
	       moveUp(currentSpace, nextSpace);
	    }
	 }
      }

      else if (currentSpace == BLACK) //ant is on black
      {
	 if (antOrientation == UP) //ant is on black facing up
	 {
	    antOrientation = LEFT;

	    if (antXCoord - 1 == -1)
	    {
	       antOrientation = DOWN;
	    }

	    else
	    {
	       moveLeft(currentSpace, nextSpace);
	    }
	 }

	 else if (antOrientation == LEFT) //ant is on black facing left
	 {
	    antOrientation = DOWN;

	    if (antYCoord + 1 > rows - 1)
	    {
	       antOrientation = RIGHT;
	    }

	    else
	    {
	       moveDown(currentSpace, nextSpace);
	    }
	 }

	 else if (antOrientation == DOWN) //ant is on black facing down
	 {
	    antOrientation = RIGHT;

	    if (antXCoord + 1 > columns - 1)
	    {
	       antOrientation = UP;
	    }

	    else
	    {
	       moveRight(currentSpace, nextSpace);
	    }
	 }

	 else if (antOrientation == RIGHT) //ant is on black facing right
	 {
	    antOrientation = UP;

	    if (antYCoord - 1 == -1)
	    {
	       antOrientation = LEFT;
	    }

	    else
	    {
	       moveUp(currentSpace, nextSpace);
	    }
	 }
      }

      getBoard();

      steps--;

      cout << "There are " << steps << " steps remaining.";
      
      if (antOrientation == UP)
      {
	 cout << " The ant is facing up.\n";
      }

      else if (antOrientation == RIGHT)
      {
	 cout << " The ant is facing right.\n";
      }

      else if (antOrientation == DOWN)
      {
	 cout << " The ant is facing down.\n";
      }

      else if (antOrientation == LEFT)
      {
	 cout << " The ant is facing left.\n";
      }
   }
}

void Ant::moveRight(char& currentSpace, char& nextSpace)
{
   const char WHITE = ' ';

   const char BLACK = '#';

   const char ANT = '*';

   nextSpace = board[antYCoord][antXCoord + 1]; //memorize the color of the space the ant moves to

   if (currentSpace == WHITE)
   {
     currentSpace = BLACK; //flip the color of the ant's current space
   }

   else if (currentSpace == BLACK)
   {
     currentSpace = WHITE;
   } 

   antXCoord += 1; //move the ant right one space

   board[antYCoord][antXCoord] = ANT; //mark the ant's current position with a *

   board[antYCoord][antXCoord - 1] = currentSpace; //flip the color of the ant's previous space

   currentSpace = nextSpace; //store the value of the space the ant is now on
}

void Ant::moveDown(char& currentSpace, char& nextSpace)
{
   const char WHITE = ' ';

   const char BLACK = '#';

   const char ANT = '*';

   nextSpace = board[antYCoord + 1][antXCoord];

   if (currentSpace == WHITE)
   {
     currentSpace = BLACK; //flip the color of the ant's current space
   }

   else if (currentSpace == BLACK)
   {
     currentSpace = WHITE;
   } 
   
   antYCoord += 1;
   
   board[antYCoord][antXCoord] = ANT;
   
   board[antYCoord - 1][antXCoord] = currentSpace;
   
   currentSpace = nextSpace;
}

void Ant::moveLeft(char& currentSpace, char& nextSpace)
{
   const char WHITE = ' ';

   const char BLACK = '#';

   const char ANT = '*';

   nextSpace = board[antYCoord][antXCoord - 1];

   if (currentSpace == WHITE)
   {
     currentSpace = BLACK; //flip the color of the ant's current space
   }

   else if (currentSpace == BLACK)
   {
     currentSpace = WHITE;
   } 
   
   antXCoord -= 1;

   board[antYCoord][antXCoord] = ANT;

   board[antYCoord][antXCoord + 1] = currentSpace;

   currentSpace = nextSpace;
}

void Ant::moveUp(char& currentSpace, char& nextSpace)
{
   const char WHITE = ' ';

   const char BLACK = '#';

   const char ANT = '*';

   nextSpace = board[antYCoord - 1][antXCoord];

   if (currentSpace == WHITE)
   {
     currentSpace = BLACK; //flip the color of the ant's current space
   }

   else if (currentSpace == BLACK)
   {
     currentSpace = WHITE;
   } 

   antYCoord -= 1;

   board[antYCoord][antXCoord] = ANT;

   board[antYCoord + 1][antXCoord] = currentSpace;

   currentSpace = nextSpace;
}

void Ant::getBoard()
{
   cout << endl << " ";

   for (int i = 0; i < columns; i++)
   {
      cout << "-";
   }

   cout << endl;

   for (int i = 0; i < rows; i++) //print the board to the user
   {
      cout << "|";

      for (int j = 0; j < columns; j++)
      {
	 cout << board[i][j];
      }

      cout << "|";

      cout << endl;
   }

   cout << " ";

   for (int i = 0; i < columns; i++)
   {
      cout << "-";
   }

   cout << endl;
}
