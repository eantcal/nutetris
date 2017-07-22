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

#ifndef __NU_GUI_H__
#define __NU_GUI_H__

#include <vector>
#include <string>



/* -------------------------------------------------------------------------- */

namespace nu
{


/* -------------------------------------------------------------------------- */

using gdi_iarg_t = unsigned int;
class gdi_ctx_t;


/* -------------------------------------------------------------------------- */

#ifndef _nu_rgb
#define _nu_rgb(r,g,b) \
   ((unsigned int)(((unsigned char)(r)|\
   ((unsigned short)((unsigned char)(g))<<8))|\
   (((unsigned short)(unsigned char)(b))<<16)))
#endif

class gui_t
{
private:
   gdi_ctx_t & _ctx;

   gui_t(gdi_ctx_t & ctx) throw();

   static gui_t * _instance;

public:
   static const int WHITE = _nu_rgb(0xff, 0xff, 0xff);

   static gui_t & get_instance() throw();

   int textout(int x, int y, const std::string& text, int c) throw();
   int plotimage(int x, int y, const std::string& filename) throw();
   int line(int x1, int y1, int x2, int y2, int pw=1, int col=WHITE) throw();
   int rect(int x, int y, int dx, int dy, int pw=1, int col=WHITE, bool full=false) throw();
   int ellipse(int x, int y, int dx, int dy, int pw=1, int col=WHITE, bool full=false) throw();
   int circle(int x, int y, int r, int pw=1, int col=WHITE, bool full=false) throw();

   int get_client_width() throw();
   int get_client_height() throw();

   int mouse_x() throw();
   int mouse_y() throw();
   int mouse_btn() throw();

   int msg_box(const std::string& title, const std::string& message, int flg=0) throw();
   int play_sound(const std::string& filename, int flg=1) throw();
   int move_window(int x, int y, int dx, int dy) throw();

   int get_window_x() throw();
   int get_window_y() throw();
   int get_window_dx() throw();
   int get_window_dy() throw();
};


/* -------------------------------------------------------------------------- */

} // namespace nu


/* -------------------------------------------------------------------------- */

#endif //__NU_OS_GUI_H__