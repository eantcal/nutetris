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

#ifndef _KEYBOARD_INPUT_DEVICE_H_
#define _KEYBOARD_INPUT_DEVICE_H_


/* -------------------------------------------------------------------------- */

#include "input_device.h"


/* -------------------------------------------------------------------------- */

//! @brief Represents the keyboard input device
class keyboard_input_device_t : public input_device_t
{
public:

   //! Peeks keyboard event, if any, and returns it
   virtual event_t poll() throw() override;
};


/* -------------------------------------------------------------------------- */

#endif