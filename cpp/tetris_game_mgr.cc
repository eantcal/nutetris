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

#include "tetris_game_mgr.h"
#include "tetris_textmode_renderer.h"


/* -------------------------------------------------------------------------- */

namespace tetris
{


/* -------------------------------------------------------------------------- */

game_mgr_t::game_mgr_t(
   coord_t cols, 
   coord_t rows,
   const interval_t& fullrow_blink_dalay_ms) 
   :
   _fullrow_blink_dalay_ms(fullrow_blink_dalay_ms),
   _pfactory(piece_factory_t::get_instance()),
   _input_mgr(input_mgr_t::get_instance()),
   _preview_canvas(piece_t::COLS, piece_t::ROWS),
   _game_grid(cols, rows),
   _game_renderer_data(this)
{
   _input_mgr.subscribe(this);
   ::srand((unsigned)::time(NULL));
}


/* -------------------------------------------------------------------------- */

void game_mgr_t::register_events() noexcept
{
   using ie_t = input_device_t::event_t;

   _event_map[ie_t::TIMERTICK] = input_t::MOVE_DOWN;
   _event_map[ie_t::DOWN] = input_t::ROTATE_CW;
   _event_map[ie_t::UP] = input_t::ROTATE_ACW;
   _event_map[ie_t::RIGHT] = input_t::MOVE_RIGHT;
   _event_map[ie_t::LEFT] = input_t::MOVE_LEFT;
   _event_map[ie_t::SPACE] = input_t::DROP_PIECE;
   _event_map[ie_t::ESCAPE] = input_t::EXIT;
}


/* -------------------------------------------------------------------------- */

void game_mgr_t::register_render() noexcept
{
   _renderer = std::unique_ptr< textmode_renderer_t >(new textmode_renderer_t);
}


/* -------------------------------------------------------------------------- */

//! Called by input manager this function convert an input device event
//! into game input command (skipping unused inputs)
void game_mgr_t::notify(const input_device_t::event_t & ev) noexcept
{
   auto ev_it = _event_map.find(ev);

   _input =
      ev_it == _event_map.end() ? input_t::NONE : ev_it->second;
}


/* -------------------------------------------------------------------------- */

piece_factory_t& game_mgr_t::piece_factory() const noexcept
{
   return _pfactory;
}


/* -------------------------------------------------------------------------- */

void game_mgr_t::render_scene() noexcept
{
   if (_renderer)
      _renderer->render(_game_renderer_data);
}


/* -------------------------------------------------------------------------- */

void game_mgr_t::undo_move_piece() noexcept
{
   _game_grid.current_piece().undo();
   _game_grid.place_piece();
}


/* -------------------------------------------------------------------------- */

void game_mgr_t::select_new_piece() noexcept
{
   _preview_canvas.give_piece(_game_grid);

   const auto catalog_size = piece_factory().get_piece_catalog_size();

   _preview_canvas.take_piece(
      piece_factory().make(rand() % catalog_size));

   _preview_canvas.clear();
   _preview_canvas.place_piece();
}


/* -------------------------------------------------------------------------- */

game_mgr_t::input_t game_mgr_t::handle_piece_movements() noexcept
{
   auto input = get_input();

   //Check if no other input is present then
   //if the piece is released create MOVE_DOWN event

   if (_piece_dropped)
   {
      input = input_t::MOVE_DOWN;

      process_input();
      auto pending_input = get_input();

      if (pending_input != input_t::NONE)
         input = pending_input;
   }

   switch (input)
   {
   case input_t::MOVE_RIGHT:
      _game_grid.current_piece().move_right();
      break;

   case input_t::MOVE_LEFT:
      _game_grid.current_piece().move_left();
      break;

   case input_t::MOVE_DOWN:
      _game_grid.current_piece().move_down();
      break;

   case input_t::ROTATE_CW:
      _game_grid.current_piece().rotate_cw();
      break;

   case input_t::ROTATE_ACW:
      _game_grid.current_piece().rotate_acw();
      break;

   case input_t::DROP_PIECE:
      drop_piece();
      break;
   
   case input_t::NONE:
   case input_t::EXIT:
   case input_t::PAUSE_GAME:
      break;
   }

   return input;
}


/* -------------------------------------------------------------------------- */

void game_mgr_t::play()
{
   // Input is processed using chain-of-responsibility pattern
   auto input = handle_piece_movements();

   switch (input)
   {
   case input_t::NONE:
      process_input();
      return;

   case input_t::EXIT:
      break;

   case input_t::PAUSE_GAME:
      break;

   default:
      break;
   }

   auto place_status = _game_grid.place_piece();
   grid_t::full_rows_t full_rows;

   switch (place_status)
   {
   case grid_t::place_st_t::NO_ROOM_FOR_PIECE:
      // Game over
      _game_st = game_state_t::GAMEOVER;
      break;

   case grid_t::place_st_t::TOUCH_DOWN:
      //Revert to last (valid) position
      undo_move_piece();

      //Get the full rows list
      get_full_rows(full_rows);

      if (! full_rows.empty())
      {
         int score_k = 1;

         for (auto row : full_rows)
         {
            fill_row(row, -1);
            score_k *= 2;
         }

         _score += score_k * FULL_ROW_SCORE_ODM;
      }

      render_scene();
      select_new_piece();

      std::this_thread::sleep_for( 
         std::chrono::milliseconds( _fullrow_blink_dalay_ms ) );

      remove_full_rows();
      render_scene();


      //Turn-off release mode
      drop_piece(false);

      return;

   default:
      if (place_status != grid_t::place_st_t::OK)
         undo_move_piece();

      render_scene();

      //Clean the piece from game area
      clean_piece();
      process_input();
   }
}


/* -------------------------------------------------------------------------- */

void game_mgr_t::setup() noexcept
{
   set_idle_intv(timer_input_device_t::interval_t(_falling_idle_intv));

   _game_grid.clear();
   _preview_canvas.clear();

   const auto catalog_size = piece_factory().get_piece_catalog_size();

   _game_grid.take_piece(piece_factory().make(rand() % catalog_size));

   _preview_canvas.take_piece(piece_factory().make(rand() % catalog_size));

   _preview_canvas.place_piece();

   drop_piece(false);

   _game_st = game_state_t::PLAYING;
}


/* -------------------------------------------------------------------------- */

void game_mgr_t::game_over()
{
   // Input is processed using chain-of-responsabilty pattern
   auto input = get_input();

   render_scene();

   if (input == input_t::EXIT)
      _game_st = game_state_t::BEGIN;

   process_input();
}


/* -------------------------------------------------------------------------- */


void game_mgr_t::run()
{
   switch (_game_st)
   {
   case game_state_t::BEGIN:
      setup();
      break;

   case game_state_t::PLAYING:
      play();
      break;

   case game_state_t::GAMEOVER:
      game_over();
      break;
   }
}


/* -------------------------------------------------------------------------- */

const grid_t & game_mgr_t::game_renderer_data_t::get_game_grid() const noexcept 
{
   return _this->_game_grid;
}


/* -------------------------------------------------------------------------- */

const grid_t & game_mgr_t::game_renderer_data_t::get_preview_canvas() const noexcept 
{
   return _this->_preview_canvas;
}


/* -------------------------------------------------------------------------- */

size_t game_mgr_t::game_renderer_data_t::get_game_score() const
{
   return _this->_score;
}


/* -------------------------------------------------------------------------- */

game_state_t game_mgr_t::game_renderer_data_t::get_game_st() const
{
   return _this->_game_st;
}


/* -------------------------------------------------------------------------- */



}

