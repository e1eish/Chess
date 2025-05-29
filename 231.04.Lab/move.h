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
   friend class TestKnight;
   friend class TestBishop;
   friend class TestKing;
   friend class TestPawn;
   friend class TestRook;
   friend class TestQueen;

   // constructor
   Move();
   Move(const string & rhs) { *this = rhs; }
   bool operator == (const Move & rhs) const { return source == rhs.source && dest == rhs.dest; }
   bool operator <  (const Move & rhs) const { return dest <  rhs.dest; }
   const Move & operator = (const string & rhs)
   {
      text = rhs;
      source = rhs.substr(0,2);
      dest   = rhs.substr(2,4);
      if (rhs.length() > 4)
      {
         for (auto it = rhs.cbegin() + 4; it != rhs.end(); ++it)
         {
            switch (*it)
            {
               case 'p':   // capture a pawn
               case 'n':   // capture a knight
               case 'b':   // capture a bishop
               case 'r':   // capture a rook
               case 'q':   // capture a queen
                  capture  = pieceTypeFromLetter(*it);
                  moveType = MOVE;
                  promote  = INVALID;
                  break;
                  
               case 'c':  // king side castle
                  moveType = CASTLE_KING;
                  promote = INVALID;
                  break;
               case 'C':  // queen side castle
                  moveType = CASTLE_QUEEN;
                  promote = INVALID;
                  break;
                  
               case 'E':  // enpassant
                  moveType = ENPASSANT;
                  capture = PAWN;
                  promote = INVALID;
                  break;
                  
               case 'N':  // promote to knight
                  promote = KNIGHT;
                  break;
               case 'B':  // promote to bishop
                  promote = BISHOP;
                  break;
               case 'R':  // promote to rook
                  promote = ROOK;
                  break;
               case 'Q':  // promote to queen
                  promote = QUEEN;
                  break;
            }
         }
      }
      else
      {
         moveType = MOVE;
         capture  = INVALID;
         promote  = INVALID;
      }
      return *this;
   }
   
   void read(const string & s) { *this = s; }
   string getText()
   {
      string moveString;
      moveString.push_back(source.getCol() + 'a');
      moveString.push_back(source.getRow() + '1');
      moveString.push_back(dest.getCol() + 'a');
      moveString.push_back(dest.getRow() + '1');
      if (moveType == ENPASSANT)
         moveString.push_back('E');
      else if (moveType == CASTLE_KING)
         moveString.push_back('c');
      else if (moveType == CASTLE_QUEEN)
         moveString.push_back('C');
      else if (capture)
         if (capture != INVALID && capture != SPACE)
            moveString.push_back(letterFromPieceType(capture));
      
      return moveString;
   }
   
   // setters
   void setSource(const Position & pos) { source   = pos; text = getText(); }
   void setDest(const Position & pos)   { dest     = pos; text = getText(); }
   void setCapture(const PieceType pt)  { capture  = pt;  text = getText(); }
   void setMoveType(const MoveType mt)  { moveType = mt;  text = getText(); }
   void setPromote(const PieceType pt)  { promote  = pt;  text = getText(); }
   
   // getters
   const Position & getSource()  const { return source;  }
   const Position & getDest()    const { return dest;    }
   PieceType  getCapture()  const { return capture;  }
   MoveType   getMoveType() const { return moveType; }
   PieceType  getPromote()  const { return promote;  }


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


