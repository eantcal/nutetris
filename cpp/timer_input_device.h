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

#ifndef _TIMER_INPUT_DEVICE_H_
#define _TIMER_INPUT_DEVICE_H_


/* -------------------------------------------------------------------------- */

#include "input_device.h"

#include <thread>
#include <mutex>
#include <memory>


/* -------------------------------------------------------------------------- */

//! @brief Represents a timer input device
//! It implements repeating (TIMERTICK) events at regular and configurable 
//! clock intervals
class timer_input_device_t : public input_device_t
{
public:
   using interval_t = std::chrono::milliseconds;
   
   enum {
      DEFAULT_INTERVAL = 500 //!< default timer interval (in ms)
   };

public:
   //! ctor
   explicit timer_input_device_t(
      interval_t intv = interval_t(DEFAULT_INTERVAL));
   
   //! Modify current timer interval
   void change_interval(const interval_t& new_interval) throw();

   //! Get current timer interval
   interval_t get_interval() const throw();

   //! Poll an event
   virtual event_t poll() throw() override;

   //! dtor
   virtual ~timer_input_device_t() throw();

private:
   interval_t _interval; // ms
   bool _stop_thread_pending = false;
   bool _event = false;
   mutable std::mutex _mtx;
   std::unique_ptr < std::thread > _thread;

   bool _stop_request_pending() const throw();
   void _stop_thread() throw();
   bool _ack_event() throw();
   void _notify_event() throw();
   static void _thread_proc(timer_input_device_t* _this);
};

#endif