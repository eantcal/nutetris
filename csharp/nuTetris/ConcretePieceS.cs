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
    public class ConcretePieceS : ConcretePiece
    {
        private readonly int color = 0;

        public ConcretePieceS(int c)
        {
            color = c;

            RowData[] data = Shape[0].getData();

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

            data = Shape[1].getData();

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

            data = Shape[2].getData();

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

            data = Shape[3].getData();

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

        public override Piece clone()
        {
            return new ConcretePieceS(color);
        }
    }
}
