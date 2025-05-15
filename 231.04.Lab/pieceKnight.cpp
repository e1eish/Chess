/***********************************************************************
 * Source File:
 *    KNIGHT
 * Author:
 *    <your name here>
 * Summary:
 *    The knight class
 ************************************************************************/

#include "pieceKnight.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Knight::display(ogstream* pgout) const
{
   pgout->drawKnight(this->position, this->fWhite);
}


/**********************************************
 * KNIGHT : GET POSITIONS
 *********************************************/
void Knight::getMoves(set <Move>& moves, const Board& board) const
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
         if (piece->getType() == SPACE)
         {
            m.setSource(position);
            m.setDest(Position(c,r));
            m.setCapture(SPACE);
            moves.insert(m);
         }
         else if (!fWhite && piece->isWhite())
         {
            m.setSource(position);
            m.setDest(Position(c,r));
            m.setCapture(piece->getType());
            moves.insert(m);
         }
         else if (fWhite && !piece->isWhite())
         {
            m.setSource(position);
            m.setDest(Position(c,r));
            m.setCapture(piece->getType());
            moves.insert(m);
         }
      }
   }
}
