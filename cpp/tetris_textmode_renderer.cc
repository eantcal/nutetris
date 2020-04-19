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

#include "tetris_textmode_renderer.h"

#include <array>
#include <memory>
#include <stdlib.h>

#if !defined(__MINGW32__) && !defined(_WIN32)
#define CLRSCREEN "clear"
#else
#define CLRSCREEN "cls"
#endif

/* -------------------------------------------------------------------------- */

namespace tetris
{


/* -------------------------------------------------------------------------- */

void textmode_renderer_t::render(const game_data_t& game_data) noexcept
{
   auto state = game_data.get_game_st();

   switch(state) 
   {
      case game_state_t::BEGIN:
         break;

      case game_state_t::PLAYING:
         {
            int res = ::system(CLRSCREEN);
            (void) res;
            _draw_score(game_data);
            std::cout << "Next:" << std::endl;
            _draw_piece_preview(game_data);
            std::cout << std::endl;
            _draw_game_area(game_data);
         }
         break;

      case game_state_t::GAMEOVER:
         {
            int res = ::system(CLRSCREEN);
            (void) res;
            std::cout << "Game Over\n";
            std::cout << "Press ESC to restart\n";
         }
         break;
   }

   
}


/* -------------------------------------------------------------------------- */

void textmode_renderer_t::_draw_game_area(const game_data_t& game_data) noexcept
{
   const auto & game_area = game_data.get_game_grid();
   _draw_grid(game_area);
}


/* -------------------------------------------------------------------------- */

void textmode_renderer_t::_draw_grid(const grid_t& grid) noexcept
{
   std::ostream& os = std::cout;

   for (int x = 0; x < grid.get_cols_count() + 2; ++x)
      os << "-";

   os << std::endl;

   for (int y = 0; y < grid.get_rows_count(); ++y)
   {
      os << "|";
      for (int x = 0; x < grid.get_cols_count(); ++x)
      {
         const auto c = grid.at(x, y);
         std::string d = c < 0 ? "#" : std::to_string(c);

         os << (c ? d : " ");
      }

      os << "|" << std::endl;
   }

   for (int x = 0; x < grid.get_cols_count() + 2; ++x)
      os << "-";
}


/* -------------------------------------------------------------------------- */

void textmode_renderer_t::_draw_piece_preview(const game_data_t& game_data) noexcept
{
   const auto & preview_area = game_data.get_preview_canvas();
   _draw_grid(preview_area);
}


/* -------------------------------------------------------------------------- */

void textmode_renderer_t::_draw_score(const game_data_t& game_data) noexcept
{
   std::cout << "Score:" << game_data.get_game_score() << std::endl;
}


/* -------------------------------------------------------------------------- */

} // namespace tetris


/* -------------------------------------------------------------------------- */

