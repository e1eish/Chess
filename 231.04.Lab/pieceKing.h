/***********************************************************************
 * Header File:
 *    KING
 * Author:
*    Ethan Leishman, Noah McSheehy
 * Summary:
 *    The KING class
 ************************************************************************/

#pragma once

#include "piece.h"

 /***************************************************
  * KING
  * The king
  ***************************************************/
class King : public Piece
{
public:
   King(const Position& pos, bool isWhite) : Piece(pos,isWhite) { }
   King(int c, int r, bool isWhite) : Piece(c, r, isWhite) { }
   ~King() {                }
   PieceType getType()            const { return KING; }
   void getMoves(set <Move>& moves, const Board& board) const;
   void display(ogstream* pgout)  const;
private:
   void addMove(set <Move>& moves, const Position & dest, const Move::MoveType moveType) const
   {
      Move m;
      m.setSource(position);
      m.setDest(dest);
      m.setMoveType(moveType);
      m.setPromote(INVALID);
      moves.insert(m);
   }
};
