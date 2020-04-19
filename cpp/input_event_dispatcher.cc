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

