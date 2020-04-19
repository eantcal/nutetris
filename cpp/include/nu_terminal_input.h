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

#if !defined(__MINGW32__) && !defined(_WIN32)
#ifndef __NU_TERMINAL_INPUT_H__
#define __NU_TERMINAL_INPUT_H__

/* -------------------------------------------------------------------------- */
// Headers
/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>

#include <string>
#include <set>
#include <list>
#include <vector>


/* -------------------------------------------------------------------------- */

namespace nu 
{


/* -------------------------------------------------------------------------- */
/* termios_reset_t                                                            */
/* -------------------------------------------------------------------------- */

struct termios_reset_t
{
private:
   struct termios _oldt;

public:
   inline termios_reset_t() throw()
   {
      tcgetattr(STDIN_FILENO, &_oldt);
   }

   inline ~termios_reset_t() throw()
   {
      tcsetattr(STDIN_FILENO, TCSANOW, &_oldt);
   }
};



/* -------------------------------------------------------------------------- */
/* termios_makeraw_t                                                          */
/* -------------------------------------------------------------------------- */

struct termios_makeraw_t : public termios_reset_t
{
public:
   inline termios_makeraw_t() throw()
   {
      struct termios new_termios;

      tcgetattr(0, &new_termios);

      cfmakeraw(&new_termios);
      tcsetattr(0, TCSANOW, &new_termios);
   }
};


/* -------------------------------------------------------------------------- */

/*! \brief This class provides a simple terminal input mechanism 
 * based on Unix General Terminal Interface (termios)
 */
class terminal_input_t
{
private:
   bool _disable_stdin_echo;

public:
   enum vkey_t 
   {
      CTRL_A = 1,
      CTRL_B, CTRL_C, CTRL_D, CTRL_E,
      CTRL_G, CTRL_F, CTRL_H, CTRL_I,
      CTRL_J, CTRL_K, CTRL_L, CTRL_M,
      CTRL_N, CTRL_O, CTRL_P, CTRL_Q,
      CTRL_R, CTRL_S, CTRL_T, CTRL_Y,
      CTRL_V, CTRL_W, CTRL_Z, 

      RETURN      = 0x0a, 

      LF          = 0x0a, 
      CR          = 0x0d,

      SPACE       = 0x20,

      TAB         = 0x09,
      ESCAPE      = 0x1b,
      ESCAPE2     = 0x5b,
      BACKSPACE   = 0x7f,

      HOME        = 0x1b5b487e,
      END         = 0x1b5b467e,
      PGUP        = 0x1b5b357e,
      PGDOWN      = 0x1b5b367e,
      DELETE      = 0x1b5b337e,
      INSERT      = 0x1b5b327e,

      UP          = 0x1b5b41,
      DOWN        = 0x1b5b42,
      RIGHT       = 0x1b5b43,
      LEFT        = 0x1b5b44,
   };


   inline
      terminal_input_t( bool disable_stdin_echo = true ) :
      _disable_stdin_echo( disable_stdin_echo ) {}

   virtual ~terminal_input_t() throw();
   virtual int getch() const throw();

   /*! \brief returns a nonzero value if a key has been pressed. 
    *  Otherwise, it returns 0 (no events) or a 
    *  negative value in case of error 
    */
   virtual int keybhit() const throw();


   /*! \brief returns a character if a key has been pressed. 
    *  Otherwise, it returns 0 (no events) or a 
    *  negative value in case of error 
    */
   virtual char getrawch() const throw();
};



/* -------------------------------------------------------------------------- */

} /* namespce nu */


#endif // __NU_TERMINAL_INPUT_H__
#endif
