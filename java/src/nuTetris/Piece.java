/*
 *  This file is part of nuTetris
 *  Author: <antonino.calderone@gmail.com>
 *
 */

package nuTetris;

/** Defines the interface of a falling piece */
public interface Piece {
    public static final int ROWS = 4;
    public static final int COLS = 4;
    public static final int ORIENTATIONS = 4;

    /** Clone the piece returning a unique pointer to it */
    public Piece clone();

    /** Set column offset to center the piece within the row */
    public void moveCenter(int rowLength);

    /** Increments game-grid related piece column offset */
    public void moveRight();

    /** Decrements game-grid related piece column offset */
    public void moveLeft();

    /** Increment game-grid related piece row offset */
    public void moveDown();

    /** Rotate the piece clockwise */
    public void rotateCw();

    /** Rotate the piece anti-clockwise */
    public void rotateAcw();

    /** Undo the last movement command */
    public void undo();

    /** Get a color attribute at piece-grid coordinates col, row */
    public int getAt(int col, int row);

    /** Get game-grid piece column offset */
    public int getCol();

    /** Get game-grid piece row offset */
    public int getRow();

    /** Get the count of empty piece-grid columns on the left side of piece shape */
    public int getLeftMargin();

    /** Get the count of empty piece-grid columns on the right side of piece shape */
    public int getRightMargin();

    /** Get the count of empty piece-grid rows on the top side of piece shape */
    public int getTopMargin();

    /** Get the count of empty piece-grid rows on the bottom side of piece shape */
    public int getBottomMargin();

    /** Get piece orientation code */
    public int getOrientation();

    /** Get piece shape data */
    public ShapeData getShape();
}
