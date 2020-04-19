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

#ifndef _INPUT_EVENT_LISTENER_H_
#define _INPUT_EVENT_LISTENER_H_

/* -------------------------------------------------------------------------- */

#include "input_device.h"


/* -------------------------------------------------------------------------- */

//! @brief Represents a generic interface for input listeners
class input_event_listener_t
{
   friend class input_event_dispatcher_t;

public:
   //! dtor
   virtual ~input_event_listener_t() {};

   //! Called to notify the implementation that an event has occurred.
   virtual void notify(const input_device_t::event_t & ev) noexcept = 0;
};


/* -------------------------------------------------------------------------- */

#endif 