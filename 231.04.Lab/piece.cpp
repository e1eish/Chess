/***********************************************************************
 * Source File:
 *    PIECE 
 * Author:
 *    Ethan Leishman, Noah McSheehy, Bro. Helfrich
 * Summary:
 *    The Piece base class and all the derived classes:
 *       SPACE, KING, QUEEN, ROOK, KNIGHT, BISHOP, PAWN
 ************************************************************************/

#include "position.h"  // for POSITION
#include "piece.h"     // for all the PIECE class definitions
#include "pieceSpace.h"
#include "pieceKnight.h"
#include "board.h"     // for BOARD
#include "uiDraw.h"    // for draw*()
#include <cassert>     // because we are paranoid
using namespace std;


/************************************************
 * PIECE : ASSIGN
 ***********************************************/
const Piece & Piece::operator = (const Piece & rhs)
{
   nMoves   = rhs.nMoves;
   fWhite   = rhs.fWhite;
   position = rhs.position;
   lastMove = rhs.lastMove;
   return *this;
}

/************************************************
 * PIECE : GET MOVES
 * Iterate through the moves decorator to allow a piece to move
 ***********************************************/
void Piece::getMoves(set <Move> & movesSet, const Board & board) const
{
}

/************************************************
 * PIECE : GET MOVES NO SLIDE
 * Get moves that don't slide from directions given
 ***********************************************/
void Piece::getMovesNoSlide(CR directions[], int size, const Board& board, set <Move>& moves) const
{
   int r;
   int c;
   Position p;
   Move m;
   const Piece * piece;
   for (int i = 0; i < size; i++)
   {
      r = position.getRow() + directions[i].row;
      c = position.getCol() + directions[i].col;
      p = Position(c,r);
      
      if (p.isValid())
      {
         piece = &board[p];
         if (   (piece->getType() == SPACE)    // if the capture target is a space
             || (!fWhite && piece->isWhite())  // or the piece is black and the capture target is white
             || (fWhite && !piece->isWhite())) // or the piece is white and the capture target is black
         {
            m.setSource(position);
            m.setDest(p);
            m.setCapture(piece->getType());
            moves.insert(m);
         }
      }
   }
}
/************************************************
 * PIECE : GET MOVES SLIDE
 * Get moves that slide from directions given
 ***********************************************/
void Piece::getMovesSlide(CR directions[], int size, const Board& board, set <Move>& moves) const
{
   int r;
   int c;
   Position p;
   Move m;
   const Piece * piece;
   for (int i = 0; i < size; i++)
   {
      r = position.getRow() + directions[i].row;
      c = position.getCol() + directions[i].col;
      p = Position(c,r);
      while (p.isValid())
      {
         piece = &board[p];
         if (   (piece->getType() == SPACE)    // if the capture target is a space
             || (!fWhite && piece->isWhite())  // or the piece is black and the capture target is white
             || (fWhite && !piece->isWhite())) // or the piece is white and the capture target is black
         {
            m.setSource(position);
            m.setDest(p);
            m.setCapture(piece->getType());
            moves.insert(m);
         }
         r += directions[i].row;
         c += directions[i].col;
         p = Position(c,r);
      }
      
   }
}
