/*
 *  This file is part of nuTetris
 *  Author: <antonino.calderone@gmail.com>
 *
 */

package nuTetris;

public class ConcretePieceO extends ConcretePiece {
    private int color = 0;

    ConcretePieceO(int c) {
        color = c;

        RowData[] data;

        int[] rowdata1 = { 0, 0, 0, 0 };
        int[] rowdata2 = { 0, c, c, 0 };
        int[] rowdata3 = { 0, c, c, 0 };
        int[] rowdata4 = { 0, 0, 0, 0 };

        for (int rowidx = 0; rowidx < Piece.ROWS; ++rowidx) {

            data = shape[rowidx].getData();

            data[0].set(rowdata1);
            data[1].set(rowdata2);
            data[2].set(rowdata3);
            data[3].set(rowdata4);
        }

        computeMinBoundingBox();
    }

    @Override
    public Piece clone() {
        return new ConcretePieceO(color);
    }

}
