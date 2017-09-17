bin_PROGRAMS = nutetris

AM_CXXFLAGS = $(INTI_CFLAGS) -pthread -std=c++11 -I/usr/X11/include
LDFLAGS+= -L/usr/X11/lib -lX11

nutetris_SOURCES = config.h \
        input_device.h \
        input_event_dispatcher.cc \
        input_event_dispatcher.h \
        input_event_listener.h \
        keyboard_input_device.cc \
        keyboard_input_device.h \
        nu_gui.cc \
        nu_gui.h \
        nu_stb_image.h \
        nu_stb_image.cc \
        nu_terminal_input.cc \
        nu_terminal_input.h \
        tetris.cc \
        tetris_concrete_piece.cc \
        tetris_concrete_piece.h \
        tetris_game_mgr.cc \
        tetris_game_mgr.h \
        tetris_game_state.h \
        tetris_gdimode_renderer.cc \
        tetris_gdimode_renderer.h \
        tetris_graph_game_mgr.h \
        tetris_grid.cc \
        tetris_grid.h \
        tetris_input_mgr.cc \
        tetris_input_mgr.h \
        tetris_piece_factory.cc \
        tetris_piece_factory.h \
        tetris_piece.h \
        tetris_piece_I.cc \
        tetris_piece_J.cc \
        tetris_piece_L.cc \
        tetris_piece_O.cc \
        tetris_piece_S.cc \
        tetris_piece_T.cc \
        tetris_piece_Z.cc \
        tetris_renderer.h \
        tetris_textmode_renderer.cc \
        tetris_textmode_renderer.h \
        timer_input_device.cc \
        timer_input_device.h 
