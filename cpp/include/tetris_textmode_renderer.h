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

#ifndef _TETRIS_TEXTMODE_RENDERER_H_
#define _TETRIS_TEXTMODE_RENDERER_H_


/* -------------------------------------------------------------------------- */

#include "tetris_renderer.h"
#include "tetris_game_mgr.h"

#include <array>
#include <memory>


/* -------------------------------------------------------------------------- */

namespace tetris
{


/* -------------------------------------------------------------------------- */

//! @brief This class implements a text renderer of the game
class textmode_renderer_t : public renderer_t
{
public:
   //! Render the game scene
   void render(const game_data_t& game_data) throw() override;

private:
   void _draw_game_area(const game_data_t& game_data) throw();
   void _draw_piece_preview(const game_data_t& game_data) throw();
   void _draw_score(const game_data_t& game_data) throw();
   void _draw_grid(const grid_t& grid) throw();
};


/* -------------------------------------------------------------------------- */

} // namespace tetris


/* -------------------------------------------------------------------------- */

#endif