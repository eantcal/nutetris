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

#include "input_event_dispatcher.h"

#include <set>
#include <cassert>


/* -------------------------------------------------------------------------- */

input_event_dispatcher_t::~input_event_dispatcher_t() throw()
{
}


/* -------------------------------------------------------------------------- */

void input_event_dispatcher_t::notify_all(const input_device_t::event_t & ev) throw()
{
   for (auto listener : _listeners)
      listener->notify(ev);
}


/* -------------------------------------------------------------------------- */

void input_event_dispatcher_t::subscribe(input_event_listener_t* listener) throw()
{
   assert(listener);
   _listeners.insert(listener);
}


/* -------------------------------------------------------------------------- */

void input_event_dispatcher_t::unsubscribe(input_event_listener_t* listener) throw()
{
   assert(listener);
   _listeners.erase(listener);
}


/* -------------------------------------------------------------------------- */

