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


#include "tetris_config.h"
#include "tetris_graph_game_mgr.h"

#include <thread>

/* -------------------------------------------------------------------------- */

int main(int argc, char* argv[])
{
   auto & game = 
      tetris::make_game_mgr_instance<tetris::graph_game_mgr_t>();

   const auto a_while = 
      std::chrono::milliseconds(NU_TETRIS_GAME_SLEEP_INTV);

   while (1)
   {
      //Sleep for a while in order to allow other 
      //processes/threads to run
      std::this_thread::sleep_for(a_while);
      game.run();
   }
   
	return 0;
}

