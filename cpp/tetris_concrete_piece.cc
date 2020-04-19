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

#include "tetris_concrete_piece.h"
#include "tetris_piece_factory.h"


/* -------------------------------------------------------------------------- */

namespace tetris
{


/* -------------------------------------------------------------------------- */

concrete_piece_t::concrete_piece_t(const concrete_piece_t& other) noexcept
   :
   _data(other._data),
   _undo_data(other._undo_data),
   _color_idx(other._color_idx)
{
   _oriented_shapes = other._oriented_shapes;
}



/* -------------------------------------------------------------------------- */

piece_t::shapedata_t& concrete_piece_t::operator[] (size_t idx) noexcept
{
   assert(idx < _oriented_shapes.size());
   return _oriented_shapes[idx];
}


/* -------------------------------------------------------------------------- */

const piece_t::shapedata_t& concrete_piece_t::operator[] (size_t idx) const noexcept
{
   assert(idx < _oriented_shapes.size());
   return _oriented_shapes[idx];
}


/* -------------------------------------------------------------------------- */

piece_t::col_t concrete_piece_t::get_color_idx() const noexcept
{
   return _color_idx;
}


/* -------------------------------------------------------------------------- */

void concrete_piece_t::move_right() noexcept
{
   _undo_data = _data;
   ++_data._pos_x;
}


/* -------------------------------------------------------------------------- */

void concrete_piece_t::move_left() noexcept
{
   _undo_data = _data;
   --_data._pos_x;
}


/* -------------------------------------------------------------------------- */

void concrete_piece_t::move_down() noexcept
{
   _undo_data = _data;
   ++_data._pos_y;
}


/* -------------------------------------------------------------------------- */

void concrete_piece_t::rotate_acw() noexcept
{
   _undo_data = _data;
   ++_data._orientation;
   if (_data._orientation >= ORIENTATIONS)
      _data._orientation = 0;

   compute_min_bounding_box();
}


/* -------------------------------------------------------------------------- */

void concrete_piece_t::rotate_cw() noexcept
{
   _undo_data = _data;
   --_data._orientation;
   if (_data._orientation < 0)
      _data._orientation = ORIENTATIONS - 1;

   compute_min_bounding_box();
}


/* -------------------------------------------------------------------------- */

void concrete_piece_t::undo() noexcept
{
   _data = _undo_data;
}


/* -------------------------------------------------------------------------- */

piece_t::coord_t concrete_piece_t::get_col() const noexcept
{
   return _data._pos_x;
}


/* -------------------------------------------------------------------------- */

piece_t::coord_t concrete_piece_t::get_row() const noexcept
{
   return _data._pos_y;
}


/* -------------------------------------------------------------------------- */

piece_t::orientation_t concrete_piece_t::get_orientation() const noexcept
{
   return _data._orientation;
}


/* -------------------------------------------------------------------------- */

void concrete_piece_t::get_shape_data(shapedata_t & data) const noexcept
{
   data = _oriented_shapes[get_orientation()];
}


/* -------------------------------------------------------------------------- */

void concrete_piece_t::compute_min_bounding_box() noexcept
{
   if (_oriented_shapes.empty())
      return;

   auto & block = _oriented_shapes[get_orientation()];

   coord_t min_x = -1;
   coord_t max_x = -1;
   coord_t min_y = -1;
   coord_t max_y = -1;

   coord_t x = 0;
   coord_t y = 0;

   for (auto & row : block)
   {
      x = 0;

      for (auto & cell : row)
      {
         if (cell)
         {
            if (min_x == -1 || x < min_x )
               min_x = x;

            if (min_y == -1 || y < min_y )
               min_y = y;

            if (max_x == -1 || x > max_x)
               max_x = x;

            if (max_y == -1 || y > max_y)
               max_y = y;
         }

         ++x;
      }

      ++y;
   }

   _data._left_margin = min_x;
   _data._right_margin = piece_t::COLS - max_x - 1;
   _data._top_margin = min_y;
   _data._bottom_margin = piece_t::ROWS - max_y - 1;
}


/* -------------------------------------------------------------------------- */

piece_t::coord_t concrete_piece_t::get_left_margin() const noexcept
{
   return _data._left_margin;
}


/* -------------------------------------------------------------------------- */

piece_t::coord_t concrete_piece_t::get_right_margin() const noexcept
{
   return _data._right_margin;
}


/* -------------------------------------------------------------------------- */

piece_t::coord_t concrete_piece_t::get_top_margin() const noexcept
{
   return _data._top_margin;
}


/* -------------------------------------------------------------------------- */

piece_t::coord_t concrete_piece_t::get_bottom_margin() const noexcept
{
   return _data._bottom_margin;
}


/* -------------------------------------------------------------------------- */

piece_t::col_t & concrete_piece_t::at(const coord_t& col, const coord_t& row) noexcept
{
   assert(col >= 0 && col < piece_t::COLS);
   assert(row >= 0 && row < piece_t::ROWS);

   auto & block_data = _oriented_shapes[get_orientation()];

   auto & row_data = block_data[row];
   return row_data[col];
}


/* -------------------------------------------------------------------------- */

const piece_t::col_t & concrete_piece_t::at(const coord_t& col, const coord_t& row) const noexcept
{
   assert(col >= 0 && col < piece_t::COLS);
   assert(row >= 0 && row < piece_t::ROWS);

   const auto & block_data = _oriented_shapes[get_orientation()];
   const auto & row_data = block_data[row];

   return row_data[col];
}


/* -------------------------------------------------------------------------- */

//! register piece into the factory
void concrete_piece_t::register_piece(const piece_t & piece)
{
   piece_factory_t::get_instance().add_catalog(piece);
}


/* -------------------------------------------------------------------------- */

//! register piece into the factory
size_t concrete_piece_t::get_next_piece_index()
{
   return piece_factory_t::get_instance().get_piece_catalog_size() + 1;
}


/* -------------------------------------------------------------------------- */

} // namespace tetris
