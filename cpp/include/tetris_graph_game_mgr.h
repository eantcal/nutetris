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

#ifndef _TETRIS_GRAPH_GAME_MGR_H_
#define _TETRIS_GRAPH_GAME_MGR_H_

#include "tetris_gdimode_renderer.h"

namespace tetris
{

/* -------------------------------------------------------------------------- */

//! @brief Extentends game_mgr_t in order to register a GDI-based renderer
class graph_game_mgr_t : public game_mgr_t
{
public:
   virtual void register_render() throw()
   {
      _renderer = std::unique_ptr< gdimode_renderer_t >(new gdimode_renderer_t);
   }
};


/* -------------------------------------------------------------------------- */

} // namespace tetris


/* -------------------------------------------------------------------------- */

#endif