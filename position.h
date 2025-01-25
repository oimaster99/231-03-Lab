/***********************************************************************
 * Header File:
 *    POSITION
 * Author:
 *    <your name here>
 * Summary:
 *    The position of a piece, the cursor, or a possible move on a chess board
 ************************************************************************/
 /***********************************************************************
  * Header File:
  *    POSITION
  * Author:
  *    <your name here>
  * Summary:
  *    The position of a piece, the cursor, or a possible move on a chess board
  ************************************************************************/

#pragma once

#include <string>
#include <cstdint>
#include <iostream>
#include <cstring>
using std::string;
using std::ostream;
using std::istream;

const int SIZE_SQUARE = 32;   // number of pixels in a square by default

/***********************************************
 * DELTA
 * Movement in a direction (dRow and dCol)
 **********************************************/
struct Delta
{
    int dRow;
    int dCol;
};

const Delta ADD_R = { 1,  0 };
const Delta ADD_C = { 0,  1 };
const Delta SUB_R = { -1,  0 };
const Delta SUB_C = { 0, -1 };


class PositionTest;

/***************************************************
 * POSITION
 * The location of a piece on the board
 ***************************************************/
class Position
{
    friend class PositionTest;
public:

    // Position :    The Position class can work with other positions,
    //               Allowing for comparisions, copying, etc.
    Position(const Position& rhs) { colRow = rhs.colRow; }
    Position() : colRow(0xFF) {} // Default to invalid position
    bool isInvalid() const { return (colRow & 0x88) != 0; }
    bool isValid() const { return !isInvalid(); }

    void setValid() { colRow = 0x00; }
    void setInvalid() { colRow = 0xFF; }

    bool operator <  (const Position& rhs) const { return colRow < rhs.colRow; }
    bool operator == (const Position& rhs) const { return colRow == rhs.colRow; }
    bool operator != (const Position& rhs) const { return colRow != rhs.colRow; }
    const Position& operator =  (const Position& rhs) { colRow = rhs.colRow; return *this; }

    // Location : The Position class can work with locations, which
    //            are 0...63 where we start in row 0, then row 1, etc.
    Position(int location) : colRow(0xFF) { setLocation(location); }
    int getLocation() const { return (getRow() * 8) + getCol(); }
    void setLocation(int location) { set(location % 8, location / 8); }


    // Row/Col : The position class can work with row/column,
    //           which are 0..7 and 0...7
    Position(int c, int r) : colRow(0xFF) { set(c, r); }
    int getCol() const
    {
        if (isInvalid()) // If the position is invalid, return -1
            return -1;

        return (colRow & 0xF0) >> 4; // Extract the column from colRow
    }
    int getRow() const
    {
        if (isInvalid()) // If the position is invalid, return -1
            return -1;

        return (colRow & 0x0F); // Extract the row from colRow
    }
    void setRow(int r) { colRow = (colRow & 0xF0) | (r & 0x07); }
    void setCol(int c) { colRow = (colRow & 0x0F) | ((c & 0x07) << 4); }
    void set(int col, int row)
    {
        if (col < 0 || col >= 8 || row < 0 || row >= 8)
        {
            setInvalid(); // Mark as invalid if out of bounds
            return;
        }

        colRow = ((col & 0x07) << 4) | (row & 0x07); // Encode column and row into colRow
    }

    // Text:    The Position class can work with textual coordinates,
    //          such as "d4"
    const Position& operator=(const char* rhs)
    {
        if (rhs && std::strlen(rhs) == 2) // Ensure input is valid and 2 characters long
        {
            char colChar = rhs[0];
            char rowChar = rhs[1];

            // Validate column ('a' to 'h') and row ('1' to '8')
            if (colChar >= 'a' && colChar <= 'h' && rowChar >= '1' && rowChar <= '8')
            {
                int col = colChar - 'a'; // Convert column to index
                int row = rowChar - '1'; // Convert row to index
                set(col, row);           // Set the position
                return *this;
            }
        }

        // If input is invalid, mark the position as invalid
        setInvalid();
        return *this;
    }
    const Position& operator=(const std::string& rhs)
    {
        return *this = rhs.c_str(); // Delegate to operator=(const char*)
    }


    // Pixels:    The Position class can work with screen coordinates,
    //            a.k.a. Pixels, these are X and Y coordinates. Note that
    //            we need to scale them according to the size of the board.
    int getX() const { return (int)((double)getCol() * getSquareWidth() + getSquareWidth()); }
    int getY() const { return (int)((double)getRow() * getSquareHeight() + getSquareHeight()); }
    void setXY(double x, double y)
    {
        // Calculate the column (x-coordinate) and row (y-coordinate)
        int col = static_cast<int>(x / squareWidth) - 1;
        int row = 8 - static_cast<int>(y / squareHeight);

        // Check for invalid X or Y positions
        if (col < 0 || col >= 8 || row < 0 || row >= 8)
        {
            setInvalid(); // Mark the position as invalid
            return;
        }

        // Set the position if within bounds
        set(col, row);
    }


    double getSquareWidth() const { return squareWidth; }
    double getSquareHeight() const { return squareHeight; }
    void setBoardWidthHeight(int widthBoard, int heightBoard)
    {
        if (widthBoard < 0 || heightBoard < 0)
            return;
        squareWidth = (double)widthBoard / 10.0; // 8 squares + 2 spaces
        squareHeight = (double)heightBoard / 10.0;
    }

    // Delta:    The Position class can work with deltas, which are
    //           offsets from a given location. This helps pieces move
    //           on the chess board.
    Position(const Position& rhs, const Delta& delta) : colRow(0xFF)
    {
        set(rhs.getCol() + delta.dCol, rhs.getRow() + delta.dRow);
    }

    void adjustRow(int dRow) { setRow(getRow() + dRow); }
    void adjustCol(int dCol) { setCol(getCol() + dCol); }

    const Position& operator+=(const Delta& rhs)
    {
        if (isInvalid()) // If already invalid, don't modify
            return *this;

        int newRow = getRow() + rhs.dRow;
        int newCol = getCol() + rhs.dCol;

        // Check if the new position is off the board
        if (newRow < 0 || newRow >= 8 || newCol < 0 || newCol >= 8)
        {
            setInvalid();
        }
        else
        {
            set(newCol, newRow); // Set the new position if valid
        }
        return *this;
    }
    Position operator + (const Delta& rhs) const
    {
        return Position(*this, rhs);
    }

private:
    void set(uint8_t colRowNew) const { colRow == colRowNew; }

    uint8_t colRow;
    static double squareWidth;
    static double squareHeight;
};


ostream& operator << (ostream& out, const Position& pos);
istream& operator >> (istream& in, Position& pos);