/*
*  This file is part of nuTetris
*
*  nuTetris is free software; you can redistribute it and/or modify
*  it under the terms of the MIT License.
*
*  nuTetris is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  MIT License for more details.
*
*  Author: <antonino.calderone@gmail.com>
*
*/


/* -------------------------------------------------------------------------- */

#ifndef _TETRIS_PIECE_H_
#define _TETRIS_PIECE_H_


/* -------------------------------------------------------------------------- */

#include <array>
#include <memory>


/* -------------------------------------------------------------------------- */

namespace tetris
{


/* -------------------------------------------------------------------------- */

//! @brief It is an abstract class that is a blueprint for each tetris piece
class piece_t
{
public:
   enum {
      ROWS = 4,
      COLS = 4,
      ORIENTATIONS = 4
   };

   //! Color attribute type
   using col_t = int;

   //! Piece shape grid-row
   using row_t = std::array < col_t, COLS > ;

   //! Piece shape data type
   using shapedata_t = std::array < row_t, ROWS > ;

   //! Column / Row coordinate type
   using coord_t = int;
      
   //! Unique (smart) pointer to piece_t
   using handle_t = std::unique_ptr < piece_t > ;

   //! Clones the piece returning a unique pointer to it
   virtual handle_t clone() const = 0;

   //! Increments game-grid related piece column offset
   virtual void move_right() throw() = 0;

   //! Decrements game-grid related piece column offset
   virtual void move_left() throw() = 0;

   //! Increments game-grid related piece row offset
   virtual void move_down() throw() = 0;

   //! Rotates the piece clockwise
   virtual void rotate_cw() throw() = 0;  //clockwise
   
   //! Rotates the piece anticlockwise
   virtual void rotate_acw() throw() = 0; //anticlockwise

   //! Undoes the last moviment command
   virtual void undo() throw() = 0;

   //! Gets color attribute reference at piece-grid coordinates col, row
   virtual col_t & at(const coord_t& col, const coord_t& row) throw() = 0;
   
   //! Gets color attribute at piece-grid coordinates col, row
   virtual const col_t & at(const coord_t& col, const coord_t& row) const throw() = 0;

   //! Gets game-grid piece column offset
   virtual coord_t get_col() const throw() = 0;

   //! Gets game-grid piece row offset
   virtual coord_t get_row() const throw() = 0;
   
   //! Gets the count of empty piece-grid columns on the left side of piece shape
   virtual coord_t get_left_margin() const throw() = 0;

   //! Gets the count of empty piece-grid columns on the right side of piece shape
   virtual coord_t get_right_margin() const throw() = 0;

   //! Gets the count of empty piece-grid rows on the top side of piece shape
   virtual coord_t get_top_margin() const throw() = 0;

   //! Gets the count of empty piece-grid rows on the bottom side of piece shape
   virtual coord_t get_bottom_margin() const throw() = 0;
   
   //! dtor
   virtual ~piece_t() throw() {};

protected:

   //! Piece orientation code type (valid codes are 0,1,2,3)
   using orientation_t = int;

   //! Get piece orientation code
   virtual orientation_t get_orientation() const throw() = 0;

   //! Gets piece data
   virtual void get_shape_data(shapedata_t & data) const throw() = 0;

};


/* -------------------------------------------------------------------------- */

} // namespace tetris


/* -------------------------------------------------------------------------- */

#endif