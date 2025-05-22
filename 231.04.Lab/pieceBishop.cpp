/***********************************************************************
 * Source File:
 *    BISHOP
 * Author:
 *    Ethan Leishman, Noah McSheehy, Bro. Helfrich
 * Summary:
 *    The bishop class
 ************************************************************************/

#include "pieceBishop.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Bishop::display(ogstream* pgout) const
{
   pgout->drawBishop(position, fWhite);
}


/**********************************************
 * BISHOP : GET POSITIONS
 *********************************************/
void Bishop::getMoves(set <Move>& moves, const Board& board) const
{
   CR directions[4] =
   {
      {-1,  1}, {1,  1},
      {-1, -1}, {1, -1}
   };
   
   getMovesSlide(directions, sizeof(directions) / sizeof(directions[0]), board, moves);
}
