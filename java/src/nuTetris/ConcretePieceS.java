/*
 *  This file is part of nuTetris
 *  Author: <antonino.calderone@gmail.com>
 *
 */

package nuTetris;

public class ConcretePieceS extends ConcretePiece {
    private int color = 0;

    ConcretePieceS(int c) {
        color = c;

        RowData[] data = shape[0].getData();

        {
            int[] rowdata1 = { 0, 0, 0, 0 };
            int[] rowdata2 = { 0, 0, c, c };
            int[] rowdata3 = { 0, c, c, 0 };
            int[] rowdata4 = { 0, 0, 0, 0 };

            data[0].set(rowdata1);
            data[1].set(rowdata2);
            data[2].set(rowdata3);
            data[3].set(rowdata4);
        }

        data = shape[1].getData();

        {
            int[] rowdata1 = { 0, 0, c, 0 };
            int[] rowdata2 = { 0, 0, c, c };
            int[] rowdata3 = { 0, 0, 0, c };
            int[] rowdata4 = { 0, 0, 0, 0 };

            data[0].set(rowdata1);
            data[1].set(rowdata2);
            data[2].set(rowdata3);
            data[3].set(rowdata4);
        }

        data = shape[2].getData();

        {
            int[] rowdata1 = { 0, 0, 0, 0 };
            int[] rowdata2 = { 0, 0, c, c };
            int[] rowdata3 = { 0, c, c, 0 };
            int[] rowdata4 = { 0, 0, 0, 0 };

            data[0].set(rowdata1);
            data[1].set(rowdata2);
            data[2].set(rowdata3);
            data[3].set(rowdata4);
        }

        data = shape[3].getData();

        {
            int[] rowdata1 = { 0, 0, c, 0 };
            int[] rowdata2 = { 0, 0, c, c };
            int[] rowdata3 = { 0, 0, 0, c };
            int[] rowdata4 = { 0, 0, 0, 0 };

            data[0].set(rowdata1);
            data[1].set(rowdata2);
            data[2].set(rowdata3);
            data[3].set(rowdata4);
        }

        computeMinBoundingBox();

    }

    @Override
    public Piece clone() {
        return new ConcretePieceS(color);
    }
}
