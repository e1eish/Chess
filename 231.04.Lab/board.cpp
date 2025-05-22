/***********************************************************************
 * Source File:
 *    BOARD 
 * Author:
 *    Ethan Leishman, Noah McSheehy, Bro. Helfrich
 * Summary:
 *    A collection of pieces and a small amount of game state
 ************************************************************************/

#include "board.h"
#include "uiDraw.h"
#include "position.h"
#include "piece.h"
#include "pieceSpace.h"
#include "pieceKnight.h"
#include "piecePawn.h"
#include "pieceRook.h"
#include "pieceBishop.h"
#include "pieceQueen.h"
#include "pieceKing.h"
#include <cassert>
using namespace std;


/***********************************************
 * BOARD : RESET
 *         Just fill the board with the known pieces
 *   +---a-b-c-d-e-f-g-h---+
 *   |                     |
 *   8   R N B Q K B N R   8
 *   7   P P P P P P P P   7
 *   6                     6
 *   5                     5
 *   4                     4
 *   3                     3
 *   2   p p p p p p p p   2
 *   1   r n b q k b n r   1
 *   |                     |
 *   +---a-b-c-d-e-f-g-h---+
 ***********************************************/
void Board::reset(bool fFree)
{
   if (fFree)
      free();
   
   // free everything
   for (int r = 0; r < 8; r++)
      for (int c = 0; c < 8; c++)
            board[c][r] = nullptr;
   
   for (int c = 0; c < 8; c++)
   {
      board[c][1] = new Pawn(c,1, true /*white*/);
      board[c][6] = new Pawn(c,6, false /*black*/);
   }
   
   board[0][0] = new Rook(0,0, true /*white*/);
   board[7][0] = new Rook(7,0, true /*white*/);
   board[0][7] = new Rook(0,7, false /*black*/);
   board[7][7] = new Rook(7,7, false /*black*/);
   
   board[1][0] = new Knight(1,0, true /*white*/);
   board[6][0] = new Knight(6,0, true /*white*/);
   board[1][7] = new Knight(1,7, false  /*black*/);
   board[6][7] = new Knight(6,7, false  /*black*/);
   
   board[2][0] = new Bishop(2,0, true /*white*/);
   board[5][0] = new Bishop(5,0, true /*white*/);
   board[2][7] = new Bishop(2,7, false  /*black*/);
   board[5][7] = new Bishop(5,7, false  /*black*/);
   
   board[3][0] = new Queen(3,0, true /*white*/);
   board[3][7] = new Queen(3,7, false  /*black*/);
   
   board[4][0] = new King(4,0, true /*white*/);
   board[4][7] = new King(4,7, false  /*black*/);
   
   for (int r = 0; r < 8; r++)
      for (int c = 0; c < 8; c++)
         if (nullptr == board[c][r])
            board[c][r] = new Space(c, r);
   
   numMoves = 0;
   assertBoard();
}

// we really REALLY need to delete this.
Space space(0,0);

/***********************************************
* BOARD : GET
*         Get a piece from a given position.
***********************************************/
const Piece& Board::operator [] (const Position& pos) const
{
   assert(pos.getCol() < 8 && pos.getCol() >= 0);
   assert(pos.getRow() < 8 && pos.getRow() >= 0);
   if (board[pos.getCol()][pos.getRow()])
      return *(board[pos.getCol()][pos.getRow()]);
   else
      return *pSpace;
}
Piece& Board::operator [] (const Position& pos)
{
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
   pgout->drawBoard();
   
   pgout->drawHover(posHover);
   pgout->drawSelected(posSelect);
   
   for (int r = 0; r < 8; r++)
      for (int c = 0; c < 8; c++)
         board[c][r]->display(pgout);
}


/************************************************
 * BOARD : CONSTRUCT
 *         Free up all the allocated memory
 ************************************************/
Board::Board(ogstream* pgout, bool noreset) : pgout(pgout), numMoves(0)
{
   pSpace = new Space(0,0);
   /*if (!noreset)
      reset(true);
   else
      for (int r = 0; r < 8; r++)
         for (int c = 0; c < 8; c++)
            board[c][r] = nullptr;*/
   for (int r = 0; r < 8; r++)
      for (int c = 0; c < 8; c++)
         board[c][r] = nullptr;
   
   if (!noreset)
      reset(false);
}


/************************************************
 * BOARD : FREE
 *         Free up all the allocated memory
 ************************************************/
void Board::free()
{
   for (int r = 0; r < 8; r++)
      for (int c = 0; c < 8; c++)
         if (board[c][r] != nullptr)
            delete board[c][r];
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
   if (move.getCapture() == SPACE)
   {
      Piece * space = board[move.getDest().getCol()][move.getDest().getRow()];
      board[move.getDest().getCol()][move.getDest().getRow()] = board[move.getSource().getCol()][move.getSource().getRow()]; // move piece to destination
      board[move.getSource().getCol()][move.getSource().getRow()] = space; // move space to source
   }
   else
   {
      delete board[move.getDest().getCol()][move.getDest().getRow()];
      board[move.getDest().getCol()][move.getDest().getRow()] = board[move.getSource().getCol()][move.getSource().getRow()]; // move piece to destination
      board[move.getSource().getCol()][move.getSource().getRow()] = new Space(move.getSource().getCol(), move.getSource().getRow()); // replace source with space
   }
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
