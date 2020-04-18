/*
 *  This file is part of nuTetris
 *  Author: <antonino.calderone@gmail.com>
 *
 */

namespace nuTetris
{
    public class ConcretePieceO : ConcretePiece
    {
        private readonly int color = 0;

        public ConcretePieceO(int c)
        {
            color = c;

            RowData[] data;

            int[] rowdata1 = { 0, 0, 0, 0 };
            int[] rowdata2 = { 0, c, c, 0 };
            int[] rowdata3 = { 0, c, c, 0 };
            int[] rowdata4 = { 0, 0, 0, 0 };

            for (int rowidx = 0; rowidx < Piece.ROWS; ++rowidx)
            {
                data = Shape[rowidx].GetData();

                data[0].Set(rowdata1);
                data[1].Set(rowdata2);
                data[2].Set(rowdata3);
                data[3].Set(rowdata4);
            }

            computeMinBoundingBox();

        }

        public override Piece Clone()
        {
            return new ConcretePieceO(color);
        }
    }
}
