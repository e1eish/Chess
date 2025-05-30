/***********************************************************************
 * Source File:
 *    PAWN
 * Author:
 *    Ethan Leishman, Noah McSheehy, Bro. Helfrich
 * Summary:
 *    The pawn class
 ************************************************************************/

#include "piecePawn.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Pawn::display(ogstream* pgout) const
{
   pgout->drawPawn(position, !fWhite);
}


/**********************************************
 * PAWN : GET POSITIONS
 *********************************************/
void Pawn::getMoves(set <Move>& moves, const Board& board) const
{
   int r;
   int c;
   Position p;
   Move m;
   const Piece * piece;
   int rowDiff;
   
   if (fWhite)       // for moving forward for white and backwards for black
      rowDiff =  1;
   else
      rowDiff = -1;
   
   // normal forward move
   r = position.getRow() + rowDiff;
   c = position.getCol();
   p = Position(c,r);
   if (p.isValid())
   {
      piece = &board[p];
      if (piece->getType() == SPACE)
      {
         addMove(moves, p, piece->getType());
         // first move double
         if (nMoves == 0)
         {
            r += rowDiff;
            p = Position(c,r);
            if (p.isValid())
            {
               piece = &board[p];
               if (piece->getType() == SPACE)
                  addMove(moves, p, piece->getType());
            }
         }
      }
   }
   
   // attack right
   r = position.getRow() + rowDiff;
   c = position.getCol() + 1;
   p = Position(c,r);
   for (int i = 0; i < 2; i++)  // loop over to get the other side
   {
      if (p.isValid())
      {
         piece = &board[p];
         if (piece->getType() != SPACE && fWhite != piece->isWhite())
            addMove(moves, p, piece->getType());
      }
      // attack left
      c = position.getCol() - 1;
      p = Position(c,r);
   }
   
   // enpassant right
   p = Position(position.getCol() + 1, position.getRow());
   for (int i = 0; i < 2; i++)  // loop over to get the other side
   {
      if (p.isValid())
      {
         piece = &board[p];
         if (piece->getType() == PAWN &&
             ((fWhite && position.getRow() == 4) || (!fWhite && position.getRow() == 3)) && // ensure enemy pawn did a double move by checking the row
             piece->isWhite() != fWhite &&
             piece->getNMoves() == 1 &&
             piece->justMoved(board.getCurrentMove()))
         {
            p.setRow(p.getRow() + rowDiff);
            addMove(moves, p, PAWN, true);
         }
      }
      // enpassant left
      c = position.getCol() - 1;
      r = position.getRow();
      p = Position(c, r);
   }
}
