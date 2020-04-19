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