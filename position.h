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
public:

   // Position :    The Position class can work with other positions,
   //               Allowing for comparisions, copying, etc.
   Position(const Position & rhs) {    }
   Position() : colRow(0x99)      {              }
   bool isInvalid() const { if (colRow > 0x77 || colRow < 0x00) {return true;} }
   bool isValid()   const         { return !isInvalid(); }
   void setValid() { set(0x00); }
   void setInvalid() { set(0x99); }
   bool operator <  (const Position & rhs) const { return true; }
   bool operator == (const Position & rhs) const { return true; }
   bool operator != (const Position & rhs) const { return true; }
   const Position & operator =  (const Position & rhs) { return *this; }
   
   // Location : The Position class can work with locations, which
   //            are 0...63 where we start in row 0, then row 1, etc.
   Position(int location) : colRow(0x99) { }
   int getLocation() const               { return colRow; }
   void setLocation(int location)        {           }

   
   // Row/Col : The position class can work with row/column,
   //           which are 0..7 and 0...7
   Position(int c, int r) : colRow(0x99)  {           }
   virtual int getCol() const                     { return 9; }
   virtual int getRow() const                     { return 9; }
   void setRow(int r)                     {           }
   void setCol(int c)                     {           }
   void set(int c, int r)                 {           }

   // Text:    The Position class can work with textual coordinates,
   //          such as "d4"
   
   Position(const char * s) : colRow(0x99) {   }
   const Position & operator =  (const char     * rhs) { return *this; }
   const Position & operator =  (const string   & rhs) { return *this; }

   
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
      set(    (int)(x / getSquareWidth ()) - 1,
          8 - (int)(y / getSquareHeight())   );
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
   Position(const Position & rhs, const Delta & delta) : colRow(-1) {  }
   void adjustRow(int dRow) { if ((colRow + 1) < 0x78) { colRow += 1; } }
   void adjustCol(int dCol)   { if ((colRow + 16) < 0x78) { colRow += 16; } }
   const Position & operator += (const Delta & rhs) { return *this; }
   Position operator + (const Delta & rhs) const { return *this; }

private:
    void set(uint8_t colRowNew) const { colRow == colRowNew; }
   
   uint8_t colRow;
   static double squareWidth;
   static double squareHeight;
};


ostream & operator << (ostream & out, const Position & pos);
istream & operator >> (istream & in,  Position & pos);
      
