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

#include "tetris_piece_factory.h"


/* -------------------------------------------------------------------------- */

namespace tetris
{

/* -------------------------------------------------------------------------- */

piece_factory_t& piece_factory_t::get_instance()
{
   // unique object instance (created the first time
   // this function is invoked)
   static piece_factory_t _instance;

   // returns the unique instance of this object
   return _instance;
}


/* -------------------------------------------------------------------------- */

piece_t::handle_t piece_factory_t::make(size_t piece_idx)
{
   if (piece_idx < 0 || piece_idx > _piece_catalog.size())
      throw exception_t("index out of range");

   // Clones the selected piece from the catalog
   return piece_t::handle_t(_piece_catalog[piece_idx]->clone());
}


/* -------------------------------------------------------------------------- */

} // namespace tetris