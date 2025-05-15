/***********************************************************************
 * Source File:
 *    BOARD 
 * Author:
 *    <your name here>
 * Summary:
 *    A collection of pieces and a small amount of game state
 ************************************************************************/

#include "board.h"
#include "uiDraw.h"
#include "position.h"
#include "piece.h"
#include "pieceSpace.h"
#include "pieceKnight.h"
#include <cassert>
using namespace std;


/***********************************************
 * BOARD : RESET
 *         Just fill the board with the known pieces
 *   +---a-b-c-d-e-f-g-h---+
 *   |                     |
 *   8     N         N     8
 *   7                     7
 *   6                     6
 *   5                     5
 *   4                     4
 *   3                     3
 *   2                     2
 *   1     n         n     1
 *   |                     |
 *   +---a-b-c-d-e-f-g-h---+
 ***********************************************/
void Board::reset(bool fFree)
{
   // free everything
   for (int r = 0; r < 8; r++)
      for (int c = 0; c < 8; c++)
      {
         if (!fFree)
            board[c][r] = pSpace;
         else
            board[c][r] = nullptr;
      }
   
   Knight wKnight1(Position("b1"), false /*white*/);
   Knight wKnight2(Position("g1"), false /*white*/);
   Knight bKnight1(Position("b8"), true  /*black*/);
   Knight bKnight2(Position("g8"), true  /*black*/);
}

// we really REALLY need to delete this.
Space space(0,0);

/***********************************************
* BOARD : GET
*         Get a piece from a given position.
***********************************************/
const Piece& Board::operator [] (const Position& pos) const
{
   assert(pos.isValid());
   assert(pos.getCol() < 8 && pos.getCol() >= 0);
   assert(pos.getRow() < 8 && pos.getRow() >= 0);
   if (board[pos.getCol()][pos.getRow()])
      return *(board[pos.getCol()][pos.getRow()]);
   else
      return *pSpace;
}
Piece& Board::operator [] (const Position& pos)
{
   assert(pos.isValid());
   assert(pos.getCol() < 8 && pos.getCol() >= 0);
   assert(pos.getRow() < 8 && pos.getRow() >= 0);
   if (board[pos.getCol()][pos.getRow()])
      return *(board[pos.getCol()][pos.getRow()]);
   else
      return *pSpace;
}

 /***********************************************
 * BOARD : DISPLAY
 *         Display the board
 ***********************************************/
void Board::display(const Position & posHover, const Position & posSelect) const
{
   
}


/************************************************
 * BOARD : CONSTRUCT
 *         Free up all the allocated memory
 ************************************************/
Board::Board(ogstream* pgout, bool noreset) : pgout(pgout), numMoves(0)
{
   pSpace = new Space(0,0);
   if (!noreset)
      reset(false /*fFree*/);
   else
      for (int r = 0; r < 8; r++)
         for (int c = 0; c < 8; c++)
            board[c][r] = nullptr;
}


/************************************************
 * BOARD : FREE
 *         Free up all the allocated memory
 ************************************************/
void Board::free()
{

}


/**********************************************
 * BOARD : ASSERT BOARD
 *         Verify the board is well-formed
 *********************************************/
void Board::assertBoard()
{

}




/**********************************************
 * BOARD : MOVE
 *         Execute a move according to the contained instructions
 *   INPUT move The instructions of the move
 *********************************************/
void Board::move(const Move & move)
{  
   (board[move.getSource().getCol()][move.getSource().getRow()])->setLastMove(numMoves);
   board[move.getDest().getCol()][move.getDest().getRow()] = board[move.getSource().getCol()][move.getSource().getRow()];
   board[move.getSource().getCol()][move.getSource().getRow()] = pSpace;
   numMoves++;
}



/**********************************************
 * BOARD EMPTY
 * The game board that is completely empty.
 * It does not even have spaces though each non-filled
 * spot will report it has a space. This is for unit testing
 *********************************************/
BoardEmpty::BoardEmpty() : BoardDummy(), pSpace(nullptr), moveNumber(0)
{
   pSpace = new Space(0, 0);
}
BoardEmpty::~BoardEmpty() 
{
   delete pSpace;
}
