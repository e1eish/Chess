/***********************************************************************
 * Source File:
 *    TEST PAWN
 * Author:
 *    Ethan Leishman, Noah McSheehy, Bro. Helfrich
 * Summary:
 *    The unit tests for the pawn
 ************************************************************************/

#include "testPawn.h"
#include "piecePawn.h"     
#include "board.h"
#include "uiDraw.h"
#include <cassert>      



 /*************************************
  * GET MOVES TEST Simple
  * White pawn in the middle of the board move forward one space: b4 --> b5
  *
  * +---a-b-c-d-e-f-g-h---+
  * |                     |
  * 8                     8
  * 7                     7
  * 6                     6
  * 5     .               5
  * 4    (p)              4
  * 3                     3
  * 2                     2
  * 1                     1
  * |                     |
  * +---a-b-c-d-e-f-g-h---+
  **************************************/
void TestPawn::getMoves_simpleWhite()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, false /*white*/);
   pawn.fWhite = true;
   pawn.nMoves = 1;
   pawn.position.colRow = 0x13;
   board.board[1][3] = &pawn;
   set <Move> moves;
   Move b4b5;
 
   b4b5.source.colRow = 0x13;
   b4b5.capture = SPACE;
   b4b5.dest.colRow = 0x14;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 1);  // one possible move
   assertUnit(moves.find(b4b5) != moves.end());


   // TEARDOWN
   board.board[1][3] = nullptr; // pawn
}

/*************************************
 * GET MOVES TEST Simple
 * Black pawn in the middle of the board move forward one space: b4 --> b3
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4    (P)              4
 * 3     .               3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_simpleBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, false /*white*/);
   pawn.fWhite = false;
   pawn.nMoves = 1;
   pawn.position.colRow = 0x13;
   board.board[1][3] = &pawn;
   set <Move> moves;
   Move b4b3;
 
   b4b3.source.colRow = 0x13;
   b4b3.capture = SPACE;
   b4b3.dest.colRow = 0x12;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 1);  // one possible move
   assertUnit(moves.find(b4b3) != moves.end());


   // TEARDOWN
   board.board[1][3] = nullptr; // pawn
}


/*************************************
 * GET MOVES TEST InitialAdvance
 * White pawn initial advance: b2 --> b4 as well as b2 --> b3
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4     .               4
 * 3     .               3
 * 2    (p)              2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_initialAdvanceWhite()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, false /*white*/);
   pawn.fWhite = true;
   pawn.nMoves = 0;
   pawn.position.colRow = 0x11;
   board.board[1][1] = &pawn;
   set <Move> moves;
   Move b2b3;
   Move b2b4;
 
   b2b3.source.colRow = b2b4.source.colRow = 0x11;
   b2b3.capture       = b2b4.capture       = SPACE;
   b2b3.dest.colRow = 0x12;
   b2b4.dest.colRow = 0x13;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);  // two possible moves
   assertUnit(moves.find(b2b3) != moves.end());
   assertUnit(moves.find(b2b4) != moves.end());


   // TEARDOWN
   board.board[1][1] = nullptr; // pawn
}

/*************************************
 * GET MOVES TEST InitialAdvance
 * Black pawn initial advance: c7 --> c5 as well as c7 --> c5
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7      (P)            7
 * 6       .             6
 * 5       .             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_initialAdvanceBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, false /*white*/);
   pawn.fWhite = false;
   pawn.nMoves = 0;
   pawn.position.colRow = 0x26;
   board.board[2][6] = &pawn;
   set <Move> moves;
   Move c7c6;
   Move c7c5;
 
   c7c6.source.colRow = c7c5.source.colRow = 0x26;
   c7c6.capture       = c7c5.capture       = SPACE;
   c7c6.dest.colRow = 0x25;
   c7c5.dest.colRow = 0x24;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);  // two possible moves
   assertUnit(moves.find(c7c6) != moves.end());
   assertUnit(moves.find(c7c5) != moves.end());


   // TEARDOWN
   board.board[2][6] = nullptr; // pawn
}


/*************************************
 * GET MOVES TEST Capture
 * Double capture: move white pawn b6 and capture two: a7 and c7. b7 is blocked
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7   P P P             7
 * 6    (p)              6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_captureWhite()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, false /*white*/);
   pawn.fWhite = true;
   pawn.nMoves = 0;
   pawn.position.colRow = 0x15;
   board.board[1][5] = &pawn;
   Black black(PAWN);
   board.board[0][6] = &black;
   board.board[1][6] = &black;
   board.board[2][6] = &black;
   set <Move> moves;
   Move b6a7p;
   Move b6c7p;
 
   b6a7p.source.colRow = b6c7p.source.colRow = 0x15;
   b6a7p.capture       = b6c7p.capture       = PAWN;
   b6a7p.dest.colRow = 0x06;
   b6c7p.dest.colRow = 0x26;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);  // two possible moves
   assertUnit(moves.find(b6a7p) != moves.end());
   assertUnit(moves.find(b6c7p) != moves.end());


   // TEARDOWN
   board.board[1][5] = nullptr; // white pawn
   board.board[0][6] = nullptr; // black pawn
   board.board[1][6] = nullptr; // black pawn
   board.board[2][6] = nullptr; // black pawn
}


/*************************************
 * GET MOVES TEST Capture
 * Double capture: move black pawn b6 and capture two: a5 and c5. b5 is blocked
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6    (P)              6
 * 5   p p p             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_captureBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, false /*white*/);
   pawn.fWhite = false;
   pawn.nMoves = 0;
   pawn.position.colRow = 0x15;
   board.board[1][5] = &pawn;
   White white(PAWN);
   board.board[0][4] = &white;
   board.board[1][4] = &white;
   board.board[2][4] = &white;
   set <Move> moves;
   Move b6a5p;
   Move b6c5p;
 
   b6a5p.source.colRow = b6c5p.source.colRow = 0x15;
   b6a5p.capture       = b6c5p.capture       = PAWN;
   b6a5p.dest.colRow = 0x04;
   b6c5p.dest.colRow = 0x24;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);  // two possible moves
   assertUnit(moves.find(b6a5p) != moves.end());
   assertUnit(moves.find(b6c5p) != moves.end());


   // TEARDOWN
   board.board[1][5] = nullptr; // black pawn
   board.board[0][4] = nullptr; // white pawn
   board.board[1][4] = nullptr; // white pawn
   board.board[2][4] = nullptr; // white pawn
}

/*************************************
 * GET MOVES TEST Enpassant
 * Enpassant: white b5 can capture a5 and c5. Note that b6 is blocked
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6   . P .             6
 * 5   P(p)P             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_enpassantWhite()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, false /*white*/);
   pawn.fWhite = true;
   pawn.nMoves = 0;
   pawn.position.colRow = 0x14;
   board.board[1][4] = &pawn;
   board.moveNumber = 2;
   Black black(PAWN);
   
   Pawn blackPawn(7, 7, true /*black*/);
   blackPawn.fWhite = false;
   blackPawn.lastMove = 1;
   blackPawn.position.colRow = 0x77;
   
   board.board[0][4] = &blackPawn;
   board.board[1][5] = &black;
   board.board[2][4] = &blackPawn;
   set <Move> moves;
   Move b6a7E;
   Move b6c7E;
 
   b6a7E.source.colRow = b6c7E.source.colRow = 0x14;
   b6a7E.moveType      = b6c7E.moveType      = Move::ENPASSANT;
   b6a7E.dest.colRow = 0x05;
   b6c7E.dest.colRow = 0x25;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);  // two possible moves
   assertUnit(moves.find(b6a7E) != moves.end());
   assertUnit(moves.find(b6c7E) != moves.end());


   // TEARDOWN
   board.board[1][4] = nullptr; // white pawn
   board.board[0][4] = nullptr; // black pawn
   board.board[1][5] = nullptr; // black pawn
   board.board[2][4] = nullptr; // black pawn
}


/*************************************
 * GET MOVES TEST Enpassant
 * Enpassant black f4 can capture e4 and g4. Note that f3 is blocked
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4           p(P)p     4
 * 3           . p .     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_enpassantBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, false /*white*/);
   pawn.fWhite = false;
   pawn.nMoves = 0;
   pawn.position.colRow = 0x53;
   board.board[5][3] = &pawn;
   board.moveNumber = 2;
   White white(PAWN);
   
   Pawn whitePawn(7, 7, false /*white*/);
   whitePawn.fWhite = true;
   whitePawn.lastMove = 1;
   whitePawn.position.colRow = 0x77;
   
   board.board[4][3] = &whitePawn;
   board.board[5][2] = &white;
   board.board[6][3] = &whitePawn;
   set <Move> moves;
   Move f4e3E;
   Move f4g3E;
 
   f4e3E.source.colRow = f4g3E.source.colRow = 0x53;
   f4e3E.moveType      = f4g3E.moveType      = Move::ENPASSANT;
   f4e3E.dest.colRow = 0x42;
   f4g3E.dest.colRow = 0x62;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);  // two possible moves
   assertUnit(moves.find(f4e3E) != moves.end());
   assertUnit(moves.find(f4g3E) != moves.end());


   // TEARDOWN
   board.board[5][3] = nullptr; // black pawn
   board.board[4][3] = nullptr; // white pawn
   board.board[5][2] = nullptr; // white pawn
   board.board[6][3] = nullptr; // white pawn
}

/*************************************
 * GET MOVES TEST Promotion
 * Promotion: white pawn b7 can capture two pawns: a8 and c8. 
 *            It can also move into b8. All three are promoted to queen
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8   P . P             8
 * 7    (p)              7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_promotionWhite()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, false /*white*/);
   pawn.fWhite = true;
   pawn.nMoves = 0;
   pawn.position.colRow = 0x16;
   board.board[1][6] = &pawn;
   Black black(PAWN);
   board.board[0][7] = &black;
   board.board[2][7] = &black;
   set <Move> moves;
   Move b7a8p;
   Move b7b8;
   Move b7c8p;
 
   b7a8p.source.colRow = b7b8.source.colRow = b7c8p.source.colRow = 0x16;
   b7a8p.promote = b7b8.promote = b7c8p.promote = QUEEN;
   b7a8p.capture = b7c8p.capture = PAWN;
   b7b8.capture  = SPACE;
   b7a8p.dest.colRow = 0x07;
   b7b8.dest.colRow  = 0x17;
   b7c8p.dest.colRow = 0x27;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 3);  // three possible moves
   assertUnit(moves.find(b7a8p) != moves.end());
   assertUnit(moves.find(b7b8)  != moves.end());
   assertUnit(moves.find(b7c8p) != moves.end());


   // TEARDOWN
   board.board[1][6] = nullptr; // white pawn
   board.board[0][7] = nullptr; // black pawn
   board.board[2][7] = nullptr; // black pawn
}


/*************************************
 * GET MOVES TEST Promotion
 * Promotion: black pawn e2 can capture two rooks: d1 and f1.
 *            It can also move into e1. All three are promoted to queen
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2          (P)        2
 * 1         r . r       1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_promotionBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(7, 7, false /*white*/);
   pawn.fWhite = false;
   pawn.nMoves = 0;
   pawn.position.colRow = 0x51;
   board.board[5][1] = &pawn;
   White white(ROOK);
   board.board[4][0] = &white;
   board.board[6][0] = &white;
   set <Move> moves;
   Move e2d1r;
   Move e2e1;
   Move e2f1r;
 
   e2d1r.source.colRow = e2e1.source.colRow = e2f1r.source.colRow = 0x51;
   e2d1r.promote = e2e1.promote = e2f1r.promote = QUEEN;
   e2d1r.capture = e2f1r.capture = ROOK;
   e2e1.capture  = SPACE;
   e2d1r.dest.colRow = 0x40;
   e2e1.dest.colRow  = 0x50;
   e2f1r.dest.colRow = 0x60;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 3);  // three possible moves
   assertUnit(moves.find(e2d1r) != moves.end());
   assertUnit(moves.find(e2e1)  != moves.end());
   assertUnit(moves.find(e2f1r) != moves.end());


   // TEARDOWN
   board.board[5][1] = nullptr; // black pawn
   board.board[4][0] = nullptr; // white rook
   board.board[6][0] = nullptr; // white rook
}


/*************************************
 * GET TYPE : pawn
 * Input:
 * Output: PAWN
 **************************************/
void TestPawn::getType()
{
   // SETUP
   const Pawn pawn(7, 7, false /*white*/);
   PieceType pt = SPACE;

   // EXERCISE
   pt = pawn.getType();

   // VERIFY
   assertUnit(pt == PAWN);
}  // TEARDOWN

