#include"StrategoProgram.h"

bool updateGame(gameSlot **board, int rPiece, int cPiece, int rStrike, int cStrike)
{
	//if a flag is attacked
	if(board[rStrike][cStrike].PieceType == FLAG)
	{
		//output the move, set the flag colur to false
		cout << "Red " << static_cast<char>(board[rPiece][cPiece].PieceType) << " at " << static_cast<char>(rPiece+65) << static_cast<char>(cPiece+49);
		cout << " captures BLUE " << static_cast<char>(board[rStrike][cStrike].PieceType) << " at " << static_cast<char>(rStrike+65) << static_cast<char>(cStrike+49)<<  "." <<endl;
		board[rStrike][cStrike].ColourType = NONE;
		//return the game being over
		return true;
	}
	//if moving to a empty place
	if(board[rStrike][cStrike].PieceType == EMPTY)
	{
		//output the move
		cout << "Red " << static_cast<char>(board[rPiece][cPiece].PieceType) << " moves from " << static_cast<char>(rPiece+65) << static_cast<char>(cPiece+49);
		cout << " to "  << static_cast<char>(rStrike+ 65) << static_cast<char>(cStrike+49)<<  "." <<endl;	
		//move the piece details to the new spot
		board[rStrike][cStrike].PieceType = board[rPiece][cPiece].PieceType;
		board[rStrike][cStrike].ColourType = board[rPiece][cPiece].ColourType;
		//set the old spot to empty
		board[rPiece][cPiece].PieceType = EMPTY;
		board[rPiece][cPiece].ColourType = NONE;
	}
	//if the defending piece is a bomb
	else if(board[rStrike][cStrike].PieceType == BOMB)
	{
		//if the attacking piece is a miner
		if(board[rPiece][cPiece].PieceType == MINER)
		{
			//output the move
			cout << "Red " << static_cast<char>(board[rPiece][cPiece].PieceType) << " at " << static_cast<char>(rPiece+65) << static_cast<char>(cPiece+49);
			cout << " defuses BLUE " << static_cast<char>(board[rStrike][cStrike].PieceType) << " at " << static_cast<char>(rStrike+65) << static_cast<char>(cStrike+49)<<  "." <<endl;	
			//move the miner into the spot where the bomb was
			board[rStrike][cStrike].PieceType = board[rPiece][cPiece].PieceType;
			board[rStrike][cStrike].ColourType = board[rPiece][cPiece].ColourType;
			//set the miners old spot to be empty
			board[rPiece][cPiece].PieceType = EMPTY;
			board[rPiece][cPiece].ColourType = NONE;
		}
		else
		{	
			//output the piece being blown up
			cout << "Red " << static_cast<char>(board[rPiece][cPiece].PieceType) << " at " << static_cast<char>(rPiece+65) << static_cast<char>(cPiece+49);
			cout << " blown up by BLUE " << static_cast<char>(board[rStrike][cStrike].PieceType) << " at " << static_cast<char>(rStrike+65) << static_cast<char>(cStrike+49)<<  "." <<endl;	
			//set the attacking piece spot to be empty
			board[rPiece][cPiece].PieceType = EMPTY;
			board[rPiece][cPiece].ColourType = NONE;
		}
	}
	else
	{
		//if it is a piece attacking another attacking piece
		//calcuate the defender rank 1 - 9
		int rankDefender = board[rStrike][cStrike].PieceType - 48;
		if(board[rStrike][cStrike].PieceType == SPY)
			rankDefender = 9;
		//calculate the attacker rank of 1 - 9
		int rankAttacker = board[rPiece][cPiece].PieceType - 48;
		if(board[rPiece][cPiece].PieceType == SPY)
			rankAttacker = 9;
		//if the attacker is a spy and they are attacking a marshal or a general or the attacking piece wins
		if((rankAttacker == 9 && (rankDefender == 1 || rankDefender == 2)) || rankDefender > rankAttacker)
		{
			//output the move
			cout << "Red " << static_cast<char>(board[rPiece][cPiece].PieceType) << " at " << static_cast<char>(rPiece+65) << static_cast<char>(cPiece+49);
			cout << " captures BLUE " << static_cast<char>(board[rStrike][cStrike].PieceType) << " at " << static_cast<char>(rStrike+65) << static_cast<char>(cStrike+49)<<  "." <<endl;	
			//replace the defending piece with the attacking piece
			board[rStrike][cStrike].PieceType = board[rPiece][cPiece].PieceType;
			board[rStrike][cStrike].ColourType = board[rPiece][cPiece].ColourType;
			//set the attacking piece spot to be empty
			board[rPiece][cPiece].PieceType = EMPTY;
			board[rPiece][cPiece].ColourType = NONE;
		} 
		//if they attack the same type
		else if(rankAttacker == rankDefender)
		{
			//output the move and result
			cout << "Red " << static_cast<char>(board[rPiece][cPiece].PieceType) << " at " << static_cast<char>(rPiece+65) << static_cast<char>(cPiece+49);
			cout << " and BLUE " << static_cast<char>(board[rStrike][cStrike].PieceType) << " at " << static_cast<char>(rStrike+65) << static_cast<char>(cStrike+49)<<  " mutually destroy each other." <<endl;	
			//remove both pieces
			board[rStrike][cStrike].PieceType = EMPTY;
			board[rStrike][cStrike].ColourType = NONE;
			board[rPiece][cPiece].PieceType = EMPTY;
			board[rPiece][cPiece].ColourType = NONE;
		}
		else
		{
			//if the attacker loses
			//output the result of the move
			cout << "Red " << static_cast<char>(board[rPiece][cPiece].PieceType) << " at " << static_cast<char>(rPiece+65) << static_cast<char>(cPiece+49);
			cout << " captured by BLUE " << static_cast<char>(board[rStrike][cStrike].PieceType) << " at " << static_cast<char>(rStrike+65) << static_cast<char>(cStrike+49)<<  "." <<endl;	
			//empty the attakers slot
			board[rPiece][cPiece].PieceType = EMPTY;
			board[rPiece][cPiece].ColourType = NONE;
		}		
	}
	//return that the game isnt over
	return false;
}

void printArray(gameSlot **board, int SIZE, bool revealBlue)
{
	
	cout <<"    1 2 3 4 5\n";

	cout <<"  +-----------+\n";
	
	cout <<"A | ";
	
	char output;
	//print out the first row
	for(int c = 0; c < ARRAY_SIZE; c++){

		output = static_cast<char>(board[0][c].PieceType);
		//if a blue colour and reveal blue, print out the blue piece
		if(board[0][c].ColourType == BLUE && revealBlue)
			
			printf("\033[1;34m%c\033[0m ",  output);
		//if blue but not reveal blue, print out a blue x
		else if(board[0][c].ColourType == BLUE)
			printf("\033[1;34m%c\033[0m ",  'X');
		//if the colour is red, print out red
		else if(board[0][c].ColourType == RED)	
			printf("\033[1;31m%c\033[0m ",  output);
		//if no colour just print out normally
		else
			cout << output << " ";
	
	}	
	
	cout << "|\nB | ";

	//print out the second row
	for(int c = 0; c < ARRAY_SIZE; c++){

		output = static_cast<char>(board[1][c].PieceType);
		//if a blue colour and reveal blue, print out the blue piece
		if(board[1][c].ColourType == BLUE && revealBlue)
			
			printf("\033[1;34m%c\033[0m ",  output);
		//if blue but not reveal blue, print out a blue x
		else if(board[1][c].ColourType == BLUE)
			printf("\033[1;34m%c\033[0m ",  'X');
		//if the colour is red, print out red
		else if(board[1][c].ColourType == RED)	
			printf("\033[1;31m%c\033[0m ",  output);
		//if no colour just print out normally
		else
			cout << output << " ";
	
	}	
	
	
	cout << "|\nC | ";
	//print out the third row
	for(int c = 0; c < ARRAY_SIZE; c++){

		output = static_cast<char>(board[2][c].PieceType);
		//if a blue colour and reveal blue, print out the blue piece
		if(board[2][c].ColourType == BLUE && revealBlue)
			
			printf("\033[1;34m%c\033[0m ",  output);
		//if blue but not reveal blue, print out a blue x
		else if(board[2][c].ColourType == BLUE)
			printf("\033[1;34m%c\033[0m ",  'X');
		//if the colour is red, print out red
		else if(board[2][c].ColourType == RED)	
			printf("\033[1;31m%c\033[0m ",  output);
		//if no colour just print out normally
		else
			cout << output << " ";
	
	}	
	
	cout << "|\nD | ";
	//print out the fourth row
	for(int c = 0; c < ARRAY_SIZE; c++){

		output = static_cast<char>(board[3][c].PieceType);
		//if a blue colour and reveal blue, print out the blue piece
		if(board[3][c].ColourType == BLUE && revealBlue)
			
			printf("\033[1;34m%c\033[0m ",  output);
		//if blue but not reveal blue, print out a blue x
		else if(board[3][c].ColourType == BLUE)
			printf("\033[1;34m%c\033[0m ",  'X');
		//if the colour is red, print out red
		else if(board[3][c].ColourType == RED)	
			printf("\033[1;31m%c\033[0m ",  output);
		//if no colour just print out normally
		else
			cout << output << " ";
	
	}	
	
	cout << "|\nE | ";
	
	//print out the ifth row
	for(int c = 0; c < ARRAY_SIZE; c++){

		output = static_cast<char>(board[4][c].PieceType);
		//if a blue colour and reveal blue, print out the blue piece
		if(board[4][c].ColourType == BLUE && revealBlue)
			
			printf("\033[1;34m%c\033[0m ",  output);
		//if blue but not reveal blue, print out a blue x
		else if(board[4][c].ColourType == BLUE)
			printf("\033[1;34m%c\033[0m ",  'X');
		//if the colour is red, print out red
		else if(board[4][c].ColourType == RED)	
			printf("\033[1;31m%c\033[0m ",  output);
		//if no colour just print out normally
		else
			cout << output << " ";
	
	}	
	
	cout << "|\n  +-----------+\n";
}





void initializeBoard(gameSlot **board, int SIZE)
{
	//seed the random number generator
	srand(time(NULL));
	
	int randR;
	int randC;
	int temp;
	
	//Place the random flags
	randC = rand() % ARRAY_SIZE;
	//place the red flg
	board[4][randC].PieceType = FLAG;
	board[4][randC].ColourType = RED;	
	randC = rand() % ARRAY_SIZE;
	//place the blue flag
	board[0][randC].PieceType = FLAG;
	board[0][randC].ColourType = BLUE;

	//place the three random bombs
	for(int i = 0; i < 3; i++)
	{
		
		do
		{
		//randomly generate bomb position for blue until it is a valid
		randR = rand() % 2;
		randC = rand() % ARRAY_SIZE;
		}while(board[randR][randC].ColourType != NONE);
		//place the bomb
		board[randR][randC].PieceType = BOMB;
		board[randR][randC].ColourType = BLUE;
		do
		{
		//randomly generate bomb position for reduntil it is valid	
		randR = rand() % 2 + 3;
		randC = rand() % ARRAY_SIZE;
		}while(board[randR][randC].ColourType != NONE);
		//place the bomb
		board[randR][randC].PieceType = BOMB;
		board[randR][randC].ColourType = RED;	
	}

	
	do
	{
		//randomly generate the position for the blue miner until one is valid
		randR = rand() % 2;
		randC = rand() % ARRAY_SIZE;
	
	}while(board[randR][randC].ColourType != NONE);
	//place the miner
	board[randR][randC].PieceType = MINER;
	board[randR][randC].ColourType = BLUE;
	

	
	do
	{
		//randomly generate the position for the red miner until one is valid	
		randR = rand() % 2 + 3;
		randC = rand() % ARRAY_SIZE;
	}while(board[randR][randC].ColourType != NONE);
	//place teh red miner
	board[randR][randC].PieceType = MINER;
	board[randR][randC].ColourType = RED;
		
	
	do
	{
		//randomly generate the spy position for the red miner until valid
		randR = rand() % 2 + 3;
		randC = rand() % ARRAY_SIZE;
	}while(board[randR][randC].ColourType != NONE);
	//place the red spy
	board[randR][randC].PieceType = SPY;
	board[randR][randC].ColourType = RED;

	
	do
	{
		//randomly generate the spy position for the blue miner	until valid
		randR = rand() % 2;
		randC = rand() % ARRAY_SIZE;
	}while(board[randR][randC].ColourType != NONE);
	//place the blue spy
	board[randR][randC].PieceType = SPY;
	board[randR][randC].ColourType = BLUE;
	
	do
	{
		//randomly generate the location until valid
		randR = rand() % 2;
		randC= rand() % ARRAY_SIZE;
	
	}while(board[randR][randC].ColourType != NONE);
	//place the random blue Marshal or General
	board[randR][randC].PieceType = static_cast<pieces>(rand() % 2 + 49);
	board[randR][randC].ColourType = BLUE;	

	
	do
	{
		//randomly generate the location until valid
		randR = rand() % 2 + 3;
		randC = rand() % ARRAY_SIZE;
	
	}while(board[randR][randC].ColourType != NONE);
	//place the random red Marshal or General
	board[randR][randC].PieceType =static_cast<pieces>( rand() % 2 + 49);
	board[randR][randC].ColourType = RED;	

	
	for(int i = 0; i < 3; i++)
	{
		
		do
		{
			//randomly generate a position until valid
			randR = rand() % 2;	
			randC = rand() % ARRAY_SIZE;
		
		}while(board[randR][randC].ColourType != NONE);
		//randomly place the blue Colonel, major, capitan, lieutenant, or seargeant 
		board[randR][randC].PieceType = static_cast<pieces>(rand() % 5 + 51);
		board[randR][randC].ColourType = BLUE;	
		
		do
		{
			//randomly generate a position until valid	
			randR = rand() % 2 + 3;	
			randC = rand() % ARRAY_SIZE;
		
		}while(board[randR][randC].ColourType != NONE);
		//randomly place the red Colonel, major, capitan, lieutenant, or seargeant 		
		board[randR][randC].PieceType =static_cast<pieces>( rand() % 5 + 51);
		board[randR][randC].ColourType = RED;		
	
	}


}



void initializeBoardNull(gameSlot **board, int SIZE)
{
	//for each row
	for(int r = 0; r < ARRAY_SIZE; r++)
		//for each column
		for(int c = 0; c < ARRAY_SIZE; c++)
		{
			//set the colour and piece to the null point
			board[r][c].ColourType = NONE;
			board[r][c].PieceType =EMPTY;
		}

}



void printGameHeader()
{
	//print out rules
	cout << "\n           W e l c o m e  t o  1 0 3 0  S t r a t e g o\n";
	cout << "------------------------------------------------------------------------ \n";
	cout << "This program will set up a 5x5 game board for a 1030 version of the game \nof Stratego. One player will compete against the computer, each assigned \n10 total pieces consisting of the following:";
	cout << "\n  1 FLAG (F)\n  3 BOMB (B)\n  1 MARSHAL (1) or GENERAL (2)\n  ";
	cout << "3 COLONEL (3), MAJOR (4), CAPTAIN (5), LIEUTENANT (6), or SERGEANT (7)\n  ";
	cout << "1 MINER (8)\n  1 SPY (S)";
	cout << "\nGENERAL RULES:\n--------------\n";
	cout << "For the most part, the game will follow the standard Stratego rules, al-\nthough there are some exceptions.";
	cout << "\n1. Both players (BLUE and RED) will have all of their 10 game pieces as-\n   signed randomly with the only requirement being that the FLAG must be\n   placed in the back row. RED will start the game first.";
	cout << "\n2. Higher ranked pieces can capture lower ranked pieces in the following\n   order: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> S, meaning that 1 (the\n   MARSHAL) can remove 2 (the GENERAL) and so forth. The MINER (8) piece\n";
	cout << "   may strike a BOMB and remove it to occupy the now unoccupied space. A\n   SPY (S), although the lowest ranked piece, may remove the MARSHAL (1)\n   or the GENERAL (2). When pieces have equal rank, then both pieces are\n   removed\n";
	cout << "\n3. the FLAG and BOMBs are not moveable while all of the other pieces may\n   move one square at a time forward, backward, or sideward, but not di-\n   agonally to an open square.\n";
	cout << "4. A player must either move or strike on his/her turn.\n5. The game ends when a player strikes his/her opponent's flag.";
	cout << "\n------------------------------------------------------------------------";	
	cout << "\n\nInitializing game board...\nAssigning BLUE pieces to board..\nAssigning RED pieces to board..\n";
}



void printHeader()
{
	//print out header
	cout << "Computer Science and Engineering\nCSCE 1030 - Computer Science I\nSophia Boisvert\tsmb0506\tSophiaBoisvert@my.unt.edu";
}




