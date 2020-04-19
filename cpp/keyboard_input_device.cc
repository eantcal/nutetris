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

#include "keyboard_input_device.h"

#if !defined(__MINGW32__) && !defined(_WIN32)

#include "nu_terminal_input.h"
#include <thread>
#include <mutex>


/* -------------------------------------------------------------------------- */

class keyb_poller_t
{

public:
   using event_t = input_device_t::event_t;

private:
   mutable std::mutex _mtx;
   nu::termios_makeraw_t _raw_mode;
   nu::terminal_input_t _termin;

   event_t _last_event = event_t::NONE;


public:
   event_t get_last_event() noexcept
   {
      std::lock_guard<std::mutex> lk(_mtx);
      auto ev = _last_event;
      _last_event = event_t::NONE;
      return ev;
   }
   
   keyb_poller_t()
   {
      std::thread t(poll_event, this);
      t.detach();
   }

   static void poll_event(keyb_poller_t * _this)
   {
      event_t ev = event_t::NONE;

      while (1)
      {
         int code = _this->_termin.getch();

         switch (code)
         {
            case EOF:
               ev = event_t::NONE;
               break;

            case nu::terminal_input_t::UP:
               ev = event_t::UP;
               break;

            case nu::terminal_input_t::DOWN:
               ev = event_t::DOWN;
               break;

            case nu::terminal_input_t::LEFT:
               ev = event_t::LEFT;
               break;

            case nu::terminal_input_t::RIGHT:
               ev = event_t::RIGHT;
               break;

            case nu::terminal_input_t::ESCAPE:
            case nu::terminal_input_t::ESCAPE2:
               ev = event_t::ESCAPE;
               break;

            case nu::terminal_input_t::SPACE:
               ev = event_t::SPACE;
               break;

            default:
               ev = event_t::UNKNOWN;
               break;
         }

         {
            std::lock_guard<std::mutex> lk(_this->_mtx);   
            _this->_last_event = ev;
         }
      }
   }

};


/* -------------------------------------------------------------------------- */

input_device_t::event_t keyboard_input_device_t::poll() noexcept
{
   static keyb_poller_t poller;
   return poller.get_last_event();
}


/* -------------------------------------------------------------------------- */

#else  /* Windows */


#include <conio.h>


/* -------------------------------------------------------------------------- */

input_device_t::event_t keyboard_input_device_t::poll() noexcept
{
   if (!_kbhit())
      return event_t::NONE;

   int code = _getch_nolock();

   if (code == 224)
   {
      code = _getch_nolock();

      switch (code)
      {
      case 80:
         return event_t::DOWN;
      case 75:
         return event_t::LEFT;
      case 72:
         return event_t::UP;
      case 77:
         return event_t::RIGHT;
      }
   }
   else
   {
      switch (code)
      {
      case 27:
         return event_t::ESCAPE;
      case 32:
         return event_t::SPACE;
      }
   }

   return event_t::UNKNOWN;
}

#endif
