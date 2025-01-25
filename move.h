/***********************************************************************
 * Header File:
 *    MOVE
 * Author:
 *    <your name here>
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


    // Constructor
    Move();

    bool operator==(const Move& rhs) const {
        return source == rhs.source &&
            dest == rhs.dest &&
            moveType == rhs.moveType &&
            promote == rhs.promote &&
            capture == rhs.capture &&
            isWhite == rhs.isWhite;
    }
    bool operator<(const Move& rhs) const
    {
        return this->dest.getLocation() < rhs.dest.getLocation();
    }
    // Core methods (Ticket 4)
    void setSource(const Position& src) { source = src; }
    void setDest(const Position& dst) { dest = dst; }
    Position getSource() const { return source; }
    Position getDest() const { return dest; }

    void setMoveType(MoveType type) { moveType = type; }
    MoveType getMoveType() const { return moveType; }

    void setPromotion(PieceType pt) { promote = pt; }
    PieceType getPromotion() const { return promote; }

    void setCapture(PieceType pt) { capture = pt; }
    PieceType getCapture() const { return capture; }

    void setIsWhite(bool white) { isWhite = white; }
    bool getIsWhite() const { return isWhite; }

    // Text methods (Ticket 5)
    void setText(const std::string& moveText)
    {
        text = moveText;

        // Parse source and destination positions
        if (text.length() >= 4)
        {
            source = Position(text[1] - '1', text[0] - 'a'); // e.g., "e5" -> col=4, row=4
            dest = Position(text[3] - '1', text[2] - 'a');   // e.g., "d6" -> col=3, row=5

            // Check for additional characters
            if (text.length() == 5)
            {
                char extra = text[4];
                switch (extra)
                {
                case 'r': capture = ROOK; break;
                case 'n': capture = KNIGHT; break;
                case 'b': capture = BISHOP; break;
                case 'q': capture = QUEEN; break;
                case 'k': capture = KING; break;
                case 'p': capture = PAWN; break;
                case 'E': moveType = ENPASSANT; break;
                case 'C': moveType = CASTLE_QUEEN; break;
                case 'c': moveType = CASTLE_KING; break;
                default: promote = pieceTypeFromLetter(extra); break;
                }
            }
            else
            {
                moveType = MOVE; // Default move type
            }
        }
    }


    std::string getText() const {
        if (source.isInvalid() || dest.isInvalid()) // Ensure positions are valid
            return "Invalid Move";

        std::string moveText;
        moveText += char(source.getCol() + 'a');  // Convert column to letter
        moveText += char(source.getRow() + '1'); // Convert row to number
        moveText += char(dest.getCol() + 'a');   // Convert column to letter
        moveText += char(dest.getRow() + '1');   // Convert row to number
        if (promote != SPACE)
            moveText += letterFromPieceType(promote);
        return moveText;
    }

private:
    char letterFromPieceType(PieceType pt) const {
        switch (pt) {
        case KING:   return 'k';
        case QUEEN:  return 'q';
        case ROOK:   return 'r';
        case BISHOP: return 'b';
        case KNIGHT: return 'n';
        case PAWN:   return 'p';
        default:     return ' ';
        }
    }

    PieceType pieceTypeFromLetter(char letter) const {
        switch (letter) {
        case 'k': return KING;
        case 'q': return QUEEN;
        case 'r': return ROOK;
        case 'b': return BISHOP;
        case 'n': return KNIGHT;
        case 'p': return PAWN;
        default:  return SPACE;
        }
    }

    Position  source;    // Where the move originated from
    Position  dest;      // Where the move finished
    PieceType promote;   // Piece to be promoted to
    PieceType capture;   // Captured piece, if any
    MoveType  moveType;  // Type of move
    bool      isWhite;   // True if the move is for white pieces
    std::string text;    // Textual version of the move
};
