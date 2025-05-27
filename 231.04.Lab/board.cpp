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
void Board::display(const Position & posHover, const Position & posSelect, set <Move>& possible) const
{
   pgout->drawBoard();
   
   pgout->drawHover(posHover);
   pgout->drawSelected(posSelect);
   
   if (possible.size() > 0)
   {
      // draw the possible moves
      set <Move> :: iterator it;
      for (it = possible.begin(); it != possible.end(); ++it)
         (*pgout).drawPossible((*it).getDest());
   }
   
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
   assert(0 == numMoves);
   assert(ROOK   == (board[0][0])->getType());
   assert(KNIGHT == (board[1][0])->getType());
   assert(BISHOP == (board[2][0])->getType());
   assert(QUEEN  == (board[3][0])->getType());
   assert(KING   == (board[4][0])->getType());
   assert(BISHOP == (board[5][0])->getType());
   assert(KNIGHT == (board[6][0])->getType());
   assert(ROOK   == (board[7][0])->getType());
   assert(true   == (board[0][0])->isWhite());
   assert(true   == (board[1][0])->isWhite());
   assert(true   == (board[2][0])->isWhite());
   assert(true   == (board[3][0])->isWhite());
   assert(true   == (board[4][0])->isWhite());
   assert(true   == (board[5][0])->isWhite());
   assert(true   == (board[6][0])->isWhite());
   assert(true   == (board[7][0])->isWhite());
   
   assert(PAWN == (board[0][1])->getType());
   assert(PAWN == (board[1][1])->getType());
   assert(PAWN == (board[2][1])->getType());
   assert(PAWN == (board[3][1])->getType());
   assert(PAWN == (board[4][1])->getType());
   assert(PAWN == (board[5][1])->getType());
   assert(PAWN == (board[6][1])->getType());
   assert(PAWN == (board[7][1])->getType());
   assert(true == (board[0][1])->isWhite());
   assert(true == (board[1][1])->isWhite());
   assert(true == (board[2][1])->isWhite());
   assert(true == (board[3][1])->isWhite());
   assert(true == (board[4][1])->isWhite());
   assert(true == (board[5][1])->isWhite());
   assert(true == (board[6][1])->isWhite());
   assert(true == (board[7][1])->isWhite());
   
   assert(SPACE == (board[0][2])->getType());
   assert(SPACE == (board[1][2])->getType());
   assert(SPACE == (board[2][2])->getType());
   assert(SPACE == (board[3][2])->getType());
   assert(SPACE == (board[4][2])->getType());
   assert(SPACE == (board[5][2])->getType());
   assert(SPACE == (board[6][2])->getType());
   assert(SPACE == (board[7][2])->getType());
   
   assert(SPACE == (board[0][3])->getType());
   assert(SPACE == (board[1][3])->getType());
   assert(SPACE == (board[2][3])->getType());
   assert(SPACE == (board[3][3])->getType());
   assert(SPACE == (board[4][3])->getType());
   assert(SPACE == (board[5][3])->getType());
   assert(SPACE == (board[6][3])->getType());
   assert(SPACE == (board[7][3])->getType());
   
   assert(SPACE == (board[0][4])->getType());
   assert(SPACE == (board[1][4])->getType());
   assert(SPACE == (board[2][4])->getType());
   assert(SPACE == (board[3][4])->getType());
   assert(SPACE == (board[4][4])->getType());
   assert(SPACE == (board[5][4])->getType());
   assert(SPACE == (board[6][4])->getType());
   assert(SPACE == (board[7][4])->getType());
   
   assert(SPACE == (board[0][5])->getType());
   assert(SPACE == (board[1][5])->getType());
   assert(SPACE == (board[2][5])->getType());
   assert(SPACE == (board[3][5])->getType());
   assert(SPACE == (board[4][5])->getType());
   assert(SPACE == (board[5][5])->getType());
   assert(SPACE == (board[6][5])->getType());
   assert(SPACE == (board[7][5])->getType());
   
   assert(PAWN  == (board[0][6])->getType());
   assert(PAWN  == (board[1][6])->getType());
   assert(PAWN  == (board[2][6])->getType());
   assert(PAWN  == (board[3][6])->getType());
   assert(PAWN  == (board[4][6])->getType());
   assert(PAWN  == (board[5][6])->getType());
   assert(PAWN  == (board[6][6])->getType());
   assert(PAWN  == (board[7][6])->getType());
   assert(false == (board[0][6])->isWhite());
   assert(false == (board[1][6])->isWhite());
   assert(false == (board[2][6])->isWhite());
   assert(false == (board[3][6])->isWhite());
   assert(false == (board[4][6])->isWhite());
   assert(false == (board[5][6])->isWhite());
   assert(false == (board[6][6])->isWhite());
   assert(false == (board[7][6])->isWhite());
   
   assert(ROOK    == (board[0][7])->getType());
   assert(KNIGHT  == (board[1][7])->getType());
   assert(BISHOP  == (board[2][7])->getType());
   assert(QUEEN   == (board[3][7])->getType());
   assert(KING    == (board[4][7])->getType());
   assert(BISHOP  == (board[5][7])->getType());
   assert(KNIGHT  == (board[6][7])->getType());
   assert(ROOK    == (board[7][7])->getType());
   assert(false   == (board[0][7])->isWhite());
   assert(false   == (board[1][7])->isWhite());
   assert(false   == (board[2][7])->isWhite());
   assert(false   == (board[3][7])->isWhite());
   assert(false   == (board[4][7])->isWhite());
   assert(false   == (board[5][7])->isWhite());
   assert(false   == (board[6][7])->isWhite());
   assert(false   == (board[7][7])->isWhite());
}




/**********************************************
 * BOARD : MOVE
 *         Execute a move according to the contained instructions
 *   INPUT move The instructions of the move
 *********************************************/
void Board::move(const Move & move)
{
   Move::MoveType mt = move.getMoveType();
   Position source   = move.getSource();
   Position dest     = move.getDest();
   
   if (move.getCapture() == SPACE)  // normal move
   {
      Piece * space = board[dest.getCol()][dest.getRow()];
      
      board[dest.getCol()][dest.getRow()] = board[source.getCol()][source.getRow()]; // move piece to destination
      board[dest.getCol()][dest.getRow()]->setLastMove(numMoves);
      board[dest.getCol()][dest.getRow()]->setPosition(dest);
      
      board[source.getCol()][source.getRow()] = space; // move space to source
   }
   else // normal capture
   {
      delete board[dest.getCol()][dest.getRow()];
      board[dest.getCol()][dest.getRow()] = board[source.getCol()][source.getRow()]; // move piece to destination
      board[dest.getCol()][dest.getRow()]->setLastMove(numMoves);
      board[dest.getCol()][dest.getRow()]->setPosition(dest);
      
      board[source.getCol()][source.getRow()] = new Space(source.getCol(), source.getRow()); // replace source with space
   }
   
   if (mt == Move::CASTLE_KING)
   {
      int row = (board[dest.getCol()][dest.getRow()]->isWhite()) ? 0 : 7;
      Piece * space = board[5][row];
      board[5][row] = board[7][row];
      board[5][row]->setLastMove(numMoves);
      Position pos(5,row);
      board[5][row]->setPosition(pos);
      
      board[7][row] = space;
   }
   if (mt == Move::CASTLE_QUEEN)
   {
      int row = (board[dest.getCol()][dest.getRow()]->isWhite()) ? 0 : 7;
      Piece * space = board[3][row];
      board[3][row] = board[0][row];
      board[3][row]->setLastMove(numMoves);
      Position pos(3,row);
      board[3][row]->setPosition(pos);
      
      board[0][row] = space;
   }
   if (mt == Move::ENPASSANT)
   {
      int diff = (whiteTurn()) ? 1 : -1;
      delete board[dest.getCol()][dest.getRow() + diff];
      board[dest.getCol()][dest.getRow() + diff] = new Space(dest.getCol(), dest.getRow() + diff);
   }

   if (move.getPromote() != SPACE && move.getPromote() != INVALID)
   {
      delete board[dest.getCol()][dest.getRow()];
      Piece * newPiece;
      switch (move.getPromote())
      {
         case QUEEN:
            newPiece = new Queen(dest.getCol(), dest.getRow(), whiteTurn());
            break;
            
         case ROOK:
            newPiece = new Rook(dest.getCol(), dest.getRow(), whiteTurn());
            break;
            
         case BISHOP:
            newPiece = new Bishop(dest.getCol(), dest.getRow(), whiteTurn());
            break;
            
         case KNIGHT:
            newPiece = new Knight(dest.getCol(), dest.getRow(), whiteTurn());
            break;
            
         default:
            newPiece = new Pawn(dest.getCol(), dest.getRow(), whiteTurn());
            break;
      }
      
      board[dest.getCol()][dest.getRow()] = newPiece;
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
