/***********************************************************************
 * Source File:
 *    KING
 * Author:
 *    Ethan Leishman, Noah McSheehy, Bro. Helfrich
 * Summary:
 *    The king class
 ************************************************************************/

#include "pieceKing.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void King::display(ogstream* pgout) const
{
   pgout->drawKing(position, fWhite);
}


/**********************************************
 * KING : GET POSITIONS
 *********************************************/
void King::getMoves(set <Move>& moves, const Board& board) const
{
   int r;
   int c;
   Position p;
   Move m;
   const Piece * piece;
   CR directions[8] =
   {
            {-1,  2}, { 1,  2},
   {-2,  1},                    { 2,  1},
   {-2, -1},                    { 2, -1},
            {-1, -2}, { 1, -2}
   };
   for (int i = 0; i < 8; i++)
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
            m.setDest(Position(c,r));
            m.setCapture(piece->getType());
            moves.insert(m);
         }
      }
   }
}
