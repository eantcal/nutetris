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

#ifndef _TETRIS_INPUT_MGR_H_
#define _TETRIS_INOUT_MGR_H_


/* -------------------------------------------------------------------------- */

#include "input_event_dispatcher.h"
#include "timer_input_device.h"
#include "keyboard_input_device.h"


/* -------------------------------------------------------------------------- */

namespace tetris
{

//! @brief Manages all the input devices used in the game
class input_mgr_t : public input_event_dispatcher_t
{
private:
   //! Keyboard device instance
   keyboard_input_device_t _keybdev;

   //! Timer-input device instance
   std::unique_ptr< timer_input_device_t >  _timedev;

   //! Returns keyboard device reference
   keyboard_input_device_t& keybdev()
   {
      return _keybdev;
   }

   //! Returns timer device reference
   timer_input_device_t& timerdev();

protected:

   //! Return any keyboard or timer event
   input_device_t::event_t poll() throw();


public:

   //! Returns the unique input manager instance
   static input_mgr_t& get_instance();


   //! This function updates manager status, it should be called
   //! periodically from client
   void run();
   

   //! Modifies the timer interval
   void change_timer_interval(const timer_input_device_t::interval_t& intv)
   {
      timerdev().change_interval(intv);
   }


};


/* -------------------------------------------------------------------------- */

} // namespace tetris


/* -------------------------------------------------------------------------- */

#endif
