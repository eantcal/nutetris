/*
 *  This file is part of nuTetris
 *  Author: <antonino.calderone@gmail.com>
 *
 */

package nuTetris;

/**
 * Represents a row of a grid
 */
public class RowData {

    protected int[] data;

    RowData(int cols) {
        data = new int[cols];

        for (int i = 0; i < data.length; ++i) {
            data[i] = 0;
        }
    }

    public int[] get() {
        return data;
    }

    public void set(int[] data) {
        for (int i = 0; i < this.data.length; ++i) {
            this.data[i] = data[i];
        }
    }

}
