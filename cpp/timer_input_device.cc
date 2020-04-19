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

#include "timer_input_device.h"


/* -------------------------------------------------------------------------- */

bool timer_input_device_t::_stop_request_pending() const noexcept
{
   std::lock_guard<std::mutex> lock(_mtx);
   return _stop_thread_pending;
}


/* -------------------------------------------------------------------------- */

void timer_input_device_t::_stop_thread() noexcept
{
   std::lock_guard<std::mutex> lock(_mtx);
   _stop_thread_pending = true;
}


/* -------------------------------------------------------------------------- */

bool timer_input_device_t::_ack_event() noexcept
{
   std::lock_guard<std::mutex> lock(_mtx);

   bool ret = _event;
   _event = false;

   return ret;
}


/* -------------------------------------------------------------------------- */

void timer_input_device_t::_notify_event() noexcept
{
   std::lock_guard<std::mutex> lock(_mtx);
   _event = true;
}


/* -------------------------------------------------------------------------- */

void timer_input_device_t::_thread_proc(timer_input_device_t* _this)
{
   while (!_this->_stop_request_pending())
   {
      const std::chrono::milliseconds dura(_this->get_interval());
      std::this_thread::sleep_for(dura);

      _this->_notify_event();
   }
}


/* -------------------------------------------------------------------------- */

timer_input_device_t::timer_input_device_t(interval_t intv) :
   _interval(intv),
   _thread(new std::thread(_thread_proc, this))
{
}


/* -------------------------------------------------------------------------- */

void timer_input_device_t::change_interval(const interval_t& new_interval) noexcept
{
   std::lock_guard<std::mutex> lock(_mtx);
   _interval = new_interval;
}


/* -------------------------------------------------------------------------- */

timer_input_device_t::interval_t timer_input_device_t::get_interval() const noexcept
{
   std::lock_guard<std::mutex> lock(_mtx);
   return _interval;
}


/* -------------------------------------------------------------------------- */

input_device_t::event_t timer_input_device_t::poll() noexcept
{
   return _ack_event() ? event_t::TIMERTICK : event_t::NONE;
}


/* -------------------------------------------------------------------------- */

timer_input_device_t::~timer_input_device_t() noexcept
{
   _stop_thread();
   _thread->join();
}

