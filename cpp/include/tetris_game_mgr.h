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

#ifndef _TETRIS_GAME_MGR_H_
#define _TETRIS_GAME_MGR_H_

#include <vector>
#include <array>
#include <cassert>
#include <memory>
#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <map>
#include <set>
#include <string>

#include "tetris_config.h"
#include "tetris_piece_factory.h"
#include "tetris_input_mgr.h"
#include "tetris_grid.h"
#include "tetris_renderer.h"
#include "tetris_game_state.h"


/* -------------------------------------------------------------------------- */

namespace tetris
{

//! @brief Game manager class is in charge to initialize other game objects 
//! (grids, piece factory, render, ...)
//! and handle the gameplay
class game_mgr_t : public input_event_listener_t
{
public:

   //! Game input events
   enum class input_t
   {
      NONE,
      MOVE_RIGHT,
      MOVE_LEFT,
      MOVE_DOWN,
      ROTATE_CW,
      ROTATE_ACW,
      DROP_PIECE,
      EXIT,
      PAUSE_GAME
   };


   //! Map used to convert device input events into game events
   using event_map_t = 
      std::map < input_device_t::event_t, input_t > ;


private:
   //! Default Constants Parameters
   enum { 
      DEF_COLS = NU_TETRIS_DEF_COLS,                    //!< Default game area columns
      DEF_ROWS = NU_TETRIS_DEF_ROWS,                    //!< Default game area rows
      FALLING_IDLE_INTV = NU_TETRIS_FALLING_IDLE_INTV,  //!< Initial falling idle timeout (ms)
      FULL_ROW_BLNK_DL = NU_TETRIS_FULL_ROW_BLNK_DL,    //!< 'Full-row blink' delay
      FULL_ROW_SCORE_ODM = NU_TETRIS_FULL_ROW_SCORE_ODM //!< Score order of magnitude
   }; 
   

protected:
   using coord_t = grid_t::coord_t;
   using col_t = piece_t::col_t;
   using full_rows_t = grid_t::full_rows_t;
   using interval_t = timer_input_device_t::interval_t;


   // ctors
   game_mgr_t(
      coord_t def_cols = DEF_COLS, 
      coord_t def_rows = DEF_ROWS,
      const interval_t& fullrow_blink_dalay_ms = 
         interval_t(FULL_ROW_BLNK_DL));


   game_mgr_t(game_mgr_t&) = delete;
   game_mgr_t& operator=(game_mgr_t&) = delete;


   //! dtor
   virtual ~game_mgr_t() {}


   //! Overriding this method you may register a different 
   //! event map (it implements template method pattern)
   virtual void register_events() throw();
   

   //! Overriding this method you may register a different 
   //! render (it implements template method pattern)
   virtual void register_render() throw();


   //! Called by input manager this function convert an input device event
   //! into game input command (skipping unused inputs)
   void notify(const input_device_t::event_t & ev) throw() override;


   //! Returns the piece factory reference
   virtual piece_factory_t& piece_factory() const throw();


   //! Redraws the scene
   void render_scene() throw();


   //! Reverts to previous piece position / orientation
   void undo_move_piece() throw();


   //! Takes a new piece from catalog
   void select_new_piece() throw();


   //! Acknowledges last input event
   void ack_input_event() throw()
   {
      _input = input_t::NONE;
   }


   //! Remove the piece from the game area
   void clean_piece()
   {
      _game_grid.remove_piece();
   }


   //! Process any new input event
   void process_input() throw()
   {
      _input_mgr.run();
   }


   //! Returns and acknowledges last input event
   input_t get_input() throw()
   {
      auto input = _input;
      _input = input_t::NONE;
      return input;
   }


   //! Set / reset _piece_dropped state
   //! which causes a series of move down event
   //! in order to speed up piece falling
   void drop_piece( bool st = true ) throw()
   {
      _piece_dropped = st;
      if (! st) ack_input_event();
   }


   //! Gets a list of completed rows
   void get_full_rows(full_rows_t & full_rows) const throw()
   {
      _game_grid.get_full_rows(full_rows);
   }


   //! Fills the cells of a whole row using a given color attribute
   void fill_row(const coord_t & row_idx, const col_t& attr) throw()
   {
      _game_grid.fill_row(row_idx, attr);
   }
   

   //! Remove the completed rows, moving down the other cells
   void remove_full_rows() throw()
   {
      _game_grid.remove_full_rows();
   }
   

   //! Processes an input and handles it
   //! if it is related to piece movement
   input_t handle_piece_movements() throw();


   //! Called on PLAYING state
   virtual void play();


   //! Called on BEING state
   virtual void setup() throw();


   //! Called on GAMEOVER state
   virtual void game_over();


   //! Updates falling timer interval 
   void set_idle_intv(const interval_t& intv) throw()
   {
      _input_mgr.change_timer_interval(intv);
   }


public:
   //! Creates or gets the unique instance of 
   //! game_mgr_t-like object
   template< typename T, typename ...Args > 
   friend T& make_game_mgr_instance(Args&&... args);


   //! Runs the game
   virtual void run();


private:
   interval_t _fullrow_blink_dalay_ms;

   //! Reference to piece factory class
   piece_factory_t & _pfactory;

   //! Reference to input manager
   input_mgr_t & _input_mgr;

   //! Preview canvas
   grid_t _preview_canvas;

   //! Game grid instance
   grid_t _game_grid;

   //! Last input event
   input_t _input = input_t::NONE;

   //! Device event to input event lookup table
   event_map_t _event_map;

   //! Falling idle timeout (determines the speed of the game)
   timer_input_device_t::interval_t _falling_idle_intv = 
      timer_input_device_t::interval_t(FALLING_IDLE_INTV);

   //! Set to speed up falling of dropped piece 
   bool _piece_dropped = false;

   //! Holds current game status
   game_state_t _game_st = game_state_t::BEGIN;

protected:
   //! Pointer to the render
   std::unique_ptr< renderer_t > _renderer;

private:
   //! Game score
   unsigned long _score = 0;

   //! Data used for rendering
   friend struct game_render_data_t;

   //! Facade object used by render to dynamically get 
   //! data for game rendering
   struct game_renderer_data_t : public renderer_t::game_data_t
   {
      const game_mgr_t* _this = nullptr;
      game_renderer_data_t(const game_mgr_t* ptr) : _this(ptr) {}
      const grid_t & get_game_grid() const throw() override;
      const grid_t & get_preview_canvas() const throw() override;
      size_t get_game_score() const override;
      game_state_t get_game_st() const override;
   }
   _game_renderer_data;

};


/* -------------------------------------------------------------------------- */

//! Generic helper function used to create and intialize game_mgr-like objects
template< typename T, typename ...Args > 
T& make_game_mgr_instance(Args&&... args)
{
   static T* _instance = nullptr;

   if (!_instance)
   {
      _instance = new T(std::forward<Args>(args)...);
      _instance->register_events();
      _instance->register_render();
   }

   return *_instance;
}


/* -------------------------------------------------------------------------- */

}

#endif 
