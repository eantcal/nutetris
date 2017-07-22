/*
*  This file is part of nuTetris
*
*  nuTetris is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  nuTetris is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with nuTetris; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  US
*
*  Author: <antonino.calderone@ericsson.com>, <acaldmail@gmail.com>
*
*/


/* -------------------------------------------------------------------------- */

#include "tetris_grid.h"

#include <iostream>
#include <list>


/* -------------------------------------------------------------------------- */

namespace tetris
{

/* -------------------------------------------------------------------------- */

grid_t::grid_t(const coord_t& columns, const coord_t& rows)
   :
   _rows(rows),
   _cols(columns)
{
   if (columns < piece_t::COLS || rows < piece_t::ROWS)
      throw exception_t("grid_t::ctor bad parameters");

   // Build up the grid cells
   _grid_map.resize(rows);

   for (auto & row : _grid_map)
      row.resize(columns);
}


/* -------------------------------------------------------------------------- */

piece_t::col_t & grid_t::_cell_at(
   grid_map_t & map_data,
   const coord_t & x,
   const coord_t & y)
{
   _check_xy_range(x, y);

   auto & row = map_data[y];
   return row[x];
}


/* -------------------------------------------------------------------------- */

piece_t::col_t & grid_t::at(const coord_t & col, const coord_t & row)
{
   return _cell_at(_grid_map, col, row);
}


/* -------------------------------------------------------------------------- */

const piece_t::col_t & grid_t::at(const coord_t & col, const coord_t & row) const
{
   _check_xy_range(col, row);

   const auto & rowcells = _grid_map[row];

   return rowcells[col];
}


/* -------------------------------------------------------------------------- */

void grid_t::clear() throw()
{
   for (auto & row : _grid_map)
      for (auto & i : row)
         i = 0;
}


/* -------------------------------------------------------------------------- */

bool grid_t::_is_completed_row(const coord_t& row_idx, bool empty) const
{
   bool completed = true;

   auto cols = get_cols_count();

   for (decltype(cols) i = 0; i < cols; ++i)
   {
      const auto c = at(i, row_idx);

      if (!c == !empty)
      {
         completed = false;
         break;
      }
   }

   return completed;
}


/* -------------------------------------------------------------------------- */

void grid_t::get_full_rows(full_rows_t & full_rows) const throw()
{
   full_rows.clear();

   auto rows = get_rows_count();

   for (decltype(rows) i = 0; i < rows; ++i)
   {
      if (_is_completed_row(i))
         full_rows.insert(i);
   }
}


/* -------------------------------------------------------------------------- */

void grid_t::fill_row(const coord_t & row_idx, const piece_t::col_t& attr) throw()
{
   auto cols = get_cols_count();

   for (decltype(cols) i = 0; i < cols; ++i)
      at(i, row_idx) = attr;
}


/* -------------------------------------------------------------------------- */

void grid_t::remove_full_rows() throw()
{
   std::list< row_t > nonfullrows;

   auto rows = get_rows_count();

   const auto cols = get_cols_count();
   
   bool completed_rows_found = false;

   for (coord_t i = rows-1; i >= 0; --i)
   {
      if (_is_empty_row(i))
      {
         if (completed_rows_found)
            break;
         else
            return; // nothing todo
      }

      if (!_is_completed_row(i))
         nonfullrows.push_back( _grid_map[i] );
      else
         completed_rows_found = true;
   }

   if (completed_rows_found)
   {
      _grid_map.clear();
      _grid_map.resize(rows);

      coord_t i = rows-1;

      for ( auto & row : nonfullrows)
         _grid_map[i--] = row;

      row_t empty_row(cols);

      //Fill the left empty rows
      for (; i >= 0; --i)
         _grid_map[i] = empty_row;
   }
}


/* -------------------------------------------------------------------------- */
   
void grid_t::take_piece( piece_t::handle_t piece ) throw()
{
   _current_piece = std::move(piece);
}


/* -------------------------------------------------------------------------- */

void grid_t::give_piece(grid_t & grid) throw()
{
   grid._current_piece = std::move(_current_piece);
}


/* -------------------------------------------------------------------------- */

grid_t::place_st_t grid_t::check_boundaries() const
{
   if (!_current_piece)
      throw(exception_t("grid_t: no piece selected"));

   auto & piece = *_current_piece;

   const coord_t piece_x = piece.get_col();
   const coord_t piece_y = piece.get_row();

   //Check if piece crosses the grid borders
   if (piece_x + piece.get_left_margin() < 0)
      return place_st_t::CROSS_LEFT_BOUNDARY;

   if (piece_y + piece.get_top_margin() <= 0)
      return place_st_t::CROSS_TOP_BOUNDARY;

   if ((piece_x + piece_t::COLS - piece.get_right_margin()) > get_cols_count())
      return place_st_t::CROSS_RIGHT_BOUNDARY;

   if ((piece_y + piece_t::ROWS - piece.get_bottom_margin()) > get_rows_count())
      return place_st_t::TOUCH_DOWN;

   return place_st_t::OK;
}


/* -------------------------------------------------------------------------- */

grid_t::place_st_t grid_t::merge_piece(merge_mode_t mode)
{
   auto st = check_boundaries();

   if (st != place_st_t::OK)
      return st;
   
   auto & piece = *_current_piece;

   const coord_t piece_x = piece.get_col();
   const coord_t piece_y = piece.get_row();

   //Copy cells data onto map_data in order to preserve it before merging
   auto draft_map = _grid_map;

   for (coord_t y = 0; y < piece_t::ROWS; ++y)
   {
      for (coord_t x = 0; x < piece_t::COLS; ++x)
      {
         auto grid_col = piece_x + x;
         auto grid_row = piece_y + y;

         if (grid_col < 0 || grid_col >= get_cols_count() ||
            grid_row < 0 || grid_row >= get_rows_count())
         {
            continue;
         }

         auto & grid_cell = _cell_at(draft_map, grid_col, grid_row);
         auto piece_cell = piece.at(x, y);

         if (mode == merge_mode_t::PUT)
         {
            //In case of cell conflict, return TOUCH_DOWN or NO_ROOM_FOR_PIECE
            //depending on top margin value
            //(cells data modification will be not committed)
            if (grid_cell && piece_cell)
            {
               return (piece_y-piece.get_top_margin()) < 1 ? 
                  place_st_t::NO_ROOM_FOR_PIECE : 
                  place_st_t::TOUCH_DOWN;
            }

            //Copy piece (or delete) cell content into the draft data map
            if (piece_cell) grid_cell = piece_cell;
         }
         else
         {
            //Copy piece (or delete) cell content into the draft data map
            if (piece_cell) grid_cell = 0;
         }
      }
   }

   // commit changes to the map data
   _grid_map = draft_map; 

   return place_st_t::OK;
}


/* -------------------------------------------------------------------------- */

piece_t & grid_t::current_piece()
{
   if (!_current_piece)
      throw(exception_t(
      "grid_t: cannot retrieve nonexistent piece"));

   return *_current_piece;
}


/* -------------------------------------------------------------------------- */

void grid_t::_check_xy_range(const coord_t& x, const coord_t& y) const
{
   auto _check_range =
      [](coord_t min, coord_t max, coord_t val, const char* msg)
   { if (val < min || val >= max) throw(msg); };

   _check_range(0, get_cols_count(),
      x, "grid_t ctor: invalid x parameter");

   _check_range(0, get_rows_count(),
      y, "grid_t ctor: invalid rows parameter");
}


/* -------------------------------------------------------------------------- */

}

