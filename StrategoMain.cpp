#include"StrategoFunc.h"

int main()
{
	//print header
	printHeader();
	//print rules
	printGameHeader();
	//instantiate the board arrays
	gameSlot **board = new gameSlot* [ARRAY_SIZE];
	for(int i = 0; i < ARRAY_SIZE; i++)
		board[i] = new gameSlot [ARRAY_SIZE];
	//initialize board to null
	initializeBoardNull(board, ARRAY_SIZE);
	//instantiate the board with the team pieces
	initializeBoard(board, ARRAY_SIZE);		
	string input;
	int columnPiece, columnStrike, rowPiece, rowStrike;
	bool valid;
	//begin playing the game while it isn't over or the player hasn't quit
	do{
			//print out the array
			printArray(board, ARRAY_SIZE, false);
			//get the input for the accepted piece or quitting
			do{
			//set the validity of the input to true
			valid = true;
			//prompt and read in the input
			cout << "RED MOVE: Enter current coordinates of piece (e.g., D2, or QQ to quit): ";
			cin >> input;
			//calculate the value of the row and column from input
			rowPiece = input.at(0) - 65;
			columnPiece = input.at(1) - 49;		
			//check if the input is not to leave	
			if(input == "QQ")
			{
				//print out that the game is over and delete the two arrays
				cout << "Red Player Forfeits" << endl;
				printArray(board, ARRAY_SIZE, true);
				cout << "Thanks for Playing :)" << endl;	
				for(int i = 0; i < ARRAY_SIZE; i++)
					delete [] board[i];
				delete [] board;
				//exit the program
				return 0;
			}
			if(input.length() > 2)
			{
				//check to see that the input is invalid and output the error
				cout << "Invalid Coordinates. Out of Range. Try Again" << endl;	
				//set the validity to false
				valid = false;
			}
			if(rowPiece < 0 || rowPiece > 4 || columnPiece < 0 || columnPiece > 4)
			{
				//if the input is out of range, output an error 
				cout << "Invalid Coordinates. Out of Range. Try Again" << endl;	
				//change the validitiy to false
				valid = false;
			}
			else if(board[rowPiece][columnPiece].ColourType != RED || board[rowPiece][columnPiece].PieceType == 70 || board[rowPiece][columnPiece].PieceType == 66 || board[rowPiece][columnPiece].PieceType == 32)
			{
				//if the piece chosen is of the incorrect colour typeprint out an error message
				cout << "Invalid Coordinates. Immoveable Piece. Try Again" << endl;	
				//set the validity to false
				valid = false;	
			}

		}while(!valid);
		


		//get the coordinates for the striking place or that they want to quit
		do{
			//set the validity of the input to true
			valid = true;
			//prompt and read in input
			cout << "RED MOVE: Enter coordinates of where to strike(e.g., D2, or QQ to quit): ";
			cin >> input;
			//calculate the row and column strike
			rowStrike = input.at(0) - 65;
			columnStrike = input.at(1) - 49;
			//check to see if the input if to quit
			if(input == "QQ")
			{
				//output the choice and quit the game
				cout << "Red Player Forfeits" << endl;
				printArray(board, ARRAY_SIZE, true);
				//delete the arrays
				cout << "Thanks for Playing :)" << endl;	
				for(int i = 0; i < ARRAY_SIZE; i++)
					delete [] board[i];
				delete [] board;
				return 0;
			}
			if(input.length() > 2)
			{
				//if the input is invalid, output error message
				cout << "Invalid Coordinates. Out of Range. Try Again" << endl;	
				//set validity to false
				valid = false;
			}
			if(rowStrike < 0 || rowStrike > 4 || columnStrike < 0 || columnStrike > 4)
			{
				//if out of range, outputerror message	
				cout << "Invalid Coordinates. Out of Range. Try Again" << endl;	
				//set validity to false
				valid = false;
			}			
			else if(abs(rowStrike-rowPiece) >=2 || abs(columnStrike-columnPiece) >=2 || (rowStrike == rowPiece && columnStrike == columnPiece))
			{
				//If the move is impossible by the rules, output error message
				cout << "Invalid Coordinates. Pieces move one space at a time. Try Again" << endl;
				//set validity to false	
				valid = false;
			}	
			else if(board[rowStrike][columnStrike].ColourType == RED)
			{
				//if you try to attack the same calendar output invalid coordinates
				cout << "Invalid Coordinates. Can't Attack Own  Colour. Try Again" << endl;	
				//set validity to false
				valid = false;
			}
			else if(rowStrike != rowPiece && columnStrike != columnPiece)
			{
				//if the move is diagonal, output error message
				cout << "Invalid Coordinates. Piece can't move diagonally. Try Again" << endl;	
				//set validity to false
				valid = false;
			}
		
		}while(!valid);
		
	}while(!updateGame(board, rowPiece, columnPiece, rowStrike, columnStrike));
	//output winner
	cout << "Red Player Won!" << endl;
	cout << "Thanks for Playing :)" << endl;	
	//delete arrays
	printArray(board, ARRAY_SIZE, true);
			
	for(int i = 0; i < ARRAY_SIZE; i++)
			delete [] board[i];
	delete [] board;
	//exit program
	return 0;	
}



