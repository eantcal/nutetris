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

#include "tetris_input_mgr.h"


/* -------------------------------------------------------------------------- */

namespace tetris
{


/* -------------------------------------------------------------------------- */

timer_input_device_t& input_mgr_t::timerdev()
{
   if (!_timedev)
      _timedev.reset(new timer_input_device_t);

   return *_timedev;
}


/* -------------------------------------------------------------------------- */

input_device_t::event_t input_mgr_t::poll() throw()
{
   auto kbev = keybdev().poll();
   auto tmev = timerdev().poll();

   const auto none =
      input_device_t::event_t::NONE;

   if (kbev != none)
      return kbev;

   if (tmev != none)
      return tmev;

   return none;
}


/* -------------------------------------------------------------------------- */

input_mgr_t& input_mgr_t::get_instance()
{
   static input_mgr_t _instance;
   return _instance;
}


/* -------------------------------------------------------------------------- */

void input_mgr_t::run()
{
   const input_device_t::event_t none =
      input_device_t::event_t::NONE;

   input_device_t::event_t ev = none;

   //Notify any pending events
   do
   {
      ev = poll();

      if (ev != none)
         notify_all(ev);

   } while (ev != none);
}


/* -------------------------------------------------------------------------- */

} // namespace tetris


/* -------------------------------------------------------------------------- */
