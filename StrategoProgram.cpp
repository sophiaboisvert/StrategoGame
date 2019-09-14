#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <stdlib.h>

#include <stdio.h>
using namespace std;

const int ARRAY_SIZE=5;
//instantiate the enumerated type for the piece type
enum pieces { FLAG = 70, BOMB = 66, MINER = 56, SPY = 83, MARSHAL = 49, GENERAL = 50, COLONEL = 51, MAJOR = 52, CAPITAN = 53, LIEUTENANT = 54, SERGEANT = 55, EMPTY = 32};
//instantiate the enumerated type for the colour type
enum colours { RED, BLUE, NONE };	

//create the board structure

struct gameSlot
{
	pieces PieceType;
	colours ColourType;
	bool Moveable;
};

//a void function that prints outs my name, my email, the course, and the instructor
void printHeader();

//a void function that prints out the game rules
void printGameHeader();

//a void function that takes the board and its size and intializes it to its null state
void initializeBoardNull(gameSlot **board, int SIZE);

//a void fucntion that takes the board and its size and initializes it with the two teams pieces
void initializeBoard(gameSlot **board, int SIZE);

//a void function that takes the board, its size and wheter or not to reveal the blue pieces and prints out the array accordingly
void printArray(gameSlot **board, int SIZE, bool revealBlue);

// a function that takes the board, the coordinates of a valid move, updates the game board and returns whether or not the game has concluded
bool updateGame(gameSlot **board, int rPiece, int cPiece, int rStrike, int cStrike);
