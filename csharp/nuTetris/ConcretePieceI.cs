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
    public class ConcretePieceI : ConcretePiece
    {
        private int color = 0;

        public ConcretePieceI(int c)
        {
            color = c;

            RowData[] data = Shape[0].getData();

            {
                int[] rowdata1 = { 0, 0, 0, 0 };
                int[] rowdata2 = { c, c, c, c };
                int[] rowdata3 = { 0, 0, 0, 0 };
                int[] rowdata4 = { 0, 0, 0, 0 };
                Shape[0].getData()[0].set(rowdata1);
                Shape[0].getData()[1].set(rowdata2);
                Shape[0].getData()[2].set(rowdata3);
                Shape[0].getData()[3].set(rowdata4);
            }

            data = Shape[1].getData();

            {
                int[] rowdata1 = { 0, 0, c, 0 };
                int[] rowdata2 = { 0, 0, c, 0 };
                int[] rowdata3 = { 0, 0, c, 0 };
                int[] rowdata4 = { 0, 0, c, 0 };
                Shape[0].getData()[0].set(rowdata1);
                Shape[0].getData()[1].set(rowdata2);
                Shape[0].getData()[2].set(rowdata3);
                Shape[0].getData()[3].set(rowdata4);
            }

            data = Shape[2].getData();

            {
                int[] rowdata1 = { 0, 0, 0, 0 };
                int[] rowdata2 = { c, c, c, c };
                int[] rowdata3 = { 0, 0, 0, 0 };
                int[] rowdata4 = { 0, 0, 0, 0 };
                Shape[0].getData()[0].set(rowdata1);
                Shape[0].getData()[1].set(rowdata2);
                Shape[0].getData()[2].set(rowdata3);
                Shape[0].getData()[3].set(rowdata4);
            }

            data = Shape[3].getData();

            {
                int[] rowdata1 = { 0, 0, c, 0 };
                int[] rowdata2 = { 0, 0, c, 0 };
                int[] rowdata3 = { 0, 0, c, 0 };
                int[] rowdata4 = { 0, 0, c, 0 };
                Shape[0].getData()[0].set(rowdata1);
                Shape[0].getData()[1].set(rowdata2);
                Shape[0].getData()[2].set(rowdata3);
                Shape[0].getData()[3].set(rowdata4);
            }

            computeMinBoundingBox();

        }

        public override Piece clone()
        {
            return new ConcretePieceI(color);
        }
    }
}
