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

#ifndef _TETRIS_RENDERER_H_
#define _TETRIS_RENDERER_H_


/* -------------------------------------------------------------------------- */

#include "tetris_piece.h"
#include "tetris_grid.h"
#include "tetris_game_state.h"

#include <array>
#include <memory>


/* -------------------------------------------------------------------------- */

namespace tetris
{

/* -------------------------------------------------------------------------- */

//! @brief This interface represents the rendering logic of the game
class renderer_t
{
public:

   //! @brief This interface represents data required by renderer to
   //! draw game objects
   struct game_data_t
   {
      using coord_t = piece_t::coord_t;
      using col_t = piece_t::col_t;

      //! Gets a reference to the grid object
      virtual const grid_t & get_game_grid() const noexcept = 0;

      //! Gets a reference to the preview canvas object
      virtual const grid_t & get_preview_canvas() const noexcept = 0;

      //! Gets the score 
      virtual size_t get_game_score() const = 0;

      //! Gets the game state
      virtual game_state_t get_game_st() const = 0;
   
      //! dtor
      virtual ~game_data_t() noexcept {};
   };

   //! Renders the scene
   virtual void render(const game_data_t& game_data) noexcept = 0;

   //! dtor
   virtual ~renderer_t() noexcept {};
};


/* -------------------------------------------------------------------------- */

} // namespace tetris


/* -------------------------------------------------------------------------- */

#endif