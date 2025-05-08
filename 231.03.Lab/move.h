/***********************************************************************
 * Header File:
 *    MOVE 
 * Author:
 *    Ethan Leishman, Noah McSheehy, Bro. Helfrich
 * Summary:
 *    Everything we need to know about a single chess move
 ************************************************************************/

#pragma once

#include <string>
#include "position.h"  // Every move has two Positions as attributes
#include "pieceType.h" // A piece type


class TestMove;
class TestBoard;

/***************************************************
 * MOVE
 * One move across the board
 ***************************************************/
class Move
{
public:
   enum MoveType { MOVE, ENPASSANT, CASTLE_KING, CASTLE_QUEEN, MOVE_ERROR };

   friend TestMove;
   friend TestBoard;

   // constructor
   Move();
   bool operator == (const Move & rhs) const { return source == rhs.source && dest == rhs.dest; }
   bool operator <  (const Move & rhs) const { return dest <  rhs.dest; }


private:
   char letterFromPieceType(PieceType pt)     const
   {
      switch(pt)
      {
         case SPACE:
            return ' ';
         case KING:
            return 'k';
         case QUEEN:
            return 'q';
         case ROOK:
            return 'r';
         case BISHOP:
            return 'b';
         case KNIGHT:
            return 'n';
         case PAWN:
            return 'p';
         case INVALID:
            return 'z';
      }
   }
   PieceType pieceTypeFromLetter(char letter) const
   {
      switch(letter)
      {
         case ' ':
            return SPACE;
         case 'k':
            return KING;
         case 'q':
            return QUEEN;
         case 'r':
            return ROOK;
         case 'b':
            return BISHOP;
         case 'n':
            return KNIGHT;
         case 'p':
            return PAWN;
         default:
            return INVALID;
      }
   }



   Position  source;    // where the move originated from
   Position  dest;      // where the move finished
   PieceType promote;   // piece to be promoted to
   PieceType capture;   // did a capture happen this move?
   MoveType  moveType;  // what type of move is this?
   bool      isWhite;   // whose turn is it anyway?
   string    text;      // what is the textual version of the move?
};


