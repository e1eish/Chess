/***********************************************************************
 * Source File:
 *    TEST KING
 * Author:
 *    Ethan Leishman, Noah McSheehy, Bro. Helfrich
 * Summary:
 *    The unit tests for the King
 ************************************************************************/

#include "testKing.h"
#include "pieceRook.h"
#include "pieceKing.h"     
#include "board.h"
#include "uiDraw.h"
#include <cassert>      


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       p p p         6
 * 5       p(k)p         5
 * 4       p p p         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 * 
 *    *Pieces*
 * D5 0x34 White King (Selected)
 * C4 0x23 White Pawn 
 * C5 0x24 White Pawn 
 * C6 0x25 White Pawn 
 * D4 0x33 White Pawn 
 * D6 0x35 White Pawn 
 * E4 0x43 White Pawn 
 * E5 0x44 White Pawn 
 * E6 0x45 White Pawn 
 * 
 *    *Moves*
 * None
 **************************************/
void TestKing::getMoves_blocked()
{  // SETUP
   BoardEmpty board;
   King king(7, 7, false /*white*/);
   king.fWhite = true;
   king.position.colRow = 0x34;
   White white(PAWN);

   // Place the board
   board.board[3][4] = &king;
   board.board[2][3] = &white;
   board.board[2][4] = &white;
   board.board[2][5] = &white;
   board.board[3][3] = &white;
   board.board[3][5] = &white;
   board.board[4][3] = &white;
   board.board[4][4] = &white;
   board.board[4][5] = &white;

   set <Move> moves;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 0);

   // TEARDOWN
   board.board[3][4] = nullptr;
   board.board[2][3] = nullptr;
   board.board[2][4] = nullptr;
   board.board[2][5] = nullptr;
   board.board[3][3] = nullptr;
   board.board[3][5] = nullptr;
   board.board[4][3] = nullptr;
   board.board[4][4] = nullptr;
   board.board[4][5] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       P P P         6
 * 5       P(k)P         5
 * 4       P P P         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 * 
 *    *Pieces*
 * D5 0x34 White King (Selected)
 * C4 0x23 Black Pawn 
 * C5 0x24 Black Pawn 
 * C6 0x25 Black Pawn 
 * D4 0x33 Black Pawn 
 * D6 0x35 Black Pawn 
 * E4 0x43 Black Pawn 
 * E5 0x44 Black Pawn 
 * E6 0x45 Black Pawn 
 * 
 *    *Moves 8*
 * C4 0x23 Black Pawn
 * C5 0x24 Black Pawn
 * C6 0x25 Black Pawn
 * D4 0x33 Black Pawn
 * D6 0x35 Black Pawn
 * E4 0x43 Black Pawn
 * E5 0x44 Black Pawn
 * E6 0x45 Black Pawn
 **************************************/
void TestKing::getMoves_capture()
{  // SETUP
   BoardEmpty board;
   King king(7, 7, false /*white*/);
   king.fWhite = true;
   king.position.colRow = 0x34;
   Black black(PAWN);

   // Place the board
   board.board[3][4] = &king;
   board.board[2][3] = &black;
   board.board[2][4] = &black;
   board.board[2][5] = &black;
   board.board[3][3] = &black;
   board.board[3][5] = &black;
   board.board[4][3] = &black;
   board.board[4][4] = &black;
   board.board[4][5] = &black;

   // Create a set of moves
   set <Move> moves;
   Move d5c4;
   Move d5c5;
   Move d5c6;
   Move d5d4;
   Move d5d6;
   Move d5e4;
   Move d5e5;
   Move d5e6;

   // Every Moves Source
   d5c4.source.colRow =
      d5c5.source.colRow =
      d5c6.source.colRow =
      d5d4.source.colRow =
      d5d6.source.colRow =
      d5e4.source.colRow =
      d5e5.source.colRow =
      d5e6.source.colRow = 0x34;

   // What is being captured
   d5c4.capture =
      d5c5.capture =
      d5c6.capture =
      d5d4.capture =
      d5d6.capture =
      d5e4.capture =
      d5e5.capture =
      d5e6.capture = PAWN;

   // Every Moves Destination
   d5c4.dest.colRow = 0x23;
   d5c5.dest.colRow = 0x24;
   d5c6.dest.colRow = 0x25;
   d5d4.dest.colRow = 0x33;
   d5d6.dest.colRow = 0x35;
   d5e4.dest.colRow = 0x43;
   d5e5.dest.colRow = 0x44;
   d5e6.dest.colRow = 0x45;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 8);
   assertUnit(moves.find(d5c4) != moves.end());
   assertUnit(moves.find(d5c5) != moves.end());
   assertUnit(moves.find(d5c6) != moves.end());
   assertUnit(moves.find(d5d4) != moves.end());
   assertUnit(moves.find(d5d6) != moves.end());
   assertUnit(moves.find(d5e4) != moves.end());
   assertUnit(moves.find(d5e5) != moves.end());
   assertUnit(moves.find(d5e6) != moves.end());

   // TEARDOWN
   board.board[3][4] = nullptr;
   board.board[2][3] = nullptr;
   board.board[2][4] = nullptr;
   board.board[2][5] = nullptr;
   board.board[3][3] = nullptr;
   board.board[3][5] = nullptr;
   board.board[4][3] = nullptr;
   board.board[4][4] = nullptr;
   board.board[4][5] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       . . .         6
 * 5       .(k).         5
 * 4       . . .         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 * 
 *    *Pieces*
 * D5 0x34 White King (Selected)
 * 
 *    *Moves 8*
 * C4 0x23 Space
 * C5 0x24 Space
 * C6 0x25 Space
 * D4 0x33 Space
 * D6 0x35 Space
 * E4 0x43 Space
 * E5 0x44 Space
 * E6 0x45 Space
 **************************************/
void TestKing::getMoves_free()
{  // SETUP
   BoardEmpty board;
   King king(7, 7, false /*white*/);
   king.fWhite = true;
   king.position.colRow = 0x34;

   // Place the board
   board.board[3][4] = &king;

   // Create a set of moves
   set <Move> moves;
   Move d5c4;
   Move d5c5;
   Move d5c6;
   Move d5d4;
   Move d5d6;
   Move d5e4;
   Move d5e5;
   Move d5e6;

   // Every Moves Source
   d5c4.source.colRow =
      d5c5.source.colRow =
      d5c6.source.colRow =
      d5d4.source.colRow =
      d5d6.source.colRow =
      d5e4.source.colRow =
      d5e5.source.colRow =
      d5e6.source.colRow = 0x34;

   // What is being captured
   d5c4.capture =
      d5c5.capture =
      d5c6.capture =
      d5d4.capture =
      d5d6.capture =
      d5e4.capture =
      d5e5.capture =
      d5e6.capture = SPACE;

   // Every Moves Destination
   d5c4.dest.colRow = 0x23;
   d5c5.dest.colRow = 0x24;
   d5c6.dest.colRow = 0x25;
   d5d4.dest.colRow = 0x33;
   d5d6.dest.colRow = 0x35;
   d5e4.dest.colRow = 0x43;
   d5e5.dest.colRow = 0x44;
   d5e6.dest.colRow = 0x45;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 8);
   assertUnit(moves.find(d5c4) != moves.end());
   assertUnit(moves.find(d5c5) != moves.end());
   assertUnit(moves.find(d5c6) != moves.end());
   assertUnit(moves.find(d5d4) != moves.end());
   assertUnit(moves.find(d5d6) != moves.end());
   assertUnit(moves.find(d5e4) != moves.end());
   assertUnit(moves.find(d5e5) != moves.end());
   assertUnit(moves.find(d5e6) != moves.end());

   // TEARDOWN
   board.board[3][4] = nullptr;
}



/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2   . .               2
 * 1  (k).               1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 *
 *    *Pieces*
 * A1 0x00 White King (Selected)
 * 
 *    *Moves 3*
 * A2 0x01 Space
 * B1 0x10 Space
 * B2 0x11 Space
 **************************************/
void TestKing::getMoves_end()
{  // SETUP
   BoardEmpty board;
   King king(7, 7, false /*white*/);
   king.fWhite = true;
   king.position.colRow = 0x00;

   // Place the board
   board.board[0][0] = &king;

   // Create a set of moves
   set <Move> moves;
   Move a1a2;
   Move a1b1;
   Move a1b2;

   // Every Moves Source
   a1a2.source.colRow =
      a1b1.source.colRow =
      a1b2.source.colRow = 0x00;

   // What is being captured
   a1a2.capture =
      a1b1.capture =
      a1b2.capture = SPACE;

   // Every Moves Destination
   a1a2.dest.colRow = 0x01;
   a1b1.dest.colRow = 0x10;
   a1b2.dest.colRow = 0x11;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 3);
   assertUnit(moves.find(a1a2) != moves.end());
   assertUnit(moves.find(a1b1) != moves.end());
   assertUnit(moves.find(a1b2) != moves.end());


   // TEARDOWN
   board.board[0][0] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r   . .(k). . r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 *
 *    *Pieces*
 * E1 0x40 White King (Selected)
 * A1 0x00 White Rook
 * H1 0x70 White Rook
 * D2 0x31 White Pawn
 * E2 0x41 White Pawn
 * F2 0x51 White Pawn
 *
 *    *Moves 4*
 * C1 0x20 Space
 * D1 0x30 Space
 * F1 0x40 Space
 * G1 0x50 Space
 **************************************/
void TestKing::getMoves_whiteCastle()
{  // SETUP
   BoardEmpty board;
   King king(7, 7, false /*white*/);
   king.fWhite = true;
   king.position.colRow = 0x40;

   Rook rookLeft(7, 7, false /*white*/); 
   rookLeft.fWhite = true;
   rookLeft.position.colRow = 0x00;

   Rook rookRight(7, 7, false /*white*/);
   rookRight.fWhite = true;
   rookRight.position.colRow = 0x70;

   White whitePawn(PAWN);

   // Place the board
   board.board[4][0] = &king;
   board.board[0][0] = &rookLeft;
   board.board[7][0] = &rookRight;
   board.board[3][1] = &whitePawn;
   board.board[4][1] = &whitePawn;
   board.board[5][1] = &whitePawn;

   // Create a set of moves
   set <Move> moves;
   Move e1c1;
   Move e1d1;
   Move e1f1;
   Move e1g1;

   // Every Moves Source
   e1c1.source.colRow =
      e1d1.source.colRow =
      e1f1.source.colRow =
      e1g1.source.colRow = 0x40;

   // What is being captured
   e1c1.capture = 
      e1d1.capture = 
      e1f1.capture = 
      e1g1.capture = SPACE;

   // Every Moves Destination
   e1c1.dest.colRow = 0x20;
   e1d1.dest.colRow = 0x30;
   e1f1.dest.colRow = 0x40;
   e1g1.dest.colRow = 0x50;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 4);
   assertUnit(moves.find(e1c1) != moves.end());
   assertUnit(moves.find(e1d1) != moves.end());
   assertUnit(moves.find(e1f1) != moves.end());
   assertUnit(moves.find(e1g1) != moves.end());

   // TEARDOWN
   board.board[4][0] = nullptr;
   board.board[0][0] = nullptr;
   board.board[7][0] = nullptr;
   board.board[3][1] = nullptr;
   board.board[4][1] = nullptr;
   board.board[5][1] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8   R   . .(K). . R   8
 * 7         P P P       7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 *
 *    *Pieces*
 * E8 0x47 Black King (Selected)
 * A8 0x07 Black Rook
 * H8 0x77 Black Rook
 * D7 0x36 Black Pawn
 * E7 0x46 Black Pawn
 * F7 0x56 Black Pawn
 *
 *    *Moves 4*
 * C8 0x27 Space
 * D8 0x37 Space
 * F8 0x47 Space
 * G8 0x57 Space
 **************************************/
void TestKing::getMoves_blackCastle()
{  // SETUP
   BoardEmpty board;
   King king(7, 7, false /*white*/);
   king.fWhite = false; // Make Black
   king.position.colRow = 0x47;

   Rook rookLeft(7, 7, false /*white*/); 
   rookLeft.fWhite = false;
   rookLeft.position.colRow = 0x07;

   Rook rookRight(7, 7, false /*white*/);
   rookRight.fWhite = false;
   rookRight.position.colRow = 0x77;

   Black blackPawn(PAWN);

   // Place the board
   board.board[4][7] = &king;
   board.board[0][7] = &rookLeft;
   board.board[7][7] = &rookRight;
   board.board[3][6] = &blackPawn;
   board.board[4][6] = &blackPawn;
   board.board[5][6] = &blackPawn;

   // Create a set of moves
   set <Move> moves;
   Move e8c8;
   Move e8d8;
   Move e8f8;
   Move e8g8;

   // Every Moves Source
   e8c8.source.colRow =
      e8d8.source.colRow =
      e8f8.source.colRow =
      e8g8.source.colRow = 0x47;

   // What is being captured
   e8c8.capture =
      e8d8.capture =
      e8f8.capture =
      e8g8.capture = SPACE;

   // Every Moves Destination
   e8c8.dest.colRow = 0x27;
   e8d8.dest.colRow = 0x37;
   e8f8.dest.colRow = 0x47;
   e8g8.dest.colRow = 0x57;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 4);
   assertUnit(moves.find(e8c8) != moves.end());
   assertUnit(moves.find(e8d8) != moves.end());
   assertUnit(moves.find(e8f8) != moves.end());
   assertUnit(moves.find(e8g8) != moves.end());

   // TEARDOWN
   board.board[4][7] = nullptr;
   board.board[0][7] = nullptr;
   board.board[7][7] = nullptr;
   board.board[3][6] = nullptr;
   board.board[4][6] = nullptr;
   board.board[5][6] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r     .(k).   r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 *
 *    *Pieces*
 * E1 0x40 White King (Selected)
 * A1 0x00 White Rook
 * H1 0x70 White Rook
 * D2 0x31 White Pawn
 * E2 0x41 White Pawn
 * F2 0x51 White Pawn
 *
 *    *Moves 4*
 * D1 0x30 Space
 * F1 0x40 Space
 **************************************/
void TestKing::getMoves_whiteCastleKingMoved()
{  // SETUP
   BoardEmpty board;
   King kingHasMoved(7, 7, false /*white*/);
   kingHasMoved.fWhite = true;
   kingHasMoved.position.colRow = 0x40;
   kingHasMoved.nMoves = 1;                 

   Rook rookLeft(7, 7, false /*white*/);    
   rookLeft.fWhite = true;
   rookLeft.position.colRow = 0x00;

   Rook rookRight(7, 7, false /*white*/);
   rookRight.fWhite = true;
   rookRight.position.colRow = 0x70;

   White whitePawn(PAWN);

   // Place the board
   board.board[4][0] = &kingHasMoved;
   board.board[0][0] = &rookLeft;
   board.board[7][0] = &rookRight;
   board.board[3][1] = &whitePawn;
   board.board[4][1] = &whitePawn;
   board.board[5][1] = &whitePawn;

   // Create a set of moves
   set <Move> moves;
   Move e1d1;
   Move e1f1;

   // Every Moves Source
   e1d1.source.colRow =
      e1f1.source.colRow = 0x40;

   // What is being captured
   e1d1.capture =
      e1f1.capture = SPACE;

   // Every Moves Destination
   e1d1.dest.colRow = 0x30;
   e1f1.dest.colRow = 0x40;

   // EXERCISE
   kingHasMoved.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(e1d1) != moves.end());
   assertUnit(moves.find(e1f1) != moves.end());

   // TEARDOWN
   board.board[4][0] = nullptr;
   board.board[0][0] = nullptr;
   board.board[7][0] = nullptr;
   board.board[3][1] = nullptr;
   board.board[4][1] = nullptr;
   board.board[5][1] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r     .(k).   r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 * 
 *    *Pieces*
 * E1 0x40 White King (Selected)
 * A1 0x00 White Rook
 * H1 0x70 White Rook
 * D2 0x31 White Pawn
 * E2 0x41 White Pawn
 * F2 0x51 White Pawn
 *
 *    *Moves 4*
 * D1 0x30 Space
 * F1 0x40 Space
 **************************************/
void TestKing::getMoves_whiteCastleRookMoved()
{  // SETUP
   BoardEmpty board;
   King king(7, 7, false /*white*/);             
   king.fWhite = true;
   king.position.colRow = 0x40;

   Rook rookHasMovedLeft(7, 7, false /*white*/); 
   rookHasMovedLeft.fWhite = true;
   rookHasMovedLeft.position.colRow = 0x00;

   Rook rookHasMovedRight(7, 7, false /*white*/);
   rookHasMovedRight.fWhite = true;
   rookHasMovedRight.position.colRow = 0x70;

   White whitePawn(PAWN);

   rookHasMovedLeft.nMoves = 1;
   rookHasMovedRight.nMoves = 1;

   // Place the board
   board.board[4][0] = &king;
   board.board[0][0] = &rookHasMovedLeft;
   board.board[7][0] = &rookHasMovedRight;
   board.board[3][1] = &whitePawn;
   board.board[4][1] = &whitePawn;
   board.board[5][1] = &whitePawn;

   // Create a set of moves
   set <Move> moves;
   Move e1d1;
   Move e1f1;

   // Every Moves Source
   e1d1.source.colRow =
      e1f1.source.colRow = 0x40;

   // What is being captured
   e1d1.capture =
      e1f1.capture = SPACE;

   // Every Moves Destination
   e1d1.dest.colRow = 0x30;
   e1f1.dest.colRow = 0x40;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(e1d1) != moves.end());
   assertUnit(moves.find(e1f1) != moves.end());

   // TEARDOWN
   board.board[4][0] = nullptr;
   board.board[0][0] = nullptr;
   board.board[7][0] = nullptr;
   board.board[3][1] = nullptr;
   board.board[4][1] = nullptr;
   board.board[5][1] = nullptr;
}

/*************************************
 * GET TYPE : king
 * Input:
 * Output: KING
 **************************************/
void TestKing::getType()
{
   // SETUP
   const King king(7, 7, false /*white*/);
   PieceType pt = SPACE;

   // EXERCISE
   pt = king.getType();

   // VERIFY
   assertUnit(pt == KING);
}  // TEARDOWN


