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

#ifndef _TETRIS_GDIMODE_RENDERER_H_
#define _TETRIS_GDIMODE_RENDERER_H_


/* -------------------------------------------------------------------------- */

#include "tetris_config.h"
#include "tetris_renderer.h"
#include "tetris_game_mgr.h"

#include <array>
#include <memory>


/* -------------------------------------------------------------------------- */

namespace tetris
{


/* -------------------------------------------------------------------------- */

//! @brief This class implements a text renderer of the game
class gdimode_renderer_t : public renderer_t
{
public:
   enum { 
      CELL_PIXEL_SIZE = NU_TETRIS_PIECE_SIZE,
      GRIDX = NU_TETRIS_GRIDX, 
      GRIDY = NU_TETRIS_GRIDY,
      SCOREX = NU_TETRIS_SCOREX, 
      SCOREY = NU_TETRIS_SCOREY, 
      SCOREDX = NU_TETRIS_SCOREDX, 
      SCOREDY = NU_TETRIS_SCOREDY,
      SCORE_TXT_XOFF = NU_TETRIS_SCORE_TXT_XOFF, 
      SCORE_TXT_YOFF = NU_TETRIS_SCORE_TXT_YOFF,
      CANVAS_X = NU_TETRIS_CANVAS_X, 
      CANVAS_Y = NU_TETRIS_CANVAS_Y, 
      CANVAS_DX = CELL_PIXEL_SIZE*piece_t::COLS, 
      CANVAS_DY = CELL_PIXEL_SIZE*piece_t::ROWS 
   };


   gdimode_renderer_t() noexcept;

   //! Render the game scene
   void render(const game_data_t& game_data) noexcept override;

private:
   void _draw_score(const game_data_t& game_data) noexcept;
   void _draw_grid(const grid_t& grid, int screenx, int screeny, int cellsize) noexcept;
   
   using rgb_color_t = int;

   std::vector< rgb_color_t > _colors;
   size_t _score = size_t(-1);
};


/* -------------------------------------------------------------------------- */

} // namespace tetris


/* -------------------------------------------------------------------------- */

#endif
