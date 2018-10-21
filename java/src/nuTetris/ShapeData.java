/*
 *  This file is part of nuTetris
 *  Author: <antonino.calderone@gmail.com>
 *
 */

package nuTetris;

import nuTetris.Piece;

/**
 * Represents the data used to draw a piece 
 */
public class ShapeData extends GridData {
    ShapeData() {
        super(Piece.COLS, Piece.ROWS);
    }
}
