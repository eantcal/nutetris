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

#include "tetris_gdimode_renderer.h"
#include "nu_gui.h"

#include <array>
#include <memory>


/* -------------------------------------------------------------------------- */

namespace tetris
{

/* -------------------------------------------------------------------------- */

namespace color
{
static const int BLACK = _nu_rgb(0, 0, 0);
static const int RED = _nu_rgb(0xff, 0, 0);
static const int GREEN = _nu_rgb(0, 0xff, 0);
static const int YELLOW2 = _nu_rgb(0x80, 0x80, 0);
static const int BLUE = _nu_rgb(0, 0, 0xff);
static const int CIANO = _nu_rgb(0, 0xff, 0xff);
static const int YELLOW = _nu_rgb(0xff, 0xff, 0);
static const int RED2 = _nu_rgb(0x80, 0, 0);
static const int GREEN2 = _nu_rgb(0, 0x80, 0);
static const int BLUE2 = _nu_rgb(0, 0, 0x80);
static const int CIANO2 = _nu_rgb(0, 0x80, 0x80);
static const int WHITE = _nu_rgb(0xff, 0xff, 0xff);
static const int GREY = _nu_rgb(0x80, 0x80, 0x80);
static const int GREY2 = _nu_rgb(0x40, 0x40, 0x40);
};


/* -------------------------------------------------------------------------- */

gdimode_renderer_t::gdimode_renderer_t() noexcept
{
   _colors = 
   {
      color::BLACK,
      color::RED,
      color::GREEN,
      color::YELLOW,
      color::BLUE,
      color::CIANO,
      color::RED2,
      color::GREEN2,
      color::YELLOW2,
      color::BLUE2,
      color::CIANO2,
      color::GREY,
      color::GREY2,
      color::WHITE
   };
}

   
   
/* -------------------------------------------------------------------------- */

void gdimode_renderer_t::render(const game_data_t& game_data) noexcept
{
   auto state = game_data.get_game_st();

   auto & game_grid = game_data.get_game_grid();
   auto & gui = nu::gui_t::get_instance();

   const auto dx = CELL_PIXEL_SIZE * game_grid.get_cols_count();
   const auto dy = CELL_PIXEL_SIZE * game_grid.get_rows_count();
   const auto bs = 1;

   switch(state) 
   {
   case game_state_t::BEGIN:
      break;

   case game_state_t::PLAYING:

      gui.rect( GRIDX, GRIDY, dx+2*+bs, dy+2*+bs, 1, color::WHITE, false);

      _draw_score(game_data);
      
      _draw_grid(
         game_data.get_preview_canvas(), 
         CANVAS_X+bs, 
         CANVAS_Y+bs, 
         CELL_PIXEL_SIZE+CELL_PIXEL_SIZE/4);

      gui.rect(
         CANVAS_X, CANVAS_Y+CANVAS_DY+CELL_PIXEL_SIZE/2, 
         CANVAS_DX+CELL_PIXEL_SIZE, 
         CELL_PIXEL_SIZE*2, 
         1, color::BLUE2, true);

      gui.textout(
         CANVAS_X+CELL_PIXEL_SIZE+CELL_PIXEL_SIZE/2, 
         CANVAS_Y + CANVAS_DY+CELL_PIXEL_SIZE, 
         "Next", color::WHITE);

      _draw_grid(
         game_data.get_game_grid(), 
         GRIDX+bs, 
         GRIDY+bs, 
         CELL_PIXEL_SIZE);

      break;

   case game_state_t::GAMEOVER:
      {
      auto & gui = nu::gui_t::get_instance();
      auto rc = game_data.get_game_grid().get_rows_count()/2;

      gui.ellipse( 
         SCOREX, 
         SCOREY+CELL_PIXEL_SIZE*rc, 
         SCOREDX, 
         SCOREDY, 1, 
         color::RED2, true);

      std::string s_score = "GAME OVER";

      for (int i = 0; i < 2; ++i)
         gui.textout( 
            SCOREX+SCORE_TXT_XOFF+CELL_PIXEL_SIZE+i, 
            SCOREY+CELL_PIXEL_SIZE*rc+SCORE_TXT_YOFF+i, 
            s_score, 
            color::YELLOW);
      break;

      }
   }

   
}


/* -------------------------------------------------------------------------- */

void _draw_grid() noexcept;

void gdimode_renderer_t::_draw_grid(
   const grid_t& grid, 
   int screenx, 
   int screeny, 
   int cellsize
   ) noexcept
{
   auto & gui = nu::gui_t::get_instance();

   auto zoom = [&](int x) { return x * cellsize; };

   for (int y = 0; y < grid.get_rows_count(); ++y)
   {
      for (int x = 0; x < grid.get_cols_count(); ++x)
      {
         const auto c = grid.at(x, y);

         int col = c < 0 ? color::WHITE : 
            (c ? _colors[c % _colors.size()] : 0);

         gui.rect(
            screenx + zoom(x), 
            screeny + zoom(y), 
            cellsize, 
            cellsize, 
            1, 
            col, true);

         if (c>0)
         {
            gui.rect(
               screenx + zoom(x), 
               screeny + zoom(y), 
               cellsize, 
               cellsize, 
               1, 
               color::GREY2, 
               false);
         }
      }

   }

}


/* -------------------------------------------------------------------------- */

void gdimode_renderer_t::_draw_score(const game_data_t& game_data) noexcept
{
   auto score = game_data.get_game_score();
   //if (score == _score)
   //   return;

   _score = score;

   auto & gui = nu::gui_t::get_instance();

   gui.ellipse( SCOREX, SCOREY, SCOREDX, SCOREDY, 1, color::YELLOW, true);

   std::string s_score = "nuTetris Score:" +  std::to_string(score);

   for (int i = 0; i < 2; ++i)
      gui.textout( 
         SCOREX+SCORE_TXT_XOFF+i, 
         SCOREY+SCORE_TXT_YOFF+i, 
         s_score, color::RED2);
   
}


/* -------------------------------------------------------------------------- */

} // namespace tetris


/* -------------------------------------------------------------------------- */

