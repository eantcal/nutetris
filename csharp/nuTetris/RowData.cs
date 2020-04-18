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
    /**
     * Represents a row of a grid
     */
    public class RowData
    {
        private int[] data;

        public RowData(int cols)
        {
            Data = new int[cols];

            for (int i = 0; i < Data.Length; ++i)
            {
                Data[i] = 0;
            }
        }

        protected int[] Data { get => data; set => data = value; }

        public int[] get()
        {
            return Data;
        }

        public void set(int[] data)
        {
            for (int i = 0; i < this.Data.Length; ++i)
            {
                this.Data[i] = data[i];
            }
        }
    }
}
