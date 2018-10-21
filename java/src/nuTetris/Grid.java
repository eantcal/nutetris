/*
 *  This file is part of nuTetris
 *  Author: <antonino.calderone@gmail.com>
 *
 */

package nuTetris;

import java.util.HashSet;
import java.util.Set;

/** Implements Canvas and Game Board 
 * The Canvas shows a preview of next falling piece.
 * The Board is the game area where the pieces fall.
 */
public class Grid {

    protected GridData gridMap;

    /** Current piece object handle */
    private Piece currentPiece = null;

    /** Merge operation type */
    enum MergeType {
        MERGE_PUT, MERGE_REMOVE
    }

    /** Place-piece operation result type */
    enum PlaceSt {
        OK, CROSS_RIGHT_BOUNDARY, CROSS_LEFT_BOUNDARY, CROSS_TOP_BOUNDARY, NO_ROOM_FOR_PIECE, TOUCH_DOWN
    };

    /** Grid rows count */
    private int rows = 0;

    /** Grid columns count */
    private int cols = 0;

    Grid(int cols, int rows) {
        this.cols = cols;
        this.rows = rows;
        gridMap = new GridData(cols, rows);
    }

    /** Get columns count */
    public final int getColsCount() {
        return cols;
    }

    /** Get rows count */
    public final int getRowsCount() {
        return rows;
    }

    /** Get value of to a cell at coordinates x,y */
    int getAt(int x, int y) {
        RowData[] row = (RowData[]) gridMap.getData();
        return row[y].get()[x];
    }

    /** Clear the grid content */
    public void clear() {
        gridMap = new GridData(cols, rows);
    }

    /** Select new piece */
    public void setCurrentPiece(Piece piece) {
        currentPiece = piece;
    }

    /** Move selected piece to another grid */
    public void movePieceToGrid(Grid grid) {
        currentPiece.moveCenter(cols);
        grid.currentPiece = currentPiece;
        currentPiece = null;
    }

    /** Get a list of completed rows */
    public Set<Integer> getFullRows() {
        Set<Integer> s = new HashSet<Integer>();

        for (int i = 0; i < rows; ++i) {
            if (isFullRow(i))
                s.add(i);
        }

        return s;
    }

    /** Fill the cells of a row using a given color attribute */
    void fillRow(int rowIdx, int attr) {

        RowData rowdata = new RowData(cols);

        int[] val = new int[cols];

        for (int i = 0; i < cols; ++i) {
            val[i] = attr;
        }

        rowdata.set(val);

        gridMap.setRow(rowIdx, rowdata);
    }

    /** Remove full rows and compact the other cells */
    public void removeFullRows() {
        HashSet<Integer> full_rows = (HashSet<Integer>) getFullRows();

        GridData gridData = new GridData(cols, rows);

        int j = rows - 1;
        for (int i = rows - 1; i >= 0; --i) {
            if (!full_rows.contains(i)) {
                gridData.setRow(j, gridMap.getRow(i));
                --j;
            }
        }

        gridMap = gridData;
    }

    /** Place current piece onto the grid. */
    public PlaceSt placePiece() {
        return mergePiece(MergeType.MERGE_PUT);
    }

    /** Remove piece from the grid */
    public void removePiece() {
        mergePiece(MergeType.MERGE_REMOVE);
    }

    /** Get a reference to the current piece */
    Piece currentPiece() {
        return currentPiece;
    }

    /** Check if piece crosses the grid boundaries */
    protected PlaceSt checkBoundaries() {
        if (currentPiece == null)
            return PlaceSt.OK;

        Piece piece = currentPiece;

        int pieceX = piece.getCol();
        int pieceY = piece.getRow();

        // Check if piece crosses the grid borders
        if (pieceX + piece.getLeftMargin() < 0)
            return PlaceSt.CROSS_LEFT_BOUNDARY;

        if (pieceY + piece.getTopMargin() < 0)
            return PlaceSt.CROSS_TOP_BOUNDARY;

        if ((pieceX + Piece.COLS - piece.getRightMargin()) > getColsCount())
            return PlaceSt.CROSS_RIGHT_BOUNDARY;

        if ((pieceY + Piece.ROWS - piece.getBottomMargin()) > getRowsCount())
            return PlaceSt.TOUCH_DOWN;

        return PlaceSt.OK;
    }

    /** Merge the piece content (cells) in the grid */
    protected PlaceSt mergePiece(MergeType mode) {
        PlaceSt st = checkBoundaries();

        if (st != PlaceSt.OK)
            return st;

        Piece piece = currentPiece;

        int pieceX = piece.getCol();
        int pieceY = piece.getRow();

        // Copy cells data onto map_data in order to preserve it before merging
        GridData draftMap = gridMap.clone();

        for (int y = 0; y < Piece.ROWS; ++y) {
            for (int x = 0; x < Piece.COLS; ++x) {
                int gridCol = pieceX + x;
                int gridRow = pieceY + y;

                if (gridCol < 0 || gridCol >= getColsCount() || gridRow < 0 || gridRow >= getRowsCount()) {
                    continue;
                }

                int gridCell = draftMap.getRow(gridRow).get()[gridCol];
                int pieceCell = piece.getAt(x, y);

                if (mode == MergeType.MERGE_PUT) {
                    // In case of cell conflict, return TOUCH_DOWN or
                    // NO_ROOM_FOR_PIECE
                    // depending on top margin value
                    // (cells data modification will be not committed)
                    if (gridCell != 0 && pieceCell != 0) {
                        return (pieceY - piece.getTopMargin()) < 1 ? PlaceSt.NO_ROOM_FOR_PIECE : PlaceSt.TOUCH_DOWN;
                    }

                    // Copy piece (or delete) cell content into the draft data map
                    if (pieceCell != 0) {
                        draftMap.getRow(gridRow).get()[gridCol] = pieceCell;
                    }
                } else {
                    // Copy piece (or delete) cell content into the draft data
                    // map
                    if (pieceCell != 0) {
                        draftMap.getRow(gridRow).get()[gridCol] = 0;
                    }
                }
            }
        }

        // commit changes to the map data
        gridMap = draftMap;

        return PlaceSt.OK;
    }

    /** Return true if the row is full, false otherwise */
    private boolean isFullRow(int rowIdx) {
        boolean ret = true;
        int[] v = gridMap.getData()[rowIdx].get();

        for (int i = 0; i < v.length; ++i) {
            if (v[i] == 0) {
                ret = false;
                break;
            }
        }

        return ret;
    }

}
