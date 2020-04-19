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
   virtual void register_render() noexcept
   {
      _renderer = std::unique_ptr< gdimode_renderer_t >(new gdimode_renderer_t);
   }
};


/* -------------------------------------------------------------------------- */

} // namespace tetris


/* -------------------------------------------------------------------------- */

#endif