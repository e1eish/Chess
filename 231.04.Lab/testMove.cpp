/***********************************************************************
 * Header File:
 *    TEST MOVE 
 * Author:
 *    Ethan Leishman, Noah McSheehy, Bro. Helfrich
 * Summary:
 *    test the Move class
 ************************************************************************/


#include "testMove.h"
#include "move.h"
#include <cassert>

 /*************************************
  * Constructor : default
  * Input: 
  * Output: source=INVALID
  *         dest  =INVALID
  **************************************/
void TestMove::constructor_default() 
{  // setup
   // exercise
   Move m;
   // verify
   assertUnit(m.source.isInvalid());
   assertUnit(m.dest.isInvalid());
}  // teardown

 /*************************************
  * CONSTRUCTOR : standard string move
  * Input:  e5e6
  * Output: source=4,4
  *         dest  =4,5
  *         type  =MOVE
  **************************************/
void TestMove::constructString_simple()
{  // setup
   // exercise
   Move m("e5e6");
   
   //verify
   assertUnit(m.text == "e5e6");
   assertEquals(m.source.getCol(), 4);
   assertEquals(m.source.getRow(), 4);
   assertEquals(m.dest.getCol(),   4);
   assertEquals(m.dest.getRow(),   5);
   assertEquals(m.moveType, Move::MOVE);
}  // teardown

 /*************************************
  * READ simple move 
  * Input:  e5e6
  * Output: source=4,4
  *         dest  =4,5
  *         type  =MOVE
  **************************************/
void TestMove::read_simple()
{  // setup
   Move m;
   // exercise
   m.read("e5e6");
   
   //verify
   assertUnit(m.text == "e5e6");
   assertEquals(m.source.getCol(), 4);
   assertEquals(m.source.getRow(), 4);
   assertEquals(m.dest.getCol(),   4);
   assertEquals(m.dest.getRow(),   5);
   assertEquals(m.moveType, Move::MOVE);
}  // teardown

 /*************************************
  * READ capture move 
  * Input:  e5d6r
  * Output: source=4,4
  *         dest  =3,5
  *         type  =MOVE
  *         capture=ROOK
  **************************************/
void TestMove::read_capture()
{  // setup
   Move m;
   // exercise
   m.read("e5d6r");
   
   //verify
   assertUnit(m.text == "e5d6r");
   assertEquals(m.source.getCol(), 4);
   assertEquals(m.source.getRow(), 4);
   assertEquals(m.dest.getCol(),   3);
   assertEquals(m.dest.getRow(),   5);
   assertEquals(m.moveType, Move::MOVE);
   assertEquals(m.capture, PieceType::ROOK);
}  // teardown

 /*************************************
  * READ enpassant move 
  * Input:  e5f6E
  * Output: source=4,4
  *         dest  =5,5
  *         type  =ENPASSANT
  **************************************/
void TestMove::read_enpassant()
{  // setup
   Move m;
   // exercise
   m.read("e5f6E");
   
   //verify
   assertUnit(m.text == "e5f6E");
   assertEquals(m.source.getCol(), 4);
   assertEquals(m.source.getRow(), 4);
   assertEquals(m.dest.getCol(),   5);
   assertEquals(m.dest.getRow(),   5);
   assertEquals(m.moveType, Move::ENPASSANT);
}  // teardown

 /*************************************
  * READ king side castle
  * Input:  e1g1c
  * Output: source=4,0
  *         dest  =6,0
  *         type  =CASTLE_KING
  **************************************/
void TestMove::read_castleKing()
{  // setup
   Move m;
   // exercise
   m.read("e1g1c");
   
   //verify
   assertUnit(m.text == "e1g1c");
   assertEquals(m.source.getCol(), 4);
   assertEquals(m.source.getRow(), 0);
   assertEquals(m.dest.getCol(),   6);
   assertEquals(m.dest.getRow(),   0);
   assertEquals(m.moveType, Move::CASTLE_KING);
}  // teardown

 /*************************************
  * READ queen side castle
  * Input:  e1c1C
  * Output: source=4,0
  *         dest  =2,0
  *         type  =CASTLE_QUEEN
  **************************************/
void TestMove::read_castleQueen()
{  // setup
   Move m;
   // exercise
   m.read("e1c1C");
   
   //verify
   assertUnit(m.text == "e1c1C");
   assertEquals(m.source.getCol(), 4);
   assertEquals(m.source.getRow(), 0);
   assertEquals(m.dest.getCol(),   2);
   assertEquals(m.dest.getRow(),   0);
   assertEquals(m.moveType, Move::CASTLE_QUEEN);
}  // teardown

 /*************************************
  * ASSIGN simple move
  * Input:  e5e6
  * Output: source=4,4
  *         dest  =4,5
  *         type  =MOVE
  **************************************/
void TestMove::assign_simple()
{  // setup
   Move m;
   // exercise
   m = "e5e6";
   
   //verify
   assertUnit(m.text == "e5e6");
   assertEquals(m.source.getCol(), 4);
   assertEquals(m.source.getRow(), 4);
   assertEquals(m.dest.getCol(),   4);
   assertEquals(m.dest.getRow(),   5);
   assertEquals(m.moveType, Move::MOVE);
}  // teardown

 /*************************************
  * ASSIGN capture move
  * Input:  e5d6r
  * Output: source=4,4
  *         dest  =3,5
  *         type  =MOVE
  *         capture=ROOK
  **************************************/
void TestMove::assign_capture()
{  // setup
   Move m;
   // exercise
   m = "e5d6r";
   
   //verify
   assertUnit(m.text == "e5d6r");
   assertEquals(m.source.getCol(), 4);
   assertEquals(m.source.getRow(), 4);
   assertEquals(m.dest.getCol(),   3);
   assertEquals(m.dest.getRow(),   5);
   assertEquals(m.moveType, Move::MOVE);
   assertEquals(m.capture, PieceType::ROOK);
}  // teardown

 /*************************************
  * ASSIGN enpassant move
  * Input:  e5f6E
  * Output: source=4,4
  *         dest  =5,5
  *         type  =ENPASSANT
  **************************************/
void TestMove::assign_enpassant()
{  // setup
   Move m;
   // exercise
   m = "e5f6E";
   
   //verify
   assertUnit(m.text == "e5f6E");
   assertEquals(m.source.getCol(), 4);
   assertEquals(m.source.getRow(), 4);
   assertEquals(m.dest.getCol(),   5);
   assertEquals(m.dest.getRow(),   5);
   assertEquals(m.moveType, Move::ENPASSANT);
}  // teardown

 /*************************************
  * ASSIGN king side castle
  * Input:  e1g1c
  * Output: source=4,0
  *         dest  =6,0
  *         type  =CASTLE_KING
  **************************************/
void TestMove::assign_castleKing()
{  // setup
   Move m;
   // exercise
   m = "e1g1c";
   
   //verify
   assertUnit(m.text == "e1g1c");
   assertEquals(m.source.getCol(), 4);
   assertEquals(m.source.getRow(), 0);
   assertEquals(m.dest.getCol(),   6);
   assertEquals(m.dest.getRow(),   0);
   assertEquals(m.moveType, Move::CASTLE_KING);
}  // teardown

 /*************************************
  * ASSIGN queen side castle
  * Input:  e1c1C
  * Output: source=4,0
  *         dest  =2,0
  *         type  =CASTLE_QUEEN
  **************************************/
void TestMove::assign_castleQueen()
{  // setup
   Move m;
   // exercise
   m = "e1c1C";
   
   //verify
   assertUnit(m.text == "e1c1C");
   assertEquals(m.source.getCol(), 4);
   assertEquals(m.source.getRow(), 0);
   assertEquals(m.dest.getCol(),   2);
   assertEquals(m.dest.getRow(),   0);
   assertEquals(m.moveType, Move::CASTLE_QUEEN);
}  // teardown

 /*************************************
  * GET TEXT simple move
  * Input : source=4,4
  *         dest  =4,5
  *         type  =MOVE
  * Output:  e5e6
  **************************************/
void TestMove::getText_simple()
{  // setup
   Move m;
   Position s(4,4);
   Position d(4,5);
   m.source   = s;
   m.dest     = d;
   m.moveType = Move::MOVE;
   string text;
   
   // exercise
   text = m.getText();
   
   // verify
   assertEquals(m.source.getCol(), 4);
   assertEquals(m.source.getRow(), 4);
   assertEquals(m.dest.getCol(), 4);
   assertEquals(m.dest.getRow(), 5);
   assertEquals(m.moveType, Move::MOVE);
   assertUnit(text == "e5e6");
}  // teardown

 /*************************************
  * GET TEXT capture
  * Input : source=4,4
  *         dest  =4,5
  *         type  =MOVE
  *         capture=ROOK
  * Output:  e5e6r
  **************************************/
void TestMove::getText_capture()
{  // setup
   Move m;
   Position s(4,4);
   Position d(4,5);
   m.source   = s;
   m.dest     = d;
   m.moveType = Move::MOVE;
   m.capture = PieceType::ROOK;
   string text = "";
   
   // exercise
   text = m.getText();
   
   // verify
   assertEquals(m.source.getCol(), 4);
   assertEquals(m.source.getRow(), 4);
   assertEquals(m.dest.getCol(), 4);
   assertEquals(m.dest.getRow(), 5);
   assertEquals(m.moveType, Move::MOVE);
   assertEquals(m.capture, PieceType::ROOK);
   assertUnit(text == "e5e6r");
}  // teardown

 /*************************************
  * GET TEXT en passant
  * Input : source=4,4
  *         dest  =5,5
  *         type  =ENPASSANT
  *         capture=PAWN
  * Output:  e5f6E
  **************************************/
void TestMove::getText_enpassant()
{  // setup
   Move m;
   Position s(4,4);
   Position d(5,5);
   m.source   = s;
   m.dest     = d;
   m.moveType = Move::ENPASSANT;
   m.capture = PieceType::PAWN;
   string text = "";
   
   // exercise
   text = m.getText();
   
   // verify
   assertEquals(m.source.getCol(), 4);
   assertEquals(m.source.getRow(), 4);
   assertEquals(m.dest.getCol(), 5);
   assertEquals(m.dest.getRow(), 5);
   assertEquals(m.moveType, Move::ENPASSANT);
   assertEquals(m.capture, PieceType::PAWN);
   assertUnit(text == "e5f6E");
}  // teardown

 /*************************************
  * GET TEXT king side castle
  * Input : source=4,0
  *         dest  =6,0
  *         type  =CASTLE_KING
  * Output:  e1g1c
  **************************************/
void TestMove::getText_castleKing()
{  // setup
   Move m;
   Position s(4,0);
   Position d(6,0);
   m.source   = s;
   m.dest     = d;
   m.moveType = Move::CASTLE_KING;
   string text = "";
   
   // exercise
   text = m.getText();
   
   // verify
   assertEquals(m.source.getCol(), 4);
   assertEquals(m.source.getRow(), 0);
   assertEquals(m.dest.getCol(), 6);
   assertEquals(m.dest.getRow(), 0);
   assertEquals(m.moveType, Move::CASTLE_KING);
   assertUnit(text == "e1g1c");
}  // teardown

 /*************************************
  * GET TEXT queen side castle
  * Input : source=4,0
  *         dest  =2,0
  *         type  =CASTLE_QUEEN  
  * Output:  e1c1C
  **************************************/
void TestMove::getText_castleQueen()
{  // setup
   Move m;
   Position s(4,0);
   Position d(2,0);
   m.source   = s;
   m.dest     = d;
   m.moveType = Move::CASTLE_QUEEN;
   string text = "";
   
   // exercise
   text = m.getText();
   
   // verify
   assertEquals(m.source.getCol(), 4);
   assertEquals(m.source.getRow(), 0);
   assertEquals(m.dest.getCol(), 2);
   assertEquals(m.dest.getRow(), 0);
   assertEquals(m.moveType, Move::CASTLE_QUEEN);
   assertUnit(text == "e1c1C");
}  // teardown

 /*************************************
  * LETTER FROM PIECE TYPE space
  * Input :  SPACE
  * Output:  ' '
  **************************************/
void TestMove::letterFromPieceType_space()
{  // setup
   Move m;
   PieceType pt = SPACE;
   char c = 'z';
   
   // exercise
   c = m.letterFromPieceType(pt);
   
   // verify
   assertEquals(pt, SPACE);
   assertEquals(c, ' ');
}  // teardown

 /*************************************
  * LETTER FROM PIECE TYPE pawn
  * Input : PAWN
  * Output:  'p'
  **************************************/
void TestMove::letterFromPieceType_pawn()
{  // setup
   Move m;
   PieceType pt = PAWN;
   char c = 'z';
   
   // exercise
   c = m.letterFromPieceType(pt);
   
   // verify
   assertEquals(pt, PAWN);
   assertEquals(c, 'p');
}  // teardown

 /*************************************
  * LETTER FROM PIECE TYPE bishop
  * Input : BISHOP
  * Output:  'b'
  **************************************/
void TestMove::letterFromPieceType_bishop()
{  // setup
   Move m;
   PieceType pt = BISHOP;
   char c = 'z';
   
   // exercise
   c = m.letterFromPieceType(pt);
   
   // verify
   assertEquals(pt, BISHOP);
   assertEquals(c, 'b');
}  // teardown

 /*************************************
  * LETTER FROM PIECE TYPE knight
  * Input : KNIGHT
  * Output:  'n'
  **************************************/
void TestMove::letterFromPieceType_knight()
{  // setup
   Move m;
   PieceType pt = KNIGHT;
   char c = 'z';
   
   // exercise
   c = m.letterFromPieceType(pt);
   
   // verify
   assertEquals(pt, KNIGHT);
   assertEquals(c, 'n');
}  // teardown

 /*************************************
  * LETTER FROM PIECE TYPE rook
  * Input : ROOK
  * Output:  'r'
  **************************************/
void TestMove::letterFromPieceType_rook()
{  // setup
   Move m;
   PieceType pt = ROOK;
   char c = 'z';
   
   // exercise
   c = m.letterFromPieceType(pt);
   
   // verify
   assertEquals(pt, ROOK);
   assertEquals(c, 'r');
}  // teardown

 /*************************************
  * LETTER FROM PIECE TYPE queen
  * Input : QUEEN
  * Output:  'q'
  **************************************/
void TestMove::letterFromPieceType_queen()
{  // setup
   Move m;
   PieceType pt = QUEEN;
   char c = 'z';
   
   // exercise
   c = m.letterFromPieceType(pt);
   
   // verify
   assertEquals(pt, QUEEN);
   assertEquals(c, 'q');
}  // teardown

 /*************************************
  * LETTER FROM PIECE TYPE king
  * Input : KING
  * Output:  'k'
  **************************************/
void TestMove::letterFromPieceType_king()
{  // setup
   Move m;
   PieceType pt = KING;
   char c = 'z';
   
   // exercise
   c = m.letterFromPieceType(pt);
   
   // verify
   assertEquals(pt, KING);
   assertEquals(c, 'k');
}  // teardown

 /*************************************
  * PIECE TYPE FROM LETTER pawn
  * Input : 'p'
  * Output:  PAWN
  **************************************/
void TestMove::pieceTypeFromLetter_pawn()
{  // setup
   Move m;
   char c = 'p';
   PieceType pt = INVALID;
   
   // exercise
   pt = m.pieceTypeFromLetter(c);
   
   // verify
   assertEquals(c, 'p');
   assertEquals(pt, PAWN);
}  // teardown

 /*************************************
  * PIECE TYPE FROM LETTER bishop
  * Input : 'b'
  * Output:  BISHOP
  **************************************/
void TestMove::pieceTypeFromLetter_bishop()
{  // setup
   Move m;
   char c = 'b';
   PieceType pt = INVALID;
   
   // exercise
   pt = m.pieceTypeFromLetter(c);
   
   // verify
   assertEquals(c, 'b');
   assertEquals(pt, BISHOP);
}  // teardown

 /*************************************
  * PIECE TYPE FROM LETTER knight
  * Input : 'n'
  * Output:  KNIGHT
  **************************************/
void TestMove::pieceTypeFromLetter_knight()
{  // setup
   Move m;
   char c = 'n';
   PieceType pt = INVALID;
   
   // exercise
   pt = m.pieceTypeFromLetter(c);
   
   // verify
   assertEquals(c, 'n');
   assertEquals(pt, KNIGHT);
}  // teardown

 /*************************************
  * PIECE TYPE FROM LETTER rook
  * Input : 'r'
  * Output:  ROOK
  **************************************/
void TestMove::pieceTypeFromLetter_rook()
{  // setup
   Move m;
   char c = 'r';
   PieceType pt = INVALID;
   
   // exercise
   pt = m.pieceTypeFromLetter(c);
   
   // verify
   assertEquals(c, 'r');
   assertEquals(pt, ROOK);
}  // teardown

 /*************************************
  * PIECE TYPE FROM LETTER queen
  * Input : 'q'
  * Output:  QUEEN
  **************************************/
void TestMove::pieceTypeFromLetter_queen()
{  // setup
   Move m;
   char c = 'q';
   PieceType pt = INVALID;
   
   // exercise
   pt = m.pieceTypeFromLetter(c);
   
   // verify
   assertEquals(c, 'q');
   assertEquals(pt, QUEEN);
}  // teardown

 /*************************************
  * PIECE TYPE FROM LETTER king
  * Input : 'k'
  * Output:  KING
  **************************************/
void TestMove::pieceTypeFromLetter_king() 
{  // setup
   Move m;
   char c = 'k';
   PieceType pt = INVALID;
   
   // exercise
   pt = m.pieceTypeFromLetter(c);
   
   // verify
   assertEquals(c, 'k');
   assertEquals(pt, KING);
}  // teardown


 /*************************************
  * EQUAL - NOT
  * Input : b2b4 == b2b5
  * Output: false
  **************************************/
void TestMove::equal_not()
{  // setup
   Move m1;
   Move m2;
   Position s1 = "b2";
   Position d1 = "b4";
   Position s2 = "b2";
   Position d2 = "b5";
   m1.source = s1;
   m1.dest   = d1;
   m2.source = s2;
   m2.dest   = d2;
   bool result = true;
   
   // exercise
   result = m1 == m2;
   
   // verify
   assertEquals(result, false);
}  // teardown

 /*************************************
  * EQUAL - EQUALS
  * Input : b2b4 == b2b4
  * Output: true
  **************************************/
void TestMove::equal_equals()
{  // setup
   Move m1;
   Move m2;
   Position s1 = "b2";
   Position d1 = "b4";
   Position s2 = "b2";
   Position d2 = "b4";
   m1.source = s1;
   m1.dest   = d1;
   m2.source = s2;
   m2.dest   = d2;
   bool result = false;
   
   // exercise
   result = m1 == m2;
   
   // verify
   assertEquals(result, true);
}  // teardown

 /*************************************
  * LESS THAN - LESS THAN
  * Input : b2b2 < b2b4
  * Output: false
  *    Note that the less-than operator is needed
  *    so std::set<T> can sort the elements. Thus,
  *    any T in a set must define less-than. In this
  *    case, I defined it according to the 
  *     destination's Position's location.
  **************************************/
void TestMove::lessthan_lessthan()
{  // setup
   Move m1;
   Move m2;
   Position s1 = "b2";
   Position d1 = "b2";
   Position s2 = "b2";
   Position d2 = "b4";
   m1.source = s1;
   m1.dest   = d1;
   m2.source = s2;
   m2.dest   = d2;
   bool result = false;
   
   // exercise
   result = m1 < m2;
   
   // verify
   assertEquals(result, true);
}  // teardown

 /*************************************
  * LESS THAN - EQUALS
  * Input : b2b4 < b2b4
  * Output: false
  **************************************/
void TestMove::lessthan_equals()
{  // setup
   Move m1;
   Move m2;
   Position s1 = "b2";
   Position d1 = "b4";
   Position s2 = "b2";
   Position d2 = "b4";
   m1.source = s1;
   m1.dest   = d1;
   m2.source = s2;
   m2.dest   = d2;
   bool result = true;
   
   // exercise
   result = m1 < m2;
   
   // verify
   assertEquals(result, false);
}  // teardown

 /*************************************
  * LESS THAN - GREATAER THAN
  * Input : b2b4 < b2b2
  * Output: false
  **************************************/
void TestMove::lessthan_greaterthan()
{  // setup
   Move m1;
   Move m2;
   Position s1 = "b2";
   Position d1 = "b4";
   Position s2 = "b2";
   Position d2 = "b2";
   m1.source = s1;
   m1.dest   = d1;
   m2.source = s2;
   m2.dest   = d2;
   bool result = true;
   
   // exercise
   result = m1 < m2;
   
   // verify
   assertEquals(result, false);
}  // teardown
