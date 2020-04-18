/*
 *  This file is part of nuTetris
 *  Author: <antonino.calderone@gmail.com>
 *
 */

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

        public RowData[] GetData() => data;

        public void SetRow(int rowindex, RowData rowdata)
        {
            if (rowindex >= 0 && rowindex < data.Length)
            {
                data[rowindex] = rowdata;
            }
        }

        public GridData Clone()
        {
            GridData obj = new GridData(cols, rows);

            for (int rowIdx = 0; rowIdx < rows; ++rowIdx)
            {
                RowData row = new RowData(cols);
                row.set(data[rowIdx].get());
                obj.SetRow(rowIdx, row);
            }

            return obj;
        }

        public RowData GetRow(int rowIdx) => data[rowIdx];

        public void SetData(RowData[] data)
        {
            this.data = data;
        }
    }
}
