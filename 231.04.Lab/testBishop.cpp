/***********************************************************************
 * Source File:
 *    TEST BISHOP
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for a bishop
 ************************************************************************/


#include "testBishop.h"
#include "pieceBishop.h"     
#include "board.h"
#include "uiDraw.h"
#include <cassert>      

 /*************************************
  * +---a-b-c-d-e-f-g-h---+
  * |                     |
  * 8                     8
  * 7                     7
  * 6                     6
  * 5                     5
  * 4                     4
  * 3     p   p           3
  * 2      (b)            2
  * 1     p   p           1
  * |                     |
  * +---a-b-c-d-e-f-g-h---+
  **************************************/
void TestBishop::getMoves_blocked()
{  // SETUP
   BoardEmpty board;
   Bishop bishop(7, 7, false /*white*/); // we will reset all this.
   bishop.fWhite = true;
   bishop.position.colRow = 0x21;
   board.board[2][1] = &bishop;
   White white(PAWN);
   board.board[1][0] = &white; // Bottom left
   board.board[1][2] = &white; // Upper  left
   board.board[3][0] = &white; // Upper  Right
   board.board[3][2] = &white; // Bottom Right
   set <Move> moves;

   // EXERCISE
   bishop.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 0); // No possible moves

   // TEARDOWN
   board.board[2][1] = nullptr; // Bishop
   board.board[1][0] = nullptr; // Bottom left  Pawn
   board.board[1][2] = nullptr; // Upper  left  Pawn
   board.board[3][0] = nullptr; // Upper  Right Pawn
   board.board[3][2] = nullptr; // Bottom Right Pawn
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 .   7
 * 6               .     6
 * 5             .       5
 * 4   .       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     .   .           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_slideToEnd()
{  // SETUP
   BoardEmpty board;
   Bishop bishop(7, 7, false /*white*/); // we will reset all this.
   bishop.fWhite = true;
   bishop.position.colRow = 0x21;
   board.board[2][1] = &bishop;
   set <Move> moves;

   Move c2a4;
   Move c2b1;
   Move c2b3;
   Move c2d1;
   Move c2d3;
   Move c2e4;
   Move c2f5;
   Move c2g6;
   Move c2h7;

   c2a4.source.colRow =
      c2b1.source.colRow =
      c2b3.source.colRow =
      c2d1.source.colRow =
      c2d3.source.colRow =
      c2e4.source.colRow =
      c2f5.source.colRow =
      c2g6.source.colRow =
      c2h7.source.colRow = 0x21;

   c2a4.capture =
      c2b1.capture =
      c2b3.capture =
      c2d1.capture =
      c2d3.capture =
      c2e4.capture =
      c2f5.capture =
      c2g6.capture =
      c2h7.capture = SPACE;

   c2a4.capture =
      c2b1.capture =
      c2d1.capture =
      c2d3.capture =
      c2e4.capture =
      c2f5.capture =
      c2b3.capture =
      c2g6.capture =
      c2h7.capture =
      c2a4.capture = SPACE;

   c2a4.dest.colRow = 0x03;
   c2b1.dest.colRow = 0x10;
   c2b3.dest.colRow = 0x12;
   c2d1.dest.colRow = 0x30;
   c2d3.dest.colRow = 0x32;
   c2e4.dest.colRow = 0x43;
   c2f5.dest.colRow = 0x54;
   c2g6.dest.colRow = 0x65;
   c2h7.dest.colRow = 0x76;

   // EXERCISE
   bishop.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 9);  // 9 possible moves
   assertUnit(moves.find(c2a4) != moves.end());
   assertUnit(moves.find(c2b1) != moves.end());
   assertUnit(moves.find(c2b3) != moves.end());
   assertUnit(moves.find(c2d1) != moves.end());
   assertUnit(moves.find(c2d3) != moves.end());
   assertUnit(moves.find(c2e4) != moves.end());
   assertUnit(moves.find(c2f5) != moves.end());
   assertUnit(moves.find(c2g6) != moves.end());
   assertUnit(moves.find(c2h7) != moves.end());

   // TEARDOWN
   board.board[2][1] = nullptr; // Bishop
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 p   7
 * 6               .     6
 * 5             .       5
 * 4   p       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     p   p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_slideToBlock()
{  // SETUP
   BoardEmpty board;
   Bishop bishop(7, 7, false /*white*/); // we will reset all this.
   bishop.fWhite = true;
   bishop.position.colRow = 0x21;
   board.board[2][1] = &bishop; // C2 White Bishop

   White white(PAWN);
   board.board[0][3] = &white; // A4 White Pawn
   board.board[1][0] = &white; // B1 White Pawn
   board.board[3][0] = &white; // D1 White Pawn
   board.board[7][6] = &white; // H7 White Pawn

   set <Move> moves;
   Move c2b3;
   Move c2d3;
   Move c2e4;
   Move c2f5;
   Move c2g6;

   c2b3.source.colRow =
      c2d3.source.colRow =
      c2e4.source.colRow =
      c2f5.source.colRow =
      c2g6.source.colRow = 0x21;

   c2b3.capture =
      c2d3.capture =
      c2e4.capture =
      c2f5.capture =
      c2g6.capture = SPACE;

   c2b3.dest.colRow = 0x12;
   c2d3.dest.colRow = 0x32;
   c2e4.dest.colRow = 0x43;
   c2f5.dest.colRow = 0x54;
   c2g6.dest.colRow = 0x65;

   // EXERCISE
   bishop.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 5); // 5 possible moves
   assertUnit(moves.find(c2b3) != moves.end());
   assertUnit(moves.find(c2d3) != moves.end());
   assertUnit(moves.find(c2e4) != moves.end());
   assertUnit(moves.find(c2f5) != moves.end());
   assertUnit(moves.find(c2g6) != moves.end());

   // TEARDOWN
   board.board[2][1] = nullptr; // White Bishop C2
   board.board[1][0] = nullptr; // White Pawn   B1
   board.board[3][0] = nullptr; // White Pawn   D1
   board.board[7][6] = nullptr; // White Pawn   H7
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 P   7
 * 6               .     6
 * 5             .       5
 * 4   P       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     P   P           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_slideToCapture()
{  // SETUP
   BoardEmpty board;
   Bishop bishop(7, 7, false /*white*/); // we will reset all this.
   bishop.fWhite = true;
   bishop.position.colRow = 0x21;
   board.board[2][1] = &bishop;
   Black black(PAWN);
   board.board[0][3] = &black; // A4 Black Pawn
   board.board[1][0] = &black; // B1 Black Pawn
   board.board[3][0] = &black; // D1 Black Pawn
   board.board[7][6] = &black; // H& Black Pawn

   set <Move> moves;

   Move c2a4;
   Move c2b1;
   Move c2b3;
   Move c2d1;
   Move c2d3;
   Move c2e4;
   Move c2f5;
   Move c2g6;
   Move c2h7;

   c2a4.source.colRow =
      c2b1.source.colRow =
      c2b3.source.colRow =
      c2d1.source.colRow =
      c2d3.source.colRow =
      c2e4.source.colRow =
      c2f5.source.colRow =
      c2g6.source.colRow =
      c2h7.source.colRow = 0x21;

   c2a4.capture = PAWN;
   c2b1.capture = PAWN;
   c2b3.capture = SPACE;
   c2d1.capture = PAWN;
   c2d3.capture = SPACE;
   c2e4.capture = SPACE;
   c2f5.capture = SPACE;
   c2g6.capture = SPACE;
   c2h7.capture = PAWN;

   c2a4.dest.colRow = 0x03;
   c2b1.dest.colRow = 0x10;
   c2b3.dest.colRow = 0x12;
   c2d1.dest.colRow = 0x30;
   c2d3.dest.colRow = 0x32;
   c2e4.dest.colRow = 0x43;
   c2f5.dest.colRow = 0x54;
   c2g6.dest.colRow = 0x65;
   c2h7.dest.colRow = 0x76;

   // EXERCISE
   bishop.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 9); // 9 possible moves
   assertUnit(moves.find(c2a4) != moves.end());
   assertUnit(moves.find(c2b1) != moves.end());
   assertUnit(moves.find(c2b3) != moves.end());
   assertUnit(moves.find(c2d1) != moves.end());
   assertUnit(moves.find(c2d3) != moves.end());
   assertUnit(moves.find(c2e4) != moves.end());
   assertUnit(moves.find(c2f5) != moves.end());
   assertUnit(moves.find(c2g6) != moves.end());
   assertUnit(moves.find(c2h7) != moves.end());

   // TEARDOWN
   board.board[2][1] = nullptr; // White Bishop C2
   board.board[1][0] = nullptr; // Black Pawn   B1
   board.board[3][0] = nullptr; // Black Pawn   D1
   board.board[7][6] = nullptr; // Black Pawn   H7
}


/*************************************
 * GET TYPE : bishop
 * Input:
 * Output: BISHOP
 **************************************/
void TestBishop::getType()
{
   // SETUP  
   const Bishop bishop(7, 7, false /*white*/);
   PieceType pt = SPACE;

   // EXERCISE
   pt = bishop.getType();

   // VERIFY
   assertUnit(pt == BISHOP);
}  // TEARDOWN
