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
#include "nu_terminal_input.h"

namespace nu
{



/* -------------------------------------------------------------------------- */
// termios_disable_echo_t
/* -------------------------------------------------------------------------- */

struct termios_disable_echo_t : public termios_reset_t
{
public:
   inline termios_disable_echo_t() throw()
   {
      struct termios newt;
      tcgetattr(STDIN_FILENO, &newt);
      newt.c_lflag &= ~(ICANON | ECHO);
      tcsetattr(STDIN_FILENO, TCSANOW, &newt);
   }
};


/* -------------------------------------------------------------------------- */
// terminal_input_t
/* -------------------------------------------------------------------------- */


terminal_input_t :: ~terminal_input_t() throw()
{
}


/* -------------------------------------------------------------------------- */

int terminal_input_t::getch() const throw()
{
   int ch = 0;

   termios_disable_echo_t echo_off;

   do
   {
      ch = getchar();

      if (ch != EOF)
      {
         if (ch == ESCAPE)
         {
            ch = getchar();

            if (ch == ESCAPE2)
            {
               ch = getchar();

               int retval1 = ((ESCAPE << 16) | (ESCAPE2 << 8) | (ch & 0xff));
               int retval2 = (retval1 << 8) | 0x7e;

               switch (retval2)
               {
               case HOME:
               case END:
               case PGUP:
               case PGDOWN:
               case DELETE:
               case INSERT:
                  ch = getchar();
                  if (ch != EOF)
                  {
                     return retval2;
                  }
                  else
                  {
                     ungetc(ch, stdin);
                     return retval1;
                  }
                  break;
               }

               return retval1;
            }
            else
            {
               return ((ESCAPE << 8) | (ch & 0xff));
            }
         }

         return ch;
      }
   } while (true);

   return EOF;
}


/* -------------------------------------------------------------------------- */

int terminal_input_t::keybhit() const throw()
{
   termios_makeraw_t makeraw_now;

   struct timeval tv = { 0L, 0L };

   fd_set fds;
   FD_ZERO(&fds);
   FD_SET(0, &fds);

   int ret = ::select(1, &fds, NULL, NULL, &tv);

   return ret > 0 ? 1 : ret;
}


/* -------------------------------------------------------------------------- */

char terminal_input_t::getrawch() const throw()
{
   if (keybhit())
   {
      termios_makeraw_t makeraw_now;

      char c = 0;

      if (::read(0, &c, sizeof(c)) < 0)
         return (char)-1; // EOF

      return c;
   }

   return 0;
}


/* -------------------------------------------------------------------------- */
// end namespace nu

}
#endif

