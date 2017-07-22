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

#include "tetris_concrete_piece.h"


/* -------------------------------------------------------------------------- */

namespace tetris
{


/* -------------------------------------------------------------------------- */

//! The "S" piece of the tetris game
class piece_S_t : public concrete_piece_t
{
public:
   piece_S_t(col_t c = get_next_piece_index()) : concrete_piece_t(c)
   {
      assert(c > 0);

      {
         const row_t r1 = { 0, 0, 0, 0 };
         const row_t r2 = { 0, 0, c, c };
         const row_t r3 = { 0, c, c, 0 };
         const row_t r4 = { 0, 0, 0, 0 };

         const shapedata_t data = { r1, r2, r3, r4 };

         (*this)[0] = data;
         (*this)[2] = data;
      }

      {
         const row_t r1 = { 0, 0, c, 0 };
         const row_t r2 = { 0, 0, c, c };
         const row_t r3 = { 0, 0, 0, c };
         const row_t r4 = { 0, 0, 0, 0 };

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

static piece_S_t _S_piece_instance;


/* -------------------------------------------------------------------------- */

} // namespace tetris