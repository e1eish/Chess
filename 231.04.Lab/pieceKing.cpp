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
   pgout->drawKing(position, !fWhite);
}


/**********************************************
 * KING : GET POSITIONS
 *********************************************/
void King::getMoves(set <Move>& moves, const Board& board) const
{
   CR directions[8] =
   {
      {-1,  1}, {0,  1}, {1,  1},
      {-1,  0},          {1,  0},
      {-1, -1}, {0, -1}, {1, -1}
   };

   Piece::getMovesNoSlide(directions, sizeof(directions) / sizeof(directions[0]), board, moves);
   
   if (nMoves == 0)
   {
      // castle king-side
      Move m;
      Position p;
      const Piece * piece;
      
      // white
      p = "h1";
      piece = &board[p];
      if (fWhite == true &&
          piece->getType() == ROOK && piece->isWhite() == true && piece->getNMoves() == 0 &&
          board[Position("f1")].getType() == SPACE &&
          board[Position("g1")].getType() == SPACE)
      {
         addMove(moves, Position("g1"), Move::CASTLE_KING);
      }
      // castle queen-side
      p = "a1";
      piece = &board[p];
      if (fWhite == true &&
          piece->getType() == ROOK && piece->isWhite() == true && piece->getNMoves() == 0 &&
          board[Position("b1")].getType() == SPACE &&
          board[Position("c1")].getType() == SPACE &&
          board[Position("d1")].getType() == SPACE)
      {
         addMove(moves, Position("c1"), Move::CASTLE_QUEEN);
      }
      
      // black
      // castle king-side
      p = "h8";
      piece = &board[p];
      if (fWhite == false &&
          piece->getType() == ROOK && piece->isWhite() == false && piece->getNMoves() == 0 &&
          board[Position("f8")].getType() == SPACE &&
          board[Position("g8")].getType() == SPACE)
      {
         addMove(moves, Position("g8"), Move::CASTLE_KING);
      }
      // castle queen-side
      p = "a8";
      piece = &board[p];
      if (fWhite == false &&
          piece->getType() == ROOK && piece->isWhite() == false && piece->getNMoves() == 0 &&
          board[Position("b8")].getType() == SPACE &&
          board[Position("c8")].getType() == SPACE &&
          board[Position("d8")].getType() == SPACE)
      {
         addMove(moves, Position("c8"), Move::CASTLE_QUEEN);
      }
   }
}
