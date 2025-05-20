/***********************************************************************
 * Source File:
 *    ROOK
 * Author:
 *    Ethan Leishman, Noah McSheehy, Bro. Helfrich
 * Summary:
 *    The rook class
 ************************************************************************/

#include "pieceRook.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Rook::display(ogstream* pgout) const
{
   pgout->drawRook(position, fWhite);
}


/**********************************************
 * ROOK : GET POSITIONS
 *********************************************/
void Rook::getMoves(set <Move>& moves, const Board& board) const
{
   CR directions[4] =
   {
               {0,  1},
      {-1, 0},         {1, 0},
               {0, -1}
   };
   
   Piece::getMovesSlide(directions, sizeof(directions) / sizeof(directions[0]), board, moves);
}
