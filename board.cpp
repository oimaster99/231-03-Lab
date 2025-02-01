/***********************************************************************
 * Source File:
 *    BOARD
 * Author:
 *    <your name here>
 * Summary:
 *    A collection of pieces and the state of the board
 ************************************************************************/

#include "board.h"
#include "position.h"
#include "piece.h"
#include <cassert>
using namespace std;

/***********************************************
* BOARD : CONSTRUCT
*         Give every piece a place on the board.
***********************************************/
Board::Board(ogstream* pgout, bool noreset) : pgout(pgout), numMoves(0)
{
	for (int r = 0; r < 8; r++)
		for (int c = 0; c < 8; c++)
			board[r][c] = nullptr;	
}


// we really REALLY need to delete this.
Space space;

/***********************************************
* BOARD : GET
*         Get a piece from a given position.
***********************************************/
const Piece& Board::operator [] (const Position& pos) const
{
	assert(0 <= pos.getCol() && pos.getCol() < 8);
	assert(0 <= pos.getRow() && pos.getRow() < 8);
	assert(nullptr != board[pos.getCol()][pos.getRow()]);
	return *board[pos.getCol()][pos.getRow()];
}
void Board::move(const Move& move)
{
	assert(false);
}
Piece& Board::operator [] (const Position& pos)
{
	assert(0 <= pos.getCol() && pos.getCol() < 8);
	assert(0 <= pos.getRow() && pos.getRow() < 8);
	assert(nullptr != board[pos.getCol()][pos.getRow()]);
	return *board[pos.getCol()][pos.getRow()];
}


/**********************************************
 * BOARD EMPTY
 * The game board that is completely empty.
 * It does not even have spaces though each non-filled
 * spot will report it has a space. This is for unit testing
 *********************************************/
BoardEmpty::BoardEmpty() : BoardDummy(), pSpace(nullptr)
{
   pSpace = new Space;
}
BoardEmpty::~BoardEmpty() 
{
   delete pSpace;
}