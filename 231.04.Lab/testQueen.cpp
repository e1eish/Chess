/***********************************************************************
 * Source File:
 *    TEST QUEEN
 * Author:
 *    Ethan Leishman, Noah McSheehy, Bro. Helfrich
 * Summary:
 *    The unit tests for the queen
 ************************************************************************/

#include "testQueen.h"
#include "pieceQueen.h"     
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
 * 3     p p p           3
 * 2     p(q)p           2
 * 1     p p p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_blocked()
{  // SETUP
   BoardEmpty board;
   Queen queen(7, 7, false /*white*/); // we will reset all this.
   queen.fWhite = true;
   queen.position.colRow = 0x21;
   board.board[2][1] = &queen;
   White white(PAWN);
   board.board[1][1] = &white; // Left
   board.board[2][0] = &white; // Bottom
   board.board[2][2] = &white; // Top
   board.board[3][1] = &white; // Right
   board.board[1][0] = &white; // Bottom left
   board.board[1][2] = &white; // Upper  left
   board.board[3][0] = &white; // Upper  Right
   board.board[3][2] = &white; // Bottom Right
   set <Move> moves;

   // EXERCISE
   queen.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 0);  // No possible moves

   // TEARDOWN
   board.board[2][1] = nullptr; // Queen
   board.board[1][1] = nullptr; // Left   Pawn
   board.board[2][0] = nullptr; // Bottom Pawn
   board.board[2][2] = nullptr; // Top    Pawn
   board.board[3][1] = nullptr; // Right  Pawn
   board.board[1][0] = nullptr; // Bottom left  Pawn
   board.board[1][2] = nullptr; // Upper  left  Pawn
   board.board[3][0] = nullptr; // Upper  Right Pawn
   board.board[3][2] = nullptr; // Bottom Right Pawn
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       .             8
 * 7       .         .   7
 * 6       .       .     6
 * 5       .     .       5
 * 4   .   .   .         4
 * 3     . . .           3
 * 2   . .(q). . . . .   2
 * 1     . . .           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_slideToEnd()
{  // SETUP
   BoardEmpty board;
   Queen queen(7, 7, false /*white*/); // we will reset all this.
   queen.fWhite = true;
   queen.position.colRow = 0x21;
   board.board[2][1] = &queen;
   set <Move> moves;
   
   // straight
   Move c2a2;
   Move c2b2;
   Move c2c1;
   Move c2c3;
   Move c2c4;
   Move c2c5;
   Move c2c6;
   Move c2c7;
   Move c2c8;
   Move c2d2;
   Move c2e2;
   Move c2f2;
   Move c2g2;
   Move c2h2;
   // diagonal
   Move c2a4;
   Move c2b1;
   Move c2b3;
   Move c2d1;
   Move c2d3;
   Move c2e4;
   Move c2f5;
   Move c2g6;
   Move c2h7;

   // straight
   c2a2.source.colRow =
      c2b2.source.colRow =
      c2c1.source.colRow =
      c2c3.source.colRow =
      c2c4.source.colRow =
      c2c5.source.colRow =
      c2c6.source.colRow =
      c2c7.source.colRow =
      c2c8.source.colRow =
      c2d2.source.colRow =
      c2e2.source.colRow =
      c2f2.source.colRow =
      c2g2.source.colRow =
      c2h2.source.colRow = 0x21;
   // diagonal
   c2a4.source.colRow =
      c2b1.source.colRow =
      c2b3.source.colRow =
      c2d1.source.colRow =
      c2d3.source.colRow =
      c2e4.source.colRow =
      c2f5.source.colRow =
      c2g6.source.colRow =
      c2h7.source.colRow = 0x21;
   
   // straight
   c2a2.capture =
      c2b2.capture =
      c2c1.capture =
      c2c3.capture =
      c2c4.capture =
      c2c5.capture =
      c2c6.capture =
      c2c7.capture =
      c2c8.capture =
      c2d2.capture =
      c2e2.capture =
      c2f2.capture =
      c2g2.capture =
      c2h2.capture = SPACE;
   // diagonal
   c2a4.capture =
      c2b1.capture =
      c2b3.capture =
      c2d1.capture =
      c2d3.capture =
      c2e4.capture =
      c2f5.capture =
      c2g6.capture =
      c2h7.capture = SPACE;
   
   // straight
   c2a2.dest.colRow = 0x01;
   c2b2.dest.colRow = 0x11;
   c2c1.dest.colRow = 0x20;
   c2c3.dest.colRow = 0x22;
   c2c4.dest.colRow = 0x23;
   c2c5.dest.colRow = 0x24;
   c2c6.dest.colRow = 0x25;
   c2c7.dest.colRow = 0x26;
   c2c8.dest.colRow = 0x27;
   c2d2.dest.colRow = 0x31;
   c2e2.dest.colRow = 0x41;
   c2f2.dest.colRow = 0x51;
   c2g2.dest.colRow = 0x61;
   c2h2.dest.colRow = 0x71;
   // diagonal
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
   queen.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 23);  // 23 possible moves
   assertUnit(moves.find(c2a2) != moves.end());
   assertUnit(moves.find(c2b2) != moves.end());
   assertUnit(moves.find(c2c1) != moves.end());
   assertUnit(moves.find(c2c3) != moves.end());
   assertUnit(moves.find(c2c4) != moves.end());
   assertUnit(moves.find(c2c5) != moves.end());
   assertUnit(moves.find(c2c6) != moves.end());
   assertUnit(moves.find(c2c7) != moves.end());
   assertUnit(moves.find(c2c8) != moves.end());
   assertUnit(moves.find(c2d2) != moves.end());
   assertUnit(moves.find(c2e2) != moves.end());
   assertUnit(moves.find(c2f2) != moves.end());
   assertUnit(moves.find(c2g2) != moves.end());
   assertUnit(moves.find(c2h2) != moves.end());
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
   board.board[2][1] = nullptr; // Queen
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       p             8
 * 7       .         p   7
 * 6       .       .     6
 * 5       .     .       5
 * 4   p   .   .         4
 * 3     . . .           3
 * 2   p .(q). . . . p   2
 * 1     p p p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_slideToBlock()
{  // SETUP
   BoardEmpty board;
   Queen queen(7, 7, false /*white*/); // we will reset all this.
   queen.fWhite = true;
   queen.position.colRow = 0x21;
   board.board[2][1] = &queen;
   White white(PAWN);
   board.board[0][1] = &white;
   board.board[2][0] = &white;
   board.board[2][7] = &white;
   board.board[7][1] = &white;
   board.board[0][3] = &white; // A4 White Pawn
   board.board[1][0] = &white; // B1 White Pawn
   board.board[3][0] = &white; // D1 White Pawn
   board.board[7][6] = &white; // H7 White Pawn
   set <Move> moves;
   
   // straight
   Move c2b2;
   Move c2c3;
   Move c2c4;
   Move c2c5;
   Move c2c6;
   Move c2c7;
   Move c2d2;
   Move c2e2;
   Move c2f2;
   Move c2g2;
   // diagonal
   Move c2b3;
   Move c2d3;
   Move c2e4;
   Move c2f5;
   Move c2g6;

   // straight
   c2b2.source.colRow =
      c2c3.source.colRow =
      c2c4.source.colRow =
      c2c5.source.colRow =
      c2c6.source.colRow =
      c2c7.source.colRow =
      c2d2.source.colRow =
      c2e2.source.colRow =
      c2f2.source.colRow =
      c2g2.source.colRow = 0x21;
   // diagonal
      c2b3.source.colRow =
      c2d3.source.colRow =
      c2e4.source.colRow =
      c2f5.source.colRow =
      c2g6.source.colRow = 0x21;
   
   // straight
   c2b2.capture =
      c2c3.capture =
      c2c4.capture =
      c2c5.capture =
      c2c6.capture =
      c2c7.capture =
      c2d2.capture =
      c2e2.capture =
      c2f2.capture =
      c2g2.capture = SPACE;
   // diagonal
   c2b3.capture =
      c2d3.capture =
      c2e4.capture =
      c2f5.capture =
      c2g6.capture = SPACE;
   
   // straight
   c2b2.dest.colRow = 0x11;
   c2c3.dest.colRow = 0x22;
   c2c4.dest.colRow = 0x23;
   c2c5.dest.colRow = 0x24;
   c2c6.dest.colRow = 0x25;
   c2c7.dest.colRow = 0x26;
   c2d2.dest.colRow = 0x31;
   c2e2.dest.colRow = 0x41;
   c2f2.dest.colRow = 0x51;
   c2g2.dest.colRow = 0x61;
   // diagonal
   c2b3.dest.colRow = 0x12;
   c2d3.dest.colRow = 0x32;
   c2e4.dest.colRow = 0x43;
   c2f5.dest.colRow = 0x54;
   c2g6.dest.colRow = 0x65;

   // EXERCISE
   queen.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 15);  // 15 possible moves
   assertUnit(moves.find(c2b2) != moves.end());
   assertUnit(moves.find(c2c3) != moves.end());
   assertUnit(moves.find(c2c4) != moves.end());
   assertUnit(moves.find(c2c5) != moves.end());
   assertUnit(moves.find(c2c6) != moves.end());
   assertUnit(moves.find(c2c7) != moves.end());
   assertUnit(moves.find(c2d2) != moves.end());
   assertUnit(moves.find(c2e2) != moves.end());
   assertUnit(moves.find(c2f2) != moves.end());
   assertUnit(moves.find(c2g2) != moves.end());
   assertUnit(moves.find(c2b3) != moves.end());
   assertUnit(moves.find(c2d3) != moves.end());
   assertUnit(moves.find(c2e4) != moves.end());
   assertUnit(moves.find(c2f5) != moves.end());
   assertUnit(moves.find(c2g6) != moves.end());

   
   // TEARDOWN
   board.board[2][1] = nullptr; // Queen
   board.board[0][1] = nullptr; // White Pawn
   board.board[2][0] = nullptr; // White Pawn
   board.board[2][7] = nullptr; // White Pawn
   board.board[7][1] = nullptr; // White Pawn
   board.board[0][3] = nullptr; // White Pawn   A4
   board.board[1][0] = nullptr; // White Pawn   B1
   board.board[3][0] = nullptr; // White Pawn   D1
   board.board[7][6] = nullptr; // White Pawn   H7
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       P             8
 * 7       .         P   7
 * 6       .       .     6
 * 5       .     .       5
 * 4   P   .   .         4
 * 3     . . .           3
 * 2   P .(q). . . . P   2
 * 1     P P P           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_slideToCapture()
{  // SETUP
   BoardEmpty board;
   Queen queen(7, 7, false /*white*/); // we will reset all this.
   queen.fWhite = true;
   queen.position.colRow = 0x21;
   board.board[2][1] = &queen;
   Black black(PAWN);
   board.board[0][1] = &black;
   board.board[2][0] = &black;
   board.board[2][7] = &black;
   board.board[7][1] = &black;
   board.board[0][3] = &black; // A4 White Pawn
   board.board[1][0] = &black; // B1 White Pawn
   board.board[3][0] = &black; // D1 White Pawn
   board.board[7][6] = &black; // H7 White Pawn
   set <Move> moves;
   
   // straight
   Move c2a2;
   Move c2b2;
   Move c2c1;
   Move c2c3;
   Move c2c4;
   Move c2c5;
   Move c2c6;
   Move c2c7;
   Move c2c8;
   Move c2d2;
   Move c2e2;
   Move c2f2;
   Move c2g2;
   Move c2h2;
   // diagonal
   Move c2a4;
   Move c2b1;
   Move c2b3;
   Move c2d1;
   Move c2d3;
   Move c2e4;
   Move c2f5;
   Move c2g6;
   Move c2h7;

   // straight
   c2a2.source.colRow =
      c2b2.source.colRow =
      c2c1.source.colRow =
      c2c3.source.colRow =
      c2c4.source.colRow =
      c2c5.source.colRow =
      c2c6.source.colRow =
      c2c7.source.colRow =
      c2c8.source.colRow =
      c2d2.source.colRow =
      c2e2.source.colRow =
      c2f2.source.colRow =
      c2g2.source.colRow =
      c2h2.source.colRow = 0x21;
   // diagonal
   c2a4.source.colRow =
      c2b1.source.colRow =
      c2b3.source.colRow =
      c2d1.source.colRow =
      c2d3.source.colRow =
      c2e4.source.colRow =
      c2f5.source.colRow =
      c2g6.source.colRow =
      c2h7.source.colRow = 0x21;
   
   // straight
   c2a2.capture =
      c2b2.capture =
      c2c1.capture =
      c2c3.capture =
      c2c4.capture =
      c2c5.capture =
      c2c6.capture =
      c2c7.capture =
      c2c8.capture =
      c2d2.capture =
      c2e2.capture =
      c2f2.capture =
      c2g2.capture =
      c2h2.capture = SPACE;
   // diagonal
   c2a4.capture =
      c2b1.capture =
      c2b3.capture =
      c2d1.capture =
      c2d3.capture =
      c2e4.capture =
      c2f5.capture =
      c2g6.capture =
      c2h7.capture = SPACE;
   
   // straight
   c2a2.dest.colRow = 0x01;
   c2b2.dest.colRow = 0x11;
   c2c1.dest.colRow = 0x20;
   c2c3.dest.colRow = 0x22;
   c2c4.dest.colRow = 0x23;
   c2c5.dest.colRow = 0x24;
   c2c6.dest.colRow = 0x25;
   c2c7.dest.colRow = 0x26;
   c2c8.dest.colRow = 0x27;
   c2d2.dest.colRow = 0x31;
   c2e2.dest.colRow = 0x41;
   c2f2.dest.colRow = 0x51;
   c2g2.dest.colRow = 0x61;
   c2h2.dest.colRow = 0x71;
   // diagonal
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
   queen.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 23);  // 23 possible moves
   assertUnit(moves.find(c2a2) != moves.end());
   assertUnit(moves.find(c2b2) != moves.end());
   assertUnit(moves.find(c2c1) != moves.end());
   assertUnit(moves.find(c2c3) != moves.end());
   assertUnit(moves.find(c2c4) != moves.end());
   assertUnit(moves.find(c2c5) != moves.end());
   assertUnit(moves.find(c2c6) != moves.end());
   assertUnit(moves.find(c2c7) != moves.end());
   assertUnit(moves.find(c2c8) != moves.end());
   assertUnit(moves.find(c2d2) != moves.end());
   assertUnit(moves.find(c2e2) != moves.end());
   assertUnit(moves.find(c2f2) != moves.end());
   assertUnit(moves.find(c2g2) != moves.end());
   assertUnit(moves.find(c2h2) != moves.end());
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
   board.board[2][1] = nullptr; // Queen
   board.board[0][1] = nullptr; // Black Pawn
   board.board[2][0] = nullptr; // Black Pawn
   board.board[2][7] = nullptr; // Black Pawn
   board.board[7][1] = nullptr; // Black Pawn
   board.board[0][3] = nullptr; // Black Pawn   A4
   board.board[1][0] = nullptr; // Black Pawn   B1
   board.board[3][0] = nullptr; // Black Pawn   D1
   board.board[7][6] = nullptr; // Black Pawn   H7
}


/*************************************
 * GET TYPE : queen
 * Input:
 * Output: QUEEN
 **************************************/
void TestQueen::getType()
{
   // SETUP
   const Queen queen(7, 7, false /*white*/);
   PieceType pt = SPACE;

   // EXERCISE
   pt = queen.getType();

   // VERIFY
   assertUnit(pt == QUEEN);
}  // TEARDOWN
