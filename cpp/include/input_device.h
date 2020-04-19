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

#ifndef _INPUT_DEVICE_H_
#define _INPUT_DEVICE_H_


/* -------------------------------------------------------------------------- */

//! @brief This interface represents a specific input device 
class input_device_t
{
public:

   //! Input event list
   enum class event_t
   {
      NONE,
      LEFT,
      RIGHT,
      DOWN,
      UP,
      SPACE,
      PAUSE,
      ESCAPE,
      TIMERTICK,
      UNKNOWN
   };

   //! Peeks the event of input device, if any, and returns it. 
   virtual event_t poll() throw() = 0;
};


/* -------------------------------------------------------------------------- */

#endif 