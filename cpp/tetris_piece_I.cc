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


/* -------------------------------------------------------------------------- */

namespace tetris
{

/* -------------------------------------------------------------------------- */

//! The "I" piece of the tetris game
class piece_I_t : public concrete_piece_t
{
public:
   piece_I_t(col_t c = get_next_piece_index()) : concrete_piece_t(c)
   {
      assert(c > 0);

      {
         const row_t r1 = { 0, 0, 0, 0 };
         const row_t r2 = { c, c, c, c };
         const row_t r3 = { 0, 0, 0, 0 };
         const row_t r4 = { 0, 0, 0, 0 };

         const shapedata_t data = { r1, r2, r3, r4 };

         (*this)[0] = data;
         (*this)[2] = data;
      }

      {
         const row_t r1 = { 0, 0, c, 0 };
         const row_t r2 = { 0, 0, c, 0 };
         const row_t r3 = { 0, 0, c, 0 };
         const row_t r4 = { 0, 0, c, 0 };

         const shapedata_t data = { r1, r2, r3, r4 };

         (*this)[1] = data;
         (*this)[3] = data;
      }

      compute_min_bounding_box();
      register_piece(*this);

   }

   piece_t::handle_t clone() const throw() override
   {
      return _clone(*this);
   }

};


/* -------------------------------------------------------------------------- */

static piece_I_t _instance;


/* -------------------------------------------------------------------------- */

} // namespace tetris