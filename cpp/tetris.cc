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


#include "tetris_config.h"
#include "tetris_graph_game_mgr.h"

#include <thread>

/* -------------------------------------------------------------------------- */

int main()
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

