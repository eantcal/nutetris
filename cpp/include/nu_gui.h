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

#ifndef __NU_GUI_H__
#define __NU_GUI_H__

#ifndef TEXT_MODE

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

   gui_t(gdi_ctx_t & ctx) noexcept;

   static gui_t * _instance;

public:
   static const int WHITE = _nu_rgb(0xff, 0xff, 0xff);

   static gui_t & get_instance() noexcept;

   int textout(int x, int y, const std::string& text, int c) noexcept;
   int line(int x1, int y1, int x2, int y2, int pw=1, int col=WHITE) noexcept;
   int rect(int x, int y, int dx, int dy, int pw=1, int col=WHITE, bool full=false) noexcept;
   int ellipse(int x, int y, int dx, int dy, int pw=1, int col=WHITE, bool full=false) noexcept;
   int circle(int x, int y, int r, int pw=1, int col=WHITE, bool full=false) noexcept;

   int get_client_width() noexcept;
   int get_client_height() noexcept;

   int mouse_x() noexcept;
   int mouse_y() noexcept;
   int mouse_btn() noexcept;

   int msg_box(const std::string& title, const std::string& message, int flg=0) noexcept;
   int play_sound(const std::string& filename, int flg=1) noexcept;
   int move_window(int x, int y, int dx, int dy) noexcept;

   int get_window_x() noexcept;
   int get_window_y() noexcept;
   int get_window_dx() noexcept;
   int get_window_dy() noexcept;
};


/* -------------------------------------------------------------------------- */

} // namespace nu


/* -------------------------------------------------------------------------- */

#endif // TEXT_MODE

#endif //__NU_OS_GUI_H__
