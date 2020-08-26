/************************************************************************
 * * Program name: 	Project1
 * * Author: 		Benjamin Hillen
 * * Date: 		1 October 2019
 * * Description: 	Declaration of Ant class	
************************************************************************/

#ifndef ANT_HPP
#define ANT_HPP

class Ant
{ private:
   
   int antXCoord;
   
   int antYCoord;

   int antOrientation;

   int steps;

   char** board;

   int rows;

   int columns;

  public:

   Ant(); //defaults ant's data members to 0 upon creation of ant object

   ~Ant(); //deallocates memory assigned to the Ant object

   void startUp();

   void simulate();

   void moveRight(char& currentSpace, char& nextSpace);

   void moveDown(char& currentSpace, char& nextSpace);

   void moveLeft(char& currentSpace, char& nextSpace);

   void moveUp(char& currentSpace, char& nextSpace);

   //mutators
   void setBoard();

   //void setAntXCoord(int XCoord);

   //void setAntYCoord(int YCoord);

   //void setAntOrientation(int direction);

   //accessors
   void getBoard();

   //void getAntXCoord();

   //void getAntYCoord();

   //void getAntOrientation();
};
#endif
