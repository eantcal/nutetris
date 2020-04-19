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
   void change_interval(const interval_t& new_interval) noexcept;

   //! Get current timer interval
   interval_t get_interval() const noexcept;

   //! Poll an event
   virtual event_t poll() noexcept override;

   //! dtor
   virtual ~timer_input_device_t() noexcept;

private:
   interval_t _interval; // ms
   bool _stop_thread_pending = false;
   bool _event = false;
   mutable std::mutex _mtx;
   std::unique_ptr < std::thread > _thread;

   bool _stop_request_pending() const noexcept;
   void _stop_thread() noexcept;
   bool _ack_event() noexcept;
   void _notify_event() noexcept;
   static void _thread_proc(timer_input_device_t* _this);
};

#endif