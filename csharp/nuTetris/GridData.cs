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
    /** Holds grid data used by renderer to draw the scene */
    public class GridData
    {
        protected RowData[] data;
        private readonly int rows = 0;
        private readonly int cols = 0;

        public GridData(int cols, int rows)
        {
            this.cols = cols;
            this.rows = rows;

            data = new RowData[rows];

            for (int i = 0; i < data.Length; ++i)
            {
                data[i] = new RowData(cols);
            }
        }

        public RowData[] getData() => data;

        public void setRow(int rowindex, RowData rowdata)
        {
            if (rowindex >= 0 && rowindex < data.Length)
            {
                data[rowindex] = rowdata;
            }
        }

        public GridData clone()
        {
            GridData obj = new GridData(cols, rows);

            for (int rowIdx = 0; rowIdx < rows; ++rowIdx)
            {
                RowData row = new RowData(cols);
                row.set(data[rowIdx].get());
                obj.setRow(rowIdx, row);
            }

            return obj;
        }

        public RowData getRow(int rowIdx) => data[rowIdx];

        public void setData(RowData[] data)
        {
            this.data = data;
        }
    }
}
