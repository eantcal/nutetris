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

#ifndef _TETRIS_CONFIG_H_
#define _TETRIS_CONFIG_H_


/* -------------------------------------------------------------------------- */
#ifdef _WIN32

#define NU_TETRIS_FALLING_INTV         1000  /* ms */
#define NU_TETRIS_GAME_SLEEP_INTV        10  /* ms */
#define NU_TETRIS_PIECE_SIZE             20  /* pixels */
#define NU_TETRIS_DEF_COLS               10  /* Default game area columns */
#define NU_TETRIS_DEF_ROWS               20  /* Default game area rows */
#define NU_TETRIS_FALLING_IDLE_INTV     500  /* Initial falling idle timeout (ms) */
#define NU_TETRIS_FULL_ROW_BLNK_DL      250  /* 'Full-row blink' delay */
#define NU_TETRIS_FULL_ROW_SCORE_ODM     10  /* Score order of magnitude */

#define NU_TETRIS_GRIDX                 200  /* pixels */
#define NU_TETRIS_GRIDY                 100  /* pixels */
#define NU_TETRIS_SCOREX                200  /* pixels */
#define NU_TETRIS_SCOREY                 10  /* pixels */
#define NU_TETRIS_SCOREDX               200  /* pixels */
#define NU_TETRIS_SCOREDY                60  /* pixels */
#define NU_TETRIS_SCORE_TXT_XOFF         30  /* pixels */
#define NU_TETRIS_SCORE_TXT_YOFF         20  /* pixels */
#define NU_TETRIS_CANVAS_X               30  /* pixels */
#define NU_TETRIS_CANVAS_Y               30  /* pixels */

#else

#define NU_TETRIS_FALLING_INTV          200  /* ms */
#define NU_TETRIS_GAME_SLEEP_INTV         1  /* ms */
#define NU_TETRIS_PIECE_SIZE             16  /* pixels */
#define NU_TETRIS_DEF_COLS               10  /* Default game area columns */
#define NU_TETRIS_DEF_ROWS               20  /* Default game area rows */
#define NU_TETRIS_FALLING_IDLE_INTV     200  /* Initial falling idle timeout (ms) */
#define NU_TETRIS_FULL_ROW_BLNK_DL      200  /* 'Full-row blink' delay */
#define NU_TETRIS_FULL_ROW_SCORE_ODM     10  /* Score order of magnitude */

#define NU_TETRIS_GRIDX                 200  /* pixels */
#define NU_TETRIS_GRIDY                 100  /* pixels */
#define NU_TETRIS_SCOREX                200  /* pixels */
#define NU_TETRIS_SCOREY                 10  /* pixels */
#define NU_TETRIS_SCOREDX               200  /* pixels */
#define NU_TETRIS_SCOREDY                60  /* pixels */
#define NU_TETRIS_SCORE_TXT_XOFF         30  /* pixels */
#define NU_TETRIS_SCORE_TXT_YOFF         30  /* pixels */
#define NU_TETRIS_CANVAS_X               20  /* pixels */
#define NU_TETRIS_CANVAS_Y               20  /* pixels */

#endif


/* -------------------------------------------------------------------------- */

#endif // _TETRIS_CONFI_H_
