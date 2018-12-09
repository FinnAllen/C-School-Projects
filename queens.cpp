//authors: dr Y, Makoto Kewish and Finnian Allen
//file: queens.cpp
//date: November 9, 2018

// ADT Queens (motivated by the famous Eight Queens Problem)
//      data object: a number of queens on a chess board
//      operations: create, create a certain size, destroy
//                  place a queen on the board, remove a queen from the board
//                  check if a spot is valid (previous queens cannot attack)
//                  print the queens on the board

#include "queens.h"
#include <iostream>
using namespace std;

   //creates an empty chessboard of default size 8
   //post: empty chessboard is assigned with no queens yet on it
   //usage: Queens queensOnBoard;
   Queens::Queens()
   {
	   boardSize = 4;
	   queensCount = 0;
	   for (int row = 0; row < boardSize; row++)
	   {
		   for(int column = 0; column < boardSize; column++)
		   {
			   board[row][column] = false;
		   }
	   }
   }
   
   //creates an empty chessboard of size a certain size
   //post empty chessboard is assigned with no queens yet on it
   //usage Queens queensOnBoard(4);
   Queens::Queens(int size)
   {
	   boardSize = size;
	   queensCount = 0;
	   for (int row = 0; row < boardSize; row++)
	   {
		   for(int column = 0; column < boardSize; column++)
		   {
			   board[row][column] = false;
		   }
	   }
   }  
   
   //destroys the board
   //pre: queens object exists
   //automatically called at the end of scope    
   Queens::~Queens()
   {
	   
	   
   }

   //places a queen on the chessboard
   //pre: board exists with queens in rows 0 to queensCount - 1
   //post: a queen has been placed on the board in row queensCount and column
   //usage: queensOnBoard.placeQueen(2);
   void Queens::placeQueen(int column)
   {
	   board[queensCount][column] = true;
	   queensCount++;
   }
   
   //removes a queen from the chessboard
   //pre: queens exist on the board in rows 0 to queensCount - 1
   //post: removes the queen in row queensCount - 1 and column
   //usage: queensOnBoard.removeQueen(3);
   void Queens::removeQueen(int column)
   {
	   queensCount--;
	   board[queensCount][column] = false;
   }
   
   //checks to see of a square on the chessboard is safe for a queen
   //pre: queens are on the board in rows 0 to queensCount - 1
   //post: if the square at row queensCount and column is safe for a queen
   //        returns true else returns false
   //usage: isValidSpot(column);
   bool Queens::isValidSpot(int column) const
   {
	   bool isOkUp = true;
	   int row = queensCount - 1;
	   while (isOkUp and row >= 0)
	   {
		   isOkUp = not board[row][column];
		   row--;
	   }
	   bool isOkDiagonalLeft = true;
	   row = queensCount - 1;
	   int columnLeft = column - 1;
	   while (isOkDiagonalLeft and columnLeft >= 0 and row >= 0)
	   {
		   isOkDiagonalLeft = not board[row][columnLeft];
		   row--;
		   columnLeft--;
	   }
	   bool isOkDiagonalRight = true;
	   row = queensCount - 1;
	   int columnRight = column + 1;
	   while (isOkDiagonalRight and columnRight < boardSize and row >= 0)
	   {
		   isOkDiagonalRight = not board[row][columnRight];
		   row--;
		   columnRight++;
	   }
	   
	   return isOkUp and isOkDiagonalLeft and isOkDiagonalRight;
   }
   
   
   //prints the chessboard and queens on it
   //pre: there may or may not be queens on the board
   //post: prints the board to look like a chessboard with squares and shows the queens
   //usage: printBoard();
   void Queens::printBoard() const
   {
	for(int row = 0; row < boardSize; row++)
	{
		for(int column = 0; column < boardSize; column++)
		{
			if(board[row][column])
			{
				cout << "|Q|";
			} else {
				cout << "|_|";
			}
		}
		cout << endl;
	}
   }

   //checks to see if the queens problem is solved
   //pre: there may or may not be queens on the board
   //post: if the number of queens on the board is the same as board size
   //      then it returns true else returns false
   //usage: if(board.IsSolved())
   bool Queens::isSolved() const
   {
	   return(queensCount == boardSize);
   }
