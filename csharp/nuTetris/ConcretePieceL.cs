﻿/*
 *  This file is part of nuTetris
 *  Author: <antonino.calderone@gmail.com>
 *
 */

namespace nuTetris
{
    public class ConcretePieceL : ConcretePiece
    {
        private readonly int color = 0;

        public ConcretePieceL(int c)
        {
            color = c;

            RowData[] data = Shape[0].GetData();

            {
                int[] rowdata1 = { 0, 0, 0, 0 };
                int[] rowdata2 = { 0, c, c, c };
                int[] rowdata3 = { 0, c, 0, 0 };
                int[] rowdata4 = { 0, 0, 0, 0 };

                data[0].Set(rowdata1);
                data[1].Set(rowdata2);
                data[2].Set(rowdata3);
                data[3].Set(rowdata4);
            }

            data = Shape[1].GetData();

            {
                int[] rowdata1 = { 0, 0, c, 0 };
                int[] rowdata2 = { 0, 0, c, 0 };
                int[] rowdata3 = { 0, 0, c, c };
                int[] rowdata4 = { 0, 0, 0, 0 };

                data[0].Set(rowdata1);
                data[1].Set(rowdata2);
                data[2].Set(rowdata3);
                data[3].Set(rowdata4);
            }

            data = Shape[2].GetData();

            {
                int[] rowdata1 = { 0, 0, 0, c };
                int[] rowdata2 = { 0, c, c, c };
                int[] rowdata3 = { 0, 0, 0, 0 };
                int[] rowdata4 = { 0, 0, 0, 0 };

                data[0].Set(rowdata1);
                data[1].Set(rowdata2);
                data[2].Set(rowdata3);
                data[3].Set(rowdata4);
            }

            data = Shape[3].GetData();

            {
                int[] rowdata1 = { 0, c, c, 0 };
                int[] rowdata2 = { 0, 0, c, 0 };
                int[] rowdata3 = { 0, 0, c, 0 };
                int[] rowdata4 = { 0, 0, 0, 0 };

                data[0].Set(rowdata1);
                data[1].Set(rowdata2);
                data[2].Set(rowdata3);
                data[3].Set(rowdata4);
            }

            computeMinBoundingBox();

        }

        public override Piece Clone()
        {
            return new ConcretePieceL(color);
        }
    }
}
