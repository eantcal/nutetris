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

#ifndef TEXT_MODE
#include "nu_gui.h"

#ifdef _WIN32

#ifndef __MINGW32__ 
#pragma comment(lib, "Winmm.lib")
#pragma comment (lib,"Gdiplus.lib")

#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#endif


/* -------------------------------------------------------------------------- */

#include <windows.h>
#include <stdio.h>


/* -------------------------------------------------------------------------- */

namespace nu
{

#ifndef __MINGW32__ 
   static struct gdi_plus_t
   {
      GdiplusStartupInput gdiplusStartupInput;
      ULONG_PTR           gdiplusToken;

      gdi_plus_t()
      {
         // Initialize GDI+.
         GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
      }

      virtual ~gdi_plus_t()
      {
         GdiplusShutdown(gdiplusToken);
      }
   }
   _gdi_plus_instance;

#endif


/* -------------------------------------------------------------------------- */

class gdi_ctx_t
{
public:
   enum brush_t {
      NO_BRUSH, SOLID_BRUSH
   };

   gdi_ctx_t() = delete;
   gdi_ctx_t(gdi_ctx_t&) = delete;


private:
   HWND _console_hwnd = nullptr;
   HDC _hdc = nullptr;
   HPEN _hpen = nullptr;
   HBRUSH _hbr = nullptr;

   gdi_iarg_t _pen_color;
   brush_t _brush_type;
   gdi_iarg_t _brush_color;
   gdi_iarg_t _pen_width;


public:
   gdi_ctx_t(
      HWND winhandle,
      gdi_iarg_t pen_color = RGB(0xff, 0xff, 0xff),
      brush_t brush_type = NO_BRUSH,
      gdi_iarg_t brush_color = RGB(0xff, 0xff, 0xff),
      gdi_iarg_t pen_width = 1)
      :
      _console_hwnd(winhandle),
      _hdc(GetDC(winhandle)),
      _hpen(CreatePen(PS_SOLID, pen_width, pen_color)),
      _hbr(HBRUSH(GetStockObject(HOLLOW_BRUSH))),
      _pen_color(pen_color),
      _brush_type(brush_type),
      _brush_color(brush_color),
      _pen_width(pen_width)
   {
      SelectObject(_hdc, _hpen);

      if (brush_type == SOLID_BRUSH)
         _hbr = CreateSolidBrush(brush_color);

      if (_hdc && _hbr)
         SelectObject(_hdc, _hbr);
   }


   HWND get_hwnd() const noexcept
   {
      return _console_hwnd;
   }


   void set_pen(gdi_iarg_t pen_color, gdi_iarg_t pen_width)
   {
      if (
         _hpen == nullptr ||
         pen_color != _pen_color ||
         pen_width != _pen_width)
      {
         _pen_color = pen_color;
         _pen_width = pen_width;

         if (_hpen)
            DeleteObject(_hpen);

         _hpen = CreatePen(PS_SOLID, pen_width, pen_color);

         if (_hdc && _hpen)
            SelectObject(_hdc, _hpen);
      }
   }


   void set_brush(brush_t brush_type, gdi_iarg_t brush_color)
   {
      if (
         _hbr == nullptr ||
         brush_type != _brush_type ||
         brush_color != _brush_color)
      {
         if (_hbr)
            DeleteObject(_hbr);

         _hbr = brush_type == SOLID_BRUSH ?
            CreateSolidBrush(brush_color) :
            HBRUSH(GetStockObject(HOLLOW_BRUSH));

         if (_hdc && _hbr)
            SelectObject(_hdc, _hbr);
      }
   }


   HDC get_hdc() const noexcept
   {
      return _hdc;
   }


   HDC reset_hdc() noexcept
   {
      if (_hbr)
         DeleteObject(_hbr);

      if (_hpen)
         DeleteObject(_hpen);

      if (_hdc)
         ReleaseDC(_console_hwnd, _hdc);

      _hdc = GetDC(get_hwnd());

      SelectObject(_hdc, _hpen);

      if (_brush_type == SOLID_BRUSH)
         _hbr = CreateSolidBrush(_brush_color);
      else
         _hbr = HBRUSH(GetStockObject(HOLLOW_BRUSH));

      if (_hdc && _hbr)
         SelectObject(_hdc, _hbr);

      return _hdc;
   }


   virtual ~gdi_ctx_t()
   {
      if (_hbr)
         DeleteObject(_hbr);

      if (_hpen)
         DeleteObject(_hpen);

      if (_hdc)
         ReleaseDC(_console_hwnd, _hdc);
   }

};


/* -------------------------------------------------------------------------- */

gui_t* gui_t::_instance = nullptr;


/* -------------------------------------------------------------------------- */

gui_t::gui_t(gdi_ctx_t& ctx) noexcept : _ctx(ctx)
{
}


/* -------------------------------------------------------------------------- */

gui_t& gui_t::get_instance() noexcept
{
   if (!_instance)
   {
      gdi_ctx_t* gdi_ctx =
         new gdi_ctx_t(GetConsoleWindow());

      _instance = new gui_t(*gdi_ctx);
   }

   return *_instance;
}


/* -------------------------------------------------------------------------- */

int gui_t::textout(int x, int y, const std::string& text, int c) noexcept
{
   auto hdc = _ctx.get_hdc();

   SetTextColor(hdc, c);
   SetBkMode(hdc, TRANSPARENT);

   BOOL ret = ::TextOut(hdc, x, y, text.c_str(), int(text.size()));

   GdiFlush();

   return ret ? 0 : errno;
}


/* -------------------------------------------------------------------------- */

void _create_pen_brush(gdi_ctx_t& ctx, int col, int pen_width, bool full)
{

   ctx.set_pen(col, pen_width);

   ctx.set_brush(
      full ?
      gdi_ctx_t::brush_t::SOLID_BRUSH :
      gdi_ctx_t::brush_t::NO_BRUSH,
      col
   );
}


/* -------------------------------------------------------------------------- */

int gui_t::line(int x1, int y1, int x2, int y2, int pw, int col) noexcept
{
   POINT ppt = { 0 };

   _create_pen_brush(_ctx, col, pw, false);

   BOOL ret = MoveToEx(_ctx.get_hdc(), x1, y1, &ppt);
   ret = ret && LineTo(_ctx.get_hdc(), x2, y2);

   GdiFlush();

   return ret ? 0 : GetLastError();
}


/* -------------------------------------------------------------------------- */

int gui_t::rect(int x, int y, int dx, int dy, int pw, int col, bool full) noexcept
{
   _create_pen_brush(_ctx, col, pw, full);

   auto ret = Rectangle(_ctx.get_hdc(), x, y, abs(dx) + x, abs(dy) + y) ?
      0 : errno;

   GdiFlush();

   return ret;
}


/* -------------------------------------------------------------------------- */

int gui_t::ellipse(int x, int y, int dx, int dy, int pw, int col, bool full) noexcept
{
   _create_pen_brush(_ctx, col, pw, full);

   auto ret = Ellipse(_ctx.get_hdc(), x, y, abs(dx) + x, abs(dy) + y) ?
      0 : errno;

   GdiFlush();

   return ret;
}


/* -------------------------------------------------------------------------- */

int gui_t::circle(int x, int y, int r, int pw, int col, bool full) noexcept
{
   const int x1 = x - r;
   const int y1 = y - r;
   const int x2 = x + r;
   const int y2 = y + r;

   _create_pen_brush(_ctx, col, pw, full);

   auto ret = Ellipse(_ctx.get_hdc(), x1, y1, x2, y2) ? 0 : errno;

   GdiFlush();

   return ret;
}

}

/* -------------------------------------------------------------------------- */

#else // LINUX -----------------------------------------------------------------

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <thread>


/* -------------------------------------------------------------------------- */

namespace nu
{


/* -------------------------------------------------------------------------- */

struct gdi_ctx_t
{
   enum brush_t { NO_BRUSH, SOLID_BRUSH };

   gdi_ctx_t() = delete;
   gdi_ctx_t(gdi_ctx_t&) = delete;

private:
   Window _xterm_win = 0;
   Display* _display = 0;
   int _screen_num = 0;
   Screen *_screen = 0;

   gdi_iarg_t _pen_color;
   brush_t   _brush_type;
   gdi_iarg_t _brush_color;
   gdi_iarg_t _pen_width;
   XColor _xcolor;
   Colormap _cmap;
   GC _gc;

   int _win_width = 0;
   int _win_height = 0;
   mutable int _win_x = 0;
   mutable int _win_y = 0;

public:
   gdi_ctx_t(
         gdi_iarg_t pen_color,
         brush_t brush_type,
         gdi_iarg_t brush_color,
         gdi_iarg_t pen_width)
      :
         _pen_color(pen_color),
         _brush_type(brush_type),
         _brush_color(brush_color),
         _pen_width(pen_width)
   {
      try
      {
         _xterm_win = std::stoi(::getenv("WINDOWID"));

      }
      catch (...)
      {
         _xterm_win = 0;
      }

      if (_xterm_win)
      {
         _display = XOpenDisplay(0);

         if (_display)
         {
            _screen_num = DefaultScreen( _display );
            _screen = XScreenOfDisplay( _display, _screen_num );
            _gc = create_gc( _pen_width );
            create_rgb_color( _pen_color );
            XSetForeground( _display, _gc, _xcolor.pixel );
            XWindowAttributes attr = {0};
            XGetWindowAttributes( _display, _xterm_win, &attr );
            _win_width = attr.width;
            _win_height = attr.height;
            _win_x = attr.x;
            _win_y = attr.y;


         }
      }
   }


/* -------------------------------------------------------------------------- */

protected:
   GC create_gc(int line_width)
   {
      XGCValues gc_val = {0};

      gc_val.function           = GXcopy;
      gc_val.plane_mask         = AllPlanes;
      gc_val.foreground         = WhitePixel(_display, _screen_num);
      gc_val.background         = BlackPixel(_display, _screen_num);
      gc_val.line_width         = line_width;
      gc_val.line_style         = LineSolid;
      gc_val.cap_style          = CapButt;
      gc_val.join_style         = JoinMiter;
      gc_val.fill_style         = FillOpaqueStippled;
      gc_val.fill_rule          = WindingRule;
      gc_val.graphics_exposures = False;
      gc_val.clip_x_origin      = 0;
      gc_val.clip_y_origin      = 0;
      gc_val.clip_mask          = None;
      gc_val.subwindow_mode     = IncludeInferiors;

      return XCreateGC(
            _display,
            _xterm_win,
            GCFunction    | GCPlaneMask     | GCForeground        |
            GCBackground  | GCLineWidth     | GCLineStyle         |
            GCCapStyle    | GCJoinStyle     | GCFillStyle         |
            GCFillRule    | GCClipXOrigin   | GCClipYOrigin       |
            GCClipMask    | GCSubwindowMode | GCGraphicsExposures ,
            &gc_val);
   }


/* -------------------------------------------------------------------------- */

   void getXYcoords() const
   {
      if (! _display)
         return;

      int screen_x, screen_y;
      Window child_win;
      Window parent_win;
      Window root_win;
      Window* child_windows;
      unsigned int num_child_windows;

      // make the query for the above values
      XQueryTree(_display, _xterm_win,
            &root_win,
            &parent_win,
            &child_windows, &num_child_windows);

      // we need to free the list of child IDs, as it was dynamically allocated
      // by the XQueryTree function.
      XFree(child_windows);

      XQueryTree(_display, parent_win,
            &root_win,
            &parent_win,
            &child_windows, &num_child_windows);

      XFree(child_windows);

      // make the coordinates translation, from the coordinates system
      // of the parent window, to the coordinates system of the root window,
      XTranslateCoordinates(_display, parent_win, root_win,
            _win_x, _win_y, &screen_x, &screen_y,
            &child_win);

      // screen_x and screen_y contain the location of our original
      // window, using screen coordinates
      _win_x = screen_x;
      _win_y = screen_y;
   }


/* -------------------------------------------------------------------------- */

   void create_rgb_color(unsigned int rgb)
   {
      _xcolor.red =  ((rgb & 0xff) << 8) | (rgb & 0xff);
      _xcolor.green = (rgb & 0xff00) | ((rgb>>8) & 0xff);
      _xcolor.blue = ((rgb>>8) & 0xff00) | ((rgb>>16) & 0xff);

      _xcolor.flags = DoRed | DoGreen | DoBlue;

      _cmap = DefaultColormap(_display, 0);

      XAllocColor(_display, _cmap, &_xcolor);
   }


/* -------------------------------------------------------------------------- */

public:


/* -------------------------------------------------------------------------- */

   int get_window_width() const noexcept
   {
      return _win_width;
   }


/* -------------------------------------------------------------------------- */

   int get_window_height() const noexcept
   {
      return _win_height;
   }


/* -------------------------------------------------------------------------- */

   int get_window_x() const noexcept
   {
      getXYcoords();
      return _win_x;
   }


/* -------------------------------------------------------------------------- */

   int get_window_y() const noexcept
   {
      getXYcoords();
      return _win_y;
   }


/* -------------------------------------------------------------------------- */

   int move_win(int x, int y) noexcept
   {
      return XMoveWindow(_display, _xterm_win, x,y);
   }


/* -------------------------------------------------------------------------- */

   int resize_win(int dx, int dy) noexcept
   {
      return XResizeWindow(_display, _xterm_win, dx, dy);
   }


/* -------------------------------------------------------------------------- */

   void textout(int x, int y, const std::string& text)
   {
      Font font = XLoadFont(_display, "fixed");
      XTextItem txt;
      txt.chars = const_cast<char*>(text.c_str());
      txt.nchars = text.size();
      txt.delta = 0;
      txt.font = font;
      XDrawText(_display, _xterm_win, _gc, x, y, &txt, 1);
      XUnloadFont(_display, font);
   }


/* -------------------------------------------------------------------------- */

   void rect(int x1, int y1, int x2, int y2)
   {
      int x = std::min(x1,x2);
      int y = std::min(y1,y2);
      XDrawRectangle(
            _display,
            _xterm_win,
            _gc,
            x, y,
            abs(abs(x2)-abs(x1)), abs(abs(y2)-abs(y1)));
   }


/* -------------------------------------------------------------------------- */

   void fillrect(int x1, int y1, int x2, int y2)
   {
      int x = std::min(x1,x2);
      int y = std::min(y1,y2);
      XFillRectangle(
            _display,
            _xterm_win,
            _gc,
            x, y,
            abs(abs(x2)-abs(x1))+1,
            abs(abs(y2)-abs(y1))+1);
   }


/* -------------------------------------------------------------------------- */

   void line(int x1, int y1, int x2, int y2)
   {
      XDrawLine(_display, _xterm_win, _gc, x1, y1, x2, y2);
   }


/* -------------------------------------------------------------------------- */

   void ellipse(int x1, int y1, int x2, int y2)
   {
      int x = std::min(x1,x2);
      int y = std::min(y1,y2);
      XDrawArc(
            _display,
            _xterm_win,
            _gc,
            x, y,
            abs(abs(x2)-abs(x1)), abs(abs(y2)-abs(y1)),
            0, 360*64);
   }


/* -------------------------------------------------------------------------- */

   void fillellipse(int x1, int y1, int x2, int y2)
   {
      int x = std::min(x1,x2);
      int y = std::min(y1,y2);
      XFillArc(
            _display,
            _xterm_win,
            _gc,
            x, y,
            abs(abs(x2)-abs(x1)), abs(abs(y2)-abs(y1)),
            0, 360*64);
   }
   

/* -------------------------------------------------------------------------- */

   ~gdi_ctx_t()
   {
      if (_display)
      {
         XFlush( _display );
         XFreeColors(_display, _cmap, &_xcolor.pixel, 1, 0);
         XFreeGC( _display, _gc );
         XCloseDisplay(_display);
      }
   }
};


/* -------------------------------------------------------------------------- */

struct mouse_ctx_t
{
   mouse_ctx_t(mouse_ctx_t&) = delete;
   private:
   Window _xterm_win = 0;
   Display* _display = 0;
   int _screen_num = 0;
   Screen *_screen = 0;

   int _win_x = 0;
   int _win_y = 0;

   public:
   mouse_ctx_t()
   {
      try
      {
         _xterm_win = std::stoi(::getenv("WINDOWID"));
      }
      catch (...)
      {
         _xterm_win = 0;
      }

      if (_xterm_win)
      {
         _display = XOpenDisplay(0);

         if (_display)
         {
            _screen_num = DefaultScreen( _display );
            _screen = XScreenOfDisplay( _display, _screen_num );
         }
      }
   }


/* -------------------------------------------------------------------------- */

   bool get_mouse_event( int & btn, std::pair<int,int> & mouse_coords )
   {
      int root_x = 0, root_y = 0;
      int win_x = 0, win_y = 0;
      unsigned int mask_return = 0;

      Window window_returned;

      unsigned int result =
         XQueryPointer(
               _display,
               _xterm_win,
               &window_returned,
               &window_returned,
               &root_x, &root_y,
               &win_x, &win_y,
               &mask_return);

      btn = (mask_return >> 8) & 7;
      mouse_coords.first = win_x;
      mouse_coords.second = win_y;

      return result != 0;
   }


   public:

/* -------------------------------------------------------------------------- */

   ~mouse_ctx_t()
   {
      if (_display)
      {
         XCloseDisplay(_display);
      }
   }
};


/* -------------------------------------------------------------------------- */

gui_t * gui_t::_instance = nullptr;


/* -------------------------------------------------------------------------- */

gui_t::gui_t( gdi_ctx_t & ctx ) noexcept : _ctx(ctx) 
{
}


/* -------------------------------------------------------------------------- */

gui_t & gui_t::get_instance() noexcept
{
   static gdi_ctx_t gdi_ctx(0, gdi_ctx_t::NO_BRUSH, 0, 1);

   if (!_instance)
      _instance = new gui_t(gdi_ctx);

   return *_instance;
}



/* -------------------------------------------------------------------------- */

int gui_t::textout(int x, int y, const std::string& text, int c) noexcept
{
   gdi_ctx_t gdi_ctx(c, gdi_ctx_t::NO_BRUSH, 0, 1);
   gdi_ctx.textout(x, y, text);
   return 0;
}


/* -------------------------------------------------------------------------- */

int gui_t::line(int x1, int y1, int x2, int y2, int pw, int col) noexcept
{
   gdi_ctx_t gdi_ctx(col, gdi_ctx_t::NO_BRUSH, 0, pw);
   gdi_ctx.line(x1, y1, x2, y2);
   return 0;
}


/* -------------------------------------------------------------------------- */

int gui_t::rect(int x, int y, int dx, int dy, int pw, int col, bool full) noexcept
{
   gdi_ctx_t gdi_ctx(col, full ? gdi_ctx_t::SOLID_BRUSH : gdi_ctx_t::NO_BRUSH, col, pw);

   if (full)
      gdi_ctx.fillrect(x, y, x+dx, y+dy);
   else
      gdi_ctx.rect(x, y, x+dx, y+dy);

   return 0;
}


/* -------------------------------------------------------------------------- */

int gui_t::ellipse(int x, int y, int dx, int dy, int pw, int col, bool full) noexcept
{
   gdi_ctx_t gdi_ctx(col, full ? gdi_ctx_t::SOLID_BRUSH : gdi_ctx_t::NO_BRUSH, col, pw);

   if (full)
      gdi_ctx.fillellipse(x, y, x+dx, y+dy);
   else
      gdi_ctx.ellipse(x, y, x+dx, y+dy);

   return 0;
}


/* -------------------------------------------------------------------------- */

int gui_t::circle(int x, int y, int r, int pw, int col, bool full) noexcept
{
   const int x1 = x - r;
   const int y1 = y - r;
   const int x2 = x + r;
   const int y2 = y + r;

   gdi_ctx_t gdi_ctx(col, full ? gdi_ctx_t::SOLID_BRUSH : gdi_ctx_t::NO_BRUSH, col, pw);

   if (full)
      gdi_ctx.fillellipse(x1, y1, x2, y2);
   else
      gdi_ctx.ellipse(x1, y1, x2, y2);

   return 0;
}


/* -------------------------------------------------------------------------- */

int gui_t::get_client_width() noexcept
{
   gdi_ctx_t gdi_ctx(0, gdi_ctx_t::NO_BRUSH, 0, 1);
   return gdi_ctx.get_window_width();
}


/* -------------------------------------------------------------------------- */

int gui_t::get_client_height() noexcept
{
   gdi_ctx_t gdi_ctx(0, gdi_ctx_t::NO_BRUSH, 0, 1);
   return gdi_ctx.get_window_height();
}


/* -------------------------------------------------------------------------- */

int gui_t::mouse_x() noexcept
{
   mouse_ctx_t ctx;
   int btn = 0;
   std::pair<int, int> pos = { 0, 0 };

   bool res = ctx.get_mouse_event( btn, pos );

   return res ? pos.first : 0;
}


/* -------------------------------------------------------------------------- */

int gui_t::mouse_y() noexcept
{
   mouse_ctx_t ctx;
   int btn = 0;
   std::pair<int, int> pos = { 0, 0 };

   bool res = ctx.get_mouse_event( btn, pos );

   return res ? pos.second : 0;
}


/* -------------------------------------------------------------------------- */

int gui_t::mouse_btn() noexcept
{
   mouse_ctx_t ctx;
   int btn = 0;
   std::pair<int, int> pos = { 0, 0 };

   bool res = ctx.get_mouse_event( btn, pos );

   return res ? btn : 0;
}


/* -------------------------------------------------------------------------- */

int gui_t::msg_box(const std::string& title, const std::string& message, int flg) noexcept
{
   // Display message using xmessage
   std::string msg =
      "xmessage -center \"" + title + (title.empty() ? "" : ": ") + message + "\"";

   return system(msg.c_str());
}   


/* -------------------------------------------------------------------------- */

int gui_t::play_sound(const std::string& filename, int flg) noexcept
{
   bool sync = true;

   switch (flg)
   {
      case 1:
         sync = false;
         break;

      case 0:
      default:
         break;
   }

   std::string cmd = "aplay \"";
   cmd += filename;
   cmd += "\" >/dev/null 2>/dev/null";

   if ( sync )
   {
      return ::system( cmd.c_str() );
   }
   else
   {
      std::thread async( [&]()
            {
            int res = ::system( cmd.c_str() );
            (void) res;
            } );

      async.detach();
   }

   return 0;
}


/* -------------------------------------------------------------------------- */

int gui_t::move_window(int x, int y, int dx, int dy) noexcept
{
   gdi_ctx_t gdi_ctx(0, gdi_ctx_t::NO_BRUSH, 0, 1);
   int ret = gdi_ctx.move_win(x,y);
   return ret && gdi_ctx.resize_win(dx,dy);
}


/* -------------------------------------------------------------------------- */

int gui_t::get_window_x() noexcept
{
   gdi_ctx_t gdi_ctx(0, gdi_ctx_t::NO_BRUSH, 0, 1);
   return gdi_ctx.get_window_x();
}


/* -------------------------------------------------------------------------- */

int gui_t::get_window_y() noexcept
{
   gdi_ctx_t gdi_ctx(0, gdi_ctx_t::NO_BRUSH, 0, 1);
   return gdi_ctx.get_window_y();
}


/* -------------------------------------------------------------------------- */

int gui_t::get_window_dx() noexcept
{
   gdi_ctx_t gdi_ctx(0, gdi_ctx_t::NO_BRUSH, 0, 1);
   return gdi_ctx.get_window_width();
}


/* -------------------------------------------------------------------------- */

int gui_t::get_window_dy() noexcept
{
   gdi_ctx_t gdi_ctx(0, gdi_ctx_t::NO_BRUSH, 0, 1);
   return gdi_ctx.get_window_height();
}


/* -------------------------------------------------------------------------- */

}


#endif // ... LINUX
#endif 


