/***********************************************************************
 * Header File:
 *    POSITION
 * Author:
 *    Ethan Leishman, Noah McSheehy, Bro. Helfrich
 * Summary:
 *    The position of a piece, the cursor, or a possible move on a chess board
 ************************************************************************/

#pragma once

#include <string>
#include <cstdint>
using std::string;
using std::ostream;
using std::istream;

const int SIZE_SQUARE  = 32;   // number of pixels in a square by default

/***********************************************
 * DELTA
 * Movement in a direction (dRow and dCol)
 **********************************************/
struct Delta
{
   int dRow;
   int dCol;
};

const Delta ADD_R = { 1,  0};
const Delta ADD_C = { 0,  1};
const Delta SUB_R = {-1,  0};
const Delta SUB_C = { 0, -1};


class PositionTest;

/***************************************************
 * POSITION
 * The location of a piece on the board
 ***************************************************/
class Position
{
   friend class PositionTest;
   friend class TestKnight;
   friend class TestBishop;
   friend class TestKing;
   friend class TestPawn;
   friend class TestRook;
   friend class TestQueen;
public:

   // Position :    The Position class can work with other positions,
   //               Allowing for comparisions, copying, etc.
   Position(const Position& rhs) : colRow(rhs.colRow) {   }
   Position() : colRow(0x99)      {                       }
   bool isInvalid() const         { return colRow & 0x88; }
   bool isValid()   const         { return !isInvalid();  }
   void setValid()                { colRow = 0x00;        }
   void setInvalid()
   {
      const bool colBad = (colRow & 0x80) != 0;
      const bool rowBad = (colRow & 0x08) != 0;

      if (colBad)
      {
         colRow = 0xFF;
      }
      else if (rowBad)
      {
         colRow = (colRow & 0xF0) | 0x0F;
      }
   }

   // Comparison operators
   bool operator <  (const Position & rhs) const { return colRow <  rhs.colRow; }
   bool operator == (const Position & rhs) const { return colRow == rhs.colRow; }
   bool operator != (const Position & rhs) const { return colRow != rhs.colRow; }
   const Position & operator =  (const Position & rhs) { colRow = rhs.colRow; return *this; }
   
   // Location : The Position class can work with locations, which
   //            are 0...63 where we start in row 0, then row 1, etc.
   Position(int location) : colRow(0x99){ setLocation(location); }
   int getLocation() const { return getRow() * 8 + getCol(); }
   void setLocation(int location)
   {
      int c = location % 8;
      int r = location / 8;
      set(c, r);
   }

   // Row/Col : The position class can work with row/column,
   //           which are 0..7 and 0...7
   Position(int c, int r)                 { set(c, r);                                               }
   virtual int getCol() const             { return (isInvalid() ? -1 : (int)((colRow & 0xf0) >> 4)); }
   virtual int getRow() const             { return (isInvalid() ? -1 : (int)((colRow & 0x0f) >> 0)); }
   void setRow(int r)                     { colRow = getCol() * 16 + r; setInvalid();                }
   void setCol(int c)                     { colRow = c * 16 + getRow(); setInvalid();                }
   void set(int c, int r)                 
   {
      colRow = (uint8_t)((c << 4) | (r & 0x0F));
      setInvalid();                
   }

   // Text:    The Position class can work with textual coordinates,
   //          such as "d4"
   Position(const char* s)
   {
      int col = *s - 'a'; ++s;
      int row = *s - '1';
      set(col, row);
   }
   const Position& operator =  (const char* rhs)
   {
      int col = rhs[0] - 'a';
      int row = rhs[1] - '1';
      set(col, row);
      return *this;
   }
   const Position& operator =  (const string& rhs)
   {
      int col = rhs[0] - 'a';
      int row = rhs[1] - '1';
      set(col, row);
      return *this;
   }

   
   // Pixels:    The Position class can work with screen coordinates,
   //            a.k.a. Pixels, these are X and Y coordinates. Note that
   //            we need to scale them according to the size of the board.
   int getX()   const
   {
      return (int)((double)getCol() * getSquareWidth() + getSquareWidth());
   }
   int getY()   const
   {
      return (int)((double)getRow() * getSquareHeight() + getSquareHeight());
   }
   void setXY(double x, double y)
   {
      int c = (int)(x / squareWidth) - 1;
      int r = 8 - (int)(y / squareHeight);

      colRow = (uint8_t)((c << 4) | (r & 0x0F));

      setInvalid();
   }
   double getSquareWidth()  const { return squareWidth;  }
   double getSquareHeight() const { return squareHeight; }
   void setBoardWidthHeight(int widthBoard, int heightBoard)
   {
      if (widthBoard < 0 || heightBoard < 0)
         return;
      squareWidth  = (double)widthBoard / 10.0; // 8 squares + 2 spaces
      squareHeight = (double)heightBoard / 10.0;
   }

   // Delta:    The Position class can work with deltas, which are
   //           offsets from a given location. This helps pieces move
   //           on the chess board.
   void adjustRow(int dRow)
   {
      int c = getCol();
      int r = getRow() + dRow;
      if (r < 0 || r > 7)
         colRow = 0xFF;
      else
         colRow = (uint8_t)((c << 4) | (r & 0x0F));
   }
   void adjustCol(int dCol)
   {
      int c = getCol() + dCol;
      int r = getRow();
      if (c < 0 || c > 7)
         colRow = 0xFF;
      else
         colRow = (uint8_t)((c << 4) | (r & 0x0F));
   }
   const Position& operator += (const Delta& rhs)
   {
      if (isValid())
      {
         adjustCol(rhs.dCol);
         adjustRow(rhs.dRow);
      }
      return *this;
   }
   Position operator + (const Delta& rhs) const
   {
      Position tmp = *this;
      tmp += rhs;
      return tmp;
   }

private:
   uint8_t colRow;
   static double squareWidth;
   static double squareHeight;
};

ostream& operator << (ostream& out, const Position& pos);
istream& operator >> (istream& in, Position& pos);

ostream & operator << (ostream & out, const Position & pos);
istream & operator >> (istream & in,  Position & pos);
