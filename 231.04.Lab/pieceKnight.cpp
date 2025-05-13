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
         if (!fWhite && board[p].isWhite())
         {
            m.setSource(position);
            m.setDest(Position(c,r));
            m.setCapture(board[p].getType());
            moves.insert(m);
         }
         if (fWhite && !board[p].isWhite())
         {
            m.setSource(position);
            m.setDest(Position(c,r));
            m.setCapture(board[p].getType());
            moves.insert(m);
         }
      }
   }
}
