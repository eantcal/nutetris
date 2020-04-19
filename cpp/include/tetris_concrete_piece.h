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

#ifndef _TETRIS_CONCRETE_PIECE_H_
#define _TETRIS_CONCRETE_PIECE_H_


/* -------------------------------------------------------------------------- */

#include "tetris_piece.h"

#include <cassert>


/* -------------------------------------------------------------------------- */

namespace tetris
{


/* -------------------------------------------------------------------------- */

//! @brief A general tetris piece, all the specific ones extend this class
class concrete_piece_t : public piece_t
{
private:
   concrete_piece_t() = delete;

protected:
   //! ctor
   explicit concrete_piece_t(col_t colidx) noexcept :
      _color_idx(colidx)
   {
   }


   //! Holds the piece color attribute 
   col_t _color_idx = 0;


   //! @brief Piece movement related data structure
   struct data_t
   {
      coord_t _pos_x = 0;
      coord_t _pos_y = 0;
      orientation_t _orientation = 0;
      coord_t _left_margin = 0;
      coord_t _right_margin = 0;
      coord_t _top_margin = 0;
      coord_t _bottom_margin = 0;

      data_t() = default;
      data_t(const data_t&) = default;
      data_t& operator=(const data_t&) = default;
   };


   //! Holds current piece position and orientation
   data_t _data;


   //! Holds previous piece position and orientation
   data_t _undo_data;


   //! Computes piece-grid related margins
   void compute_min_bounding_box() noexcept;


   //! Pre-computed piece orientations
   std::array< shapedata_t, ORIENTATIONS > _oriented_shapes;


   //! Returns a reference to piece data by using a given orientation index
   shapedata_t& operator[] (size_t idx) noexcept;


   //! Returns piece data by using a given orientation index
   const shapedata_t& operator[] (size_t idx) const noexcept;


   //! copy-ctor
   concrete_piece_t(const concrete_piece_t& other) noexcept;


   //! register piece into the factory
   static void register_piece(const piece_t & piece);


   //! returns the next piece index
   static size_t get_next_piece_index();

public:

   //! Gets color attribute reference at piece-grid coordinates col, row
   col_t & at(const coord_t& col, const coord_t& row) noexcept override;


   //! Gets color attribute at piece-grid coordinates col, row
   const col_t & at(const coord_t& col, const coord_t& row) const noexcept override;


   //! get color index
   virtual col_t get_color_idx() const noexcept final;
   

   //! move piece right by one game-grid cell
   void move_right() noexcept override;


   //! move piece left by one game-grid cell
   void move_left() noexcept override;


   //! move piece down by one game-grid cell
   void move_down() noexcept override;


   //! rotate piece clockwise
   void rotate_cw() noexcept override;


   //! rotate piece anticlockwise
   void rotate_acw() noexcept override;


   //! Updo last move/rotate operation
   void undo() noexcept override;


   //! Gets game-grid piece column offset
   coord_t get_col() const noexcept override;


   //! Gets game-grid piece row offset
   coord_t get_row() const noexcept override;


   //! Gets the count of empty piece-grid columns on the left side of piece shape
   coord_t get_left_margin() const noexcept override;


   //! Gets the count of empty piece-grid columns on the right side of piece shape
   coord_t get_right_margin() const noexcept override;


   //! Gets the count of empty piece-grid rows on the top side of piece shape
   coord_t get_top_margin() const noexcept override;


   //! Gets the count of empty piece-grid rows on the bottom side of piece shape
   coord_t get_bottom_margin() const noexcept override;

protected:
   //! Get orientation
   orientation_t get_orientation() const noexcept override;


   //! Get shape data 
   void get_shape_data(shapedata_t & data) const noexcept override;


   //! dtor
   virtual ~concrete_piece_t() noexcept
   {}


   //! Clones T object by using a copy of itself
   //! @return a unique_ptr to T object instance
   template <class T> 
   std::unique_ptr<T> _clone(const T & obj) const noexcept
   {
      auto p = new T(obj);
      assert(p);
      return std::unique_ptr<T>(p);
   }
};


} //namespace tetris

#endif
