/*
 *  This file is part of nuTetris
 *  Author: <antonino.calderone@gmail.com>
 *
 */

package nuTetris;

/** Holds grid data used by renderer to draw the scene */
public class GridData {
    protected RowData[] data;
    private int rows = 0;
    private int cols = 0;

    GridData(int cols, int rows) {
        this.cols = cols;
        this.rows = rows;

        data = new RowData[rows];

        for (int i = 0; i < data.length; ++i) {
            data[i] = new RowData(cols);
        }
    }

    public RowData[] getData() {
        return data;
    }

    public void setRow(int rowindex, RowData rowdata) {
        if (rowindex >= 0 && rowindex < data.length) {
            data[rowindex] = rowdata;
        }
    }

    public GridData clone() {
        GridData obj = new GridData(cols, rows);

        for (int rowIdx = 0; rowIdx < rows; ++rowIdx) {
            RowData row = new RowData(cols);
            row.set(data[rowIdx].data);
            obj.setRow(rowIdx, row);
        }

        return obj;
    }

    public RowData getRow(int rowIdx) {
        return data[rowIdx];
    }

    public void setData(RowData[] data) {
        this.data = data;
    }

}
