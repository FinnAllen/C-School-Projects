//authors: dr Y, Makoto Kewish and Finnian Allen
//file: queens.h
//date: November 9, 2018

// ADT Queens (motivated by the famous Eight Queens Problem)
//      data object: a number of queens on a chess board
//      operations: create, create a certain size, destroy
//                  place a queen on the board, remove a queen from the board
//                  check if a spot is valid (previous queens cannot attack)
//                  print the queens on the board

#ifndef QUEENS_H
#define QUEENS_H

const int MAXSIZE = 10;

class Queens
{
public:
   //creates an empty chessboard of default size 8
   //post empty chessboard is assigned with no queens yet on it
   //usage Queens queensOnBoard;
   Queens();
   
   //creates an empty chessboard of size a certain size
   //post empty chessboard is assigned with no queens yet on it
   //usage Queens queensOnBoard(4);
   Queens(int boardSize);  
   
   //destroys the board
   //pre queens object exists
   //automatically called at the end of scope    
   ~Queens();

   //places a queen on the chessboard
   //pre board exists with queens in rows 0 to queensCount - 1
   //post a queen has been placed on the board in row queensCount and column
   //usage queensOnBoard.placeQueen(2);
   void placeQueen(int column);
   
   //removes a queen from the chessboard
   //pre queens exist on the board in rows 0 to queensCount - 1
   //post removes the queen in row queensCount - 1 and column
   //usage queensOnBoard.removeQueen(3);
   void removeQueen(int column);
   
   //checks to see of a square on the chessboard is safe for a queen
   //pre queens are on the board in rows 0 to queensCount - 1
   //post if the square at row queensCount and column is safe for a queen
   //        returns true else returns false
   //usage isValidSpot(column);
   bool isValidSpot(int column) const;
   
   //prints the chessboard and queens on it
   //pre there may or may not be queens on the board
   //post prints the board to look like a chessboard with squares and shows the queens
   //usage printBoard()
   void printBoard() const;

   //checks to see if the queens problem is solved
   //pre there may or may not be queens on the board
   //post if the number of queens on the board is the same as board size
   //      then it returns true else returns false
   //usage if(board.IsSolved())
   bool isSolved() const;

   int boardSize;

private:

   bool board[MAXSIZE][MAXSIZE];
   
   int queensCount; //also row number for next queen
};
#endif

