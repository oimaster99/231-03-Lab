/***********************************************************************
 * Header File:
 *    TEST MOVE 
 * Author:
 *    <your name here>
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
{
    Move move;
    assertUnit(move.getSource().isInvalid());
    assertUnit(move.getDest().isInvalid());
}

 /*************************************
  * CONSTRUCTOR : standard string move
  * Input:  e5e6
  * Output: source=4,4
  *         dest  =4,5
  *         type  =MOVE
  **************************************/
void TestMove::constructString_simple()
{
    Move move;
    move.setText("e5e6");
    assertUnit(move.getSource().getCol() == 4); // 'e' -> column 4
    assertUnit(move.getSource().getRow() == 4); // '5' -> row 4
    assertUnit(move.getDest().getCol() == 4);   // 'e' -> column 4
    assertUnit(move.getDest().getRow() == 5);   // '6' -> row 5
    assertUnit(move.getMoveType() == Move::MOVE);
}


 /*************************************
  * READ simple move 
  * Input:  e5e6
  * Output: source=4,4
  *         dest  =4,5
  *         type  =MOVE
  **************************************/
void TestMove::read_simple()
{
    Move move;
    move.setText("e5e6");
    assertUnit(move.getSource().getCol() == 4);
    assertUnit(move.getSource().getRow() == 4);
    assertUnit(move.getDest().getCol() == 4);
    assertUnit(move.getDest().getRow() == 5);
    assertUnit(move.getMoveType() == Move::MOVE);
}


 /*************************************
  * READ capture move 
  * Input:  e5d6r
  * Output: source=4,4
  *         dest  =3,5
  *         type  =MOVE
  *         capture=ROOK
  **************************************/
void TestMove::read_capture()
{
    Move move;
    move.setText("e5d6r");
    assertUnit(move.getSource().getCol() == 4);
    assertUnit(move.getSource().getRow() == 4);
    assertUnit(move.getDest().getCol() == 3);  // 'd' -> column 3
    assertUnit(move.getDest().getRow() == 5);  // '6' -> row 5
    assertUnit(move.getMoveType() == Move::MOVE);
    assertUnit(move.getCapture() == ROOK);
}


 /*************************************
  * READ enpassant move 
  * Input:  e5f6E
  * Output: source=4,4
  *         dest  =5,5
  *         type  =ENPASSANT
  **************************************/
void TestMove::read_enpassant()
{
    Move move;
    move.setText("e5f6E");
    assertUnit(move.getSource().getCol() == 4);
    assertUnit(move.getSource().getRow() == 4);
    assertUnit(move.getDest().getCol() == 5);
    assertUnit(move.getDest().getRow() == 5);
    assertUnit(move.getMoveType() == Move::ENPASSANT);
}


 /*************************************
  * READ king side castle
  * Input:  e1g1c
  * Output: source=4,0
  *         dest  =6,0
  *         type  =CASTLE_KING
  **************************************/
void TestMove::read_castleKing()
{
    Move move;
    move.setText("e1g1c");
    assertUnit(move.getSource().getCol() == 4); // 'e' -> column 4
    assertUnit(move.getSource().getRow() == 0); // '1' -> row 0
    assertUnit(move.getDest().getCol() == 6);   // 'g' -> column 6
    assertUnit(move.getDest().getRow() == 0);   // '1' -> row 0
    assertUnit(move.getMoveType() == Move::CASTLE_KING);
}

 /*************************************
  * READ queen side castle
  * Input:  e1c1C
  * Output: source=4,0
  *         dest  =2,0
  *         type  =CASTLE_QUEEN
  **************************************/
void TestMove::read_castleQueen()
{
    Move move;
    move.setText("e1c1C");
    assertUnit(move.getSource().getCol() == 4); // 'e' -> column 4
    assertUnit(move.getSource().getRow() == 0); // '1' -> row 0
    assertUnit(move.getDest().getCol() == 2);   // 'c' -> column 2
    assertUnit(move.getDest().getRow() == 0);   // '1' -> row 0
    assertUnit(move.getMoveType() == Move::CASTLE_QUEEN);
}

 /*************************************
  * ASSIGN simple move
  * Input:  e5e6
  * Output: source=4,4
  *         dest  =4,5
  *         type  =MOVE
  **************************************/
void TestMove::assign_simple()
{
    Move move;
    move.setText("e5e6");

    // Validate source position
    assertUnit(move.getSource().getCol() == 4); // 'e' -> column 4
    assertUnit(move.getSource().getRow() == 4); // '5' -> row 4

    // Validate destination position
    assertUnit(move.getDest().getCol() == 4);   // 'e' -> column 4
    assertUnit(move.getDest().getRow() == 5);   // '6' -> row 5

    // Validate move type
    assertUnit(move.getMoveType() == Move::MOVE);
}

 /*************************************
  * ASSIGN capture move
  * Input:  e5d6r
  * Output: source=4,4
  *         dest  =3,5
  *         type  =MOVE
  *         capture=ROOK
  **************************************/
void TestMove::assign_capture()
{
    Move move;
    move.setText("e5d6r");

    // Validate source position
    assertUnit(move.getSource().getCol() == 4); // 'e' -> column 4
    assertUnit(move.getSource().getRow() == 4); // '5' -> row 4

    // Validate destination position
    assertUnit(move.getDest().getCol() == 3);   // 'd' -> column 3
    assertUnit(move.getDest().getRow() == 5);   // '6' -> row 5

    // Validate move type
    assertUnit(move.getMoveType() == Move::MOVE);

    // Validate capture piece
    assertUnit(move.getCapture() == ROOK);
}
 /*************************************
  * ASSIGN enpassant move
  * Input:  e5f6E
  * Output: source=4,4
  *         dest  =5,5
  *         type  =ENPASSANT
  **************************************/
void TestMove::assign_enpassant()
{
    Move move;
    move.setText("e5f6E");

    // Validate source position
    assertUnit(move.getSource().getCol() == 4); // 'e' -> column 4
    assertUnit(move.getSource().getRow() == 4); // '5' -> row 4

    // Validate destination position
    assertUnit(move.getDest().getCol() == 5);   // 'f' -> column 5
    assertUnit(move.getDest().getRow() == 5);   // '6' -> row 5

    // Validate move type
    assertUnit(move.getMoveType() == Move::ENPASSANT);
}

 /*************************************
  * ASSIGN king side castle
  * Input:  e1g1c
  * Output: source=4,0
  *         dest  =6,0
  *         type  =CASTLE_KING
  **************************************/
void TestMove::assign_castleKing()
{
    Move move;
    move.setText("e1g1c");

    // Validate source position
    assertUnit(move.getSource().getCol() == 4); // 'e' -> column 4
    assertUnit(move.getSource().getRow() == 0); // '1' -> row 0

    // Validate destination position
    assertUnit(move.getDest().getCol() == 6);   // 'g' -> column 6
    assertUnit(move.getDest().getRow() == 0);   // '1' -> row 0

    // Validate move type
    assertUnit(move.getMoveType() == Move::CASTLE_KING);
}

 /*************************************
  * ASSIGN queen side castle
  * Input:  e1c1C
  * Output: source=4,0
  *         dest  =2,0
  *         type  =CASTLE_QUEEN
  **************************************/
void TestMove::assign_castleQueen()
{
    Move move;
    move.setText("e1c1C");

    // Validate source position
    assertUnit(move.getSource().getCol() == 4); // 'e' -> column 4
    assertUnit(move.getSource().getRow() == 0); // '1' -> row 0

    // Validate destination position
    assertUnit(move.getDest().getCol() == 2);   // 'c' -> column 2
    assertUnit(move.getDest().getRow() == 0);   // '1' -> row 0

    // Validate move type
    assertUnit(move.getMoveType() == Move::CASTLE_QUEEN);
}

 /*************************************
  * GET TEXT simple move
  * Input : source=4,4
  *         dest  =4,5
  *         type  =MOVE
  * Output:  e5e6
  **************************************/
void TestMove::getText_simple()
{
    Move move;
    move.setSource(Position(4, 4)); // e5
    move.setDest(Position(4, 5));  // e6
    move.setMoveType(Move::MOVE);
    assertUnit(move.getText() == "e5e6");
}

 /*************************************
  * GET TEXT capture
  * Input : source=4,4
  *         dest  =4,5
  *         type  =MOVE
  *         capture=ROOK
  * Output:  e5e6r
  **************************************/
void TestMove::getText_capture()
{
    Move move;
    move.setSource(Position(4, 4)); // e5
    move.setDest(Position(3, 5));  // d6
    move.setCapture(ROOK);
    assertUnit(move.getText() == "e5d6r");
}

 /*************************************
  * GET TEXT en passant
  * Input : source=4,4
  *         dest  =5,5
  *         type  =ENPASSANT
  *         capture=PAWN
  * Output:  e5f6E
  **************************************/
void TestMove::getText_enpassant()
{
    Move move;
    move.setSource(Position(4, 4)); // e5
    move.setDest(Position(5, 5));  // f6
    move.setMoveType(Move::ENPASSANT);
    move.setCapture(PAWN);
    assertUnit(move.getText() == "e5f6E");
}

 /*************************************
  * GET TEXT king side castle
  * Input : source=4,0
  *         dest  =6,0
  *         type  =CASTLE_KING
  * Output:  e1g1c
  **************************************/
void TestMove::getText_castleKing()
{
    Move move;
    move.setSource(Position(4, 0)); // e1
    move.setDest(Position(6, 0));  // g1
    move.setMoveType(Move::CASTLE_KING);

    // Validate the generated text
    assertUnit(move.getText() == "e1g1c");
}
 /*************************************
  * GET TEXT queen side castle
  * Input : source=4,0
  *         dest  =2,0
  *         type  =CASTLE_QUEEN  
  * Output:  e1c1C
  **************************************/
void TestMove::getText_castleQueen()
{
    Move move;
    move.setSource(Position(4, 0)); // e1
    move.setDest(Position(2, 0));  // c1
    move.setMoveType(Move::CASTLE_QUEEN);

    // Validate the generated text
    assertUnit(move.getText() == "e1c1C");
}
 /*************************************
  * LETTER FROM PIECE TYPE space
  * Input :  SPACE
  * Output:  ' '
  **************************************/
void TestMove::letterFromPieceType_space()
{
    Move move;
    assertUnit(move.letterFromPieceType(SPACE) == ' ');
}
 /*************************************
  * LETTER FROM PIECE TYPE pawn
  * Input : PAWN
  * Output:  'p'
  **************************************/
void TestMove::letterFromPieceType_pawn()
{
    Move move;
    assertUnit(move.letterFromPieceType(PAWN) == 'p');
}


 /*************************************
  * LETTER FROM PIECE TYPE bishop
  * Input : BISHOP
  * Output:  'b'
  **************************************/
void TestMove::letterFromPieceType_bishop()
{
    Move move;
    assertUnit(move.letterFromPieceType(BISHOP) == 'b');
}

 /*************************************
  * LETTER FROM PIECE TYPE knight
  * Input : KNIGHT
  * Output:  'n'
  **************************************/
void TestMove::letterFromPieceType_knight()
{
    Move move;
    assertUnit(move.letterFromPieceType(KNIGHT) == 'n');
}

 /*************************************
  * LETTER FROM PIECE TYPE rook
  * Input : ROOK
  * Output:  'r'
  **************************************/
void TestMove::letterFromPieceType_rook()
{
    Move move;
    assertUnit(move.letterFromPieceType(ROOK) == 'r');
}

 /*************************************
  * LETTER FROM PIECE TYPE queen
  * Input : QUEEN
  * Output:  'q'
  **************************************/
void TestMove::letterFromPieceType_queen()
{
    Move move;
    assertUnit(move.letterFromPieceType(QUEEN) == 'q');
}

 /*************************************
  * LETTER FROM PIECE TYPE king
  * Input : KING
  * Output:  'k'
  **************************************/
void TestMove::letterFromPieceType_king()
{
    Move move;
    assertUnit(move.letterFromPieceType(KING) == 'k');
}

 /*************************************
  * PIECE TYPE FROM LETTER pawn
  * Input : 'p'
  * Output:  PAWN
  **************************************/
void TestMove::pieceTypeFromLetter_pawn()
{
    Move move;
    assertUnit(move.pieceTypeFromLetter('p') == PAWN);
}

 /*************************************
  * PIECE TYPE FROM LETTER bishop
  * Input : 'b'
  * Output:  BISHOP
  **************************************/
void TestMove::pieceTypeFromLetter_bishop()
{
    Move move;
    assertUnit(move.pieceTypeFromLetter('b') == BISHOP);
}

 /*************************************
  * PIECE TYPE FROM LETTER knight
  * Input : 'n'
  * Output:  KNIGHT
  **************************************/
void TestMove::pieceTypeFromLetter_knight()
{
    Move move;
    assertUnit(move.pieceTypeFromLetter('n') == KNIGHT);
}

 /*************************************
  * PIECE TYPE FROM LETTER rook
  * Input : 'r'
  * Output:  ROOK
  **************************************/
void TestMove::pieceTypeFromLetter_rook()
{
    Move move;
    assertUnit(move.pieceTypeFromLetter('r') == ROOK);
}

 /*************************************
  * PIECE TYPE FROM LETTER queen
  * Input : 'q'
  * Output:  QUEEN
  **************************************/
void TestMove::pieceTypeFromLetter_queen()
{
    Move move;
    assertUnit(move.pieceTypeFromLetter('q') == QUEEN);
}

 /*************************************
  * PIECE TYPE FROM LETTER king
  * Input : 'k'
  * Output:  KING
  **************************************/
void TestMove::pieceTypeFromLetter_king()
{
    Move move;
    assertUnit(move.pieceTypeFromLetter('k') == KING);
}


 /*************************************
  * EQUAL - NOT
  * Input : b2b4 == b2b5
  * Output: false
  **************************************/
void TestMove::equal_not()
{
    Move move1, move2;
    move1.setText("b2b4");
    move2.setText("b2b5");
    assertUnit(!(move1 == move2));
}

 /*************************************
  * EQUAL - EQUALS
  * Input : b2b4 == b2b4
  * Output: true
  **************************************/
void TestMove::equal_equals()
{
    Move move1, move2;
    move1.setText("b2b4");
    move2.setText("b2b4");
    assertUnit(move1 == move2);
}

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
{
    Move move1, move2;
    move1.setText("b2b2");
    move2.setText("b2b4");
    assertUnit(!(move1 < move2));
}


 /*************************************
  * LESS THAN - EQUALS
  * Input : b2b4 < b2b4
  * Output: false
  **************************************/
void TestMove::lessthan_equals()
{
    Move move1, move2;
    move1.setText("b2b4");
    move2.setText("b2b4");
    assertUnit(!(move1 < move2));
}

 /*************************************
  * LESS THAN - GREATAER THAN
  * Input : b2b4 < b2b2
  * Output: false
  **************************************/
void TestMove::lessthan_greaterthan()
{
    Move move1, move2;
    move1.setText("b2b4");
    move2.setText("b2b2");
    assertUnit(!(move1 < move2));
}