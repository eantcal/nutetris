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

#ifndef _INPUT_EVENT_DISPATCHER_H_
#define _INPUT_EVENT_DISPATCHER_H_

/* -------------------------------------------------------------------------- */

#include "input_event_listener.h"

#include <set>


/* -------------------------------------------------------------------------- */

//! @brief This helper class manages event listener subscriptions and event 
//! dispatching for input_event_listener_t objects.
class input_event_dispatcher_t
{
private:
   std::set< input_event_listener_t* > _listeners;

   //! deleted ctors
   input_event_dispatcher_t(const input_event_dispatcher_t&) = delete;
   input_event_dispatcher_t& operator=(const input_event_dispatcher_t&) = delete;

protected:
   //! ctor
   input_event_dispatcher_t() throw()
   {}

   //! dtor
   virtual ~input_event_dispatcher_t() throw();
   
   //! Notify all the listeners
   virtual void notify_all(const input_device_t::event_t & ev) throw();

public:

   //! Register a new listener
   virtual void subscribe(input_event_listener_t* listener) throw();

   //! Unregister an existent listener
   virtual void unsubscribe(input_event_listener_t* listener) throw();
};


/* -------------------------------------------------------------------------- */

#endif 