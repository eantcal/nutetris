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