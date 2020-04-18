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
                data = Shape[rowidx].getData();

                data[0].set(rowdata1);
                data[1].set(rowdata2);
                data[2].set(rowdata3);
                data[3].set(rowdata4);
            }

            computeMinBoundingBox();

        }

        public override Piece clone()
        {
            return new ConcretePieceO(color);
        }
    }
}
