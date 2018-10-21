/*
 *  This file is part of nuTetris
 *  Author: <antonino.calderone@gmail.com>
 *
 */

package nuTetris;

/**
 * Game entry point
 */
public class game {

    public static void main(String[] args) {

        GameManager gm = new GameManager();

        // Game main loop: run the game manager
        while (true) {
            gm.run();
        }
    }

}
