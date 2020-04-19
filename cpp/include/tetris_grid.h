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

#ifndef _TETRIS_GRID_H_
#define _TETRIS_GRID_H_


/* -------------------------------------------------------------------------- */

#include <cassert>
#include <memory>
#include <string>
#include <vector>
#include <exception>
#include <array>
#include <set>

#include "tetris_piece_factory.h"


/* -------------------------------------------------------------------------- */

namespace tetris
{

/* -------------------------------------------------------------------------- */

//! @brief This is the backend model for the entire tetris grid and piece-preview 
//! canvas, which draws a piece based off of what the next piece will be.
//! It holds integer values to represent the color attribuites of each individual 
//! cell in the grid.
class grid_t
{

private:
   //! Merge operation type
   enum class merge_mode_t { PUT, REMOVE };

public:
   //! cell coordinate type
   using coord_t = piece_t::coord_t;

   //! list of full rows
   using full_rows_t = std::set < coord_t > ;

   //! @brief grid exception class
   struct exception_t : public std::exception
   {
      private:
         const std::string _pcause;

      public:
         exception_t(const char* err) noexcept : 
            _pcause(err) 
         {}

         const char* what() const noexcept override
         {
            return _pcause.c_str();
         }
   };

   //! ctor
   grid_t(const coord_t& columns, const coord_t& row);

   //! dtor
   virtual ~grid_t() {}

   //! Gets columns count
   virtual const coord_t get_cols_count() const noexcept final
   {
      return _cols;
   }

   //! Gets rows count
   virtual const coord_t get_rows_count() const noexcept final
   {
      return _rows;
   }

   //! Gets a reference to the cell at coords x,y
   virtual piece_t::col_t & at(const coord_t & x, const coord_t & y);

   //! Gets a constant reference to the cell at coords x,y
   virtual const piece_t::col_t & at(const coord_t & x, const coord_t & y) const;

   //! Clear the grid content
   virtual void clear() noexcept;

   //! Select new piece
   virtual void take_piece(piece_t::handle_t piece) noexcept;

   //! Gives the selected piece to other grid
   virtual void give_piece(grid_t & grid) noexcept;

   //! Gets a list of full rows
   virtual void get_full_rows(full_rows_t & full_rows) const noexcept;

   //! Fills the cells of a whole row using a given color attribute
   virtual void fill_row(const coord_t & row_idx, const piece_t::col_t& attr) noexcept;

   //! Removes the completed rows, moving down the other cells
   virtual void remove_full_rows() noexcept;
   
   //! Place-piece operation result type
   enum class place_st_t
   {
      OK,
      CROSS_RIGHT_BOUNDARY,
      CROSS_LEFT_BOUNDARY,
      CROSS_TOP_BOUNDARY,
      NO_ROOM_FOR_PIECE,
      TOUCH_DOWN
   };


   //! Places current piece onto the grid. 
   place_st_t place_piece()
   {
      return merge_piece(merge_mode_t::PUT);
   }

   //! Remove piece from the grid
   void remove_piece()
   {
      merge_piece(merge_mode_t::REMOVE);
   }

   //! Gets a reference to the current piece
   piece_t & current_piece();


protected:
   //! Grid-row type
   using row_t = std::vector < piece_t::col_t > ;

   //! Grid-map type
   using grid_map_t = std::vector < row_t > ;

   grid_map_t _grid_map;

   //! Current piece object handle
   piece_t::handle_t _current_piece;

   //! Checks if piece crosses the grid boundaries 
   virtual place_st_t check_boundaries() const;
   
   //! Merges the piece cells in the grid
   virtual place_st_t merge_piece(merge_mode_t mode);


private:
   //! Grid rows count
   coord_t _rows = 0;

   //! Grid columns count
   coord_t _cols = 0;

   //! Checks X,Y coordinates validity
   void _check_xy_range(const coord_t& x, const coord_t& y) const;

   //! Gets a color attribute reference to given cell coordinates
   piece_t::col_t & _cell_at(
      grid_map_t & map_data,
      const coord_t & x, const coord_t & y);

   //! Returns true if a row is full
   //! If empty flag is true, then it returns true if the row is empty
   //! (any cell in the row has a null color attribute)
   bool _is_completed_row(const coord_t& row_idx, bool empty = false) const;

   //! Returns true if the row is empty. @see _is_completed_row
   bool _is_empty_row(const coord_t& row_idx) const
   {
      return _is_completed_row(row_idx, true);
   }
};


/* -------------------------------------------------------------------------- */

} // namespace tetris


#endif // _TETRIS_BOARD_H_
