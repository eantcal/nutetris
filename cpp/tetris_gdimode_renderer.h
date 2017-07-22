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


   gdimode_renderer_t() throw();

   //! Render the game scene
   void render(const game_data_t& game_data) throw() override;

private:
   void _draw_score(const game_data_t& game_data) throw();
   void _draw_grid(const grid_t& grid, int screenx, int screeny, int cellsize) throw();
   
   using rgb_color_t = int;

   std::vector< rgb_color_t > _colors;
   size_t _score = size_t(-1);
};


/* -------------------------------------------------------------------------- */

} // namespace tetris


/* -------------------------------------------------------------------------- */

#endif
