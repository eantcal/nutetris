/*
 *  This file is part of nuTetris
 *  Author: <antonino.calderone@gmail.com>
 *
 */

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
        public abstract Piece Clone();

        /** Set column offset to center the piece within the row */
        public abstract void MoveCenter(int rowLength);

        /** Increments game-grid related piece column offset */
        public abstract void MoveRight();

        /** Decrements game-grid related piece column offset */
        public abstract void MoveLeft();

        /** Increment game-grid related piece row offset */
        public abstract void MoveDown();

        /** Rotate the piece clockwise */
        public abstract void RotateCw();

        /** Rotate the piece anti-clockwise */
        public abstract void RotateAcw();

        /** Undo the last movement command */
        public abstract void Undo();

        /** Get a color attribute at piece-grid coordinates col, row */
        public abstract int GetAt(int col, int row);

        /** Get game-grid piece column offset */
        public abstract int GetCol();

        /** Get game-grid piece row offset */
        public abstract int GetRow();

        /** Get the count of empty piece-grid columns on the left side of piece shape */
        public abstract int GetLeftMargin();

        /** Get the count of empty piece-grid columns on the right side of piece shape */
        public abstract int GetRightMargin();

        /** Get the count of empty piece-grid rows on the top side of piece shape */
        public abstract int GetTopMargin();

        /** Get the count of empty piece-grid rows on the bottom side of piece shape */
        public abstract int GetBottomMargin();

        /** Get piece orientation code */
        public abstract int GetOrientation();

        /** Get piece shape data */
        public abstract ShapeData GetShape();
    }
}
