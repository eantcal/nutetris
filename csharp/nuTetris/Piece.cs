/*
 *  This file is part of nuTetris
 *  Author: <antonino.calderone@gmail.com>
 *
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace nuTetris
{
    /*
    *  This file is part of nuTetris
    *  Author: <antonino.calderone@gmail.com>
    *
    */


    /** Defines the interface of a falling piece */
    public abstract class Piece
    {
        public static int ROWS = 4;
        public static int COLS = 4;
        public static int ORIENTATIONS = 4;

        /** Clone the piece returning a unique pointer to it */
        public abstract Piece clone();

        /** Set column offset to center the piece within the row */
        public abstract void moveCenter(int rowLength);

        /** Increments game-grid related piece column offset */
        public abstract void moveRight();

        /** Decrements game-grid related piece column offset */
        public abstract void moveLeft();

        /** Increment game-grid related piece row offset */
        public abstract void moveDown();

        /** Rotate the piece clockwise */
        public abstract void rotateCw();

        /** Rotate the piece anti-clockwise */
        public abstract void rotateAcw();

        /** Undo the last movement command */
        public abstract void undo();

        /** Get a color attribute at piece-grid coordinates col, row */
        public abstract int getAt(int col, int row);

        /** Get game-grid piece column offset */
        public abstract int getCol();

        /** Get game-grid piece row offset */
        public abstract int getRow();

        /** Get the count of empty piece-grid columns on the left side of piece shape */
        public abstract int getLeftMargin();

        /** Get the count of empty piece-grid columns on the right side of piece shape */
        public abstract int getRightMargin();

        /** Get the count of empty piece-grid rows on the top side of piece shape */
        public abstract int getTopMargin();

        /** Get the count of empty piece-grid rows on the bottom side of piece shape */
        public abstract int getBottomMargin();

        /** Get piece orientation code */
        public abstract int getOrientation();

        /** Get piece shape data */
        public abstract ShapeData getShape();
    }
}
