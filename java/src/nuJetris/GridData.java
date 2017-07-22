/*
 *  This file is part of nuJetris
 *
 *  nuTetris is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  nuTetris is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with nuTetris; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  US
 *
 *  Author: <antonino.calderone@ericsson.com>, <acaldmail@gmail.com>
 *
 */

package nuJetris;

public class GridData 
{
	protected RowData[] data;
	
	private int rows = 0;
	private int cols = 0;
			
	GridData(int cols, int rows)
	{		
		this.cols = cols;
		this.rows = rows;
		
		data = new RowData[rows];
		for (int i = 0; i<data.length; ++i)
		{
			data[i] = new RowData(cols);
		}
	}
	
	
	public RowData[] get()
	{
		return data;
	}

	
	public void set_row(int rowindex, RowData rowdata) {
		if (rowindex >= 0 && 
			rowindex<data.length)
		{
			data[rowindex] = rowdata;
		}
	}

	public GridData clone()
	{
		GridData obj = new GridData(cols, rows);
		
		for (int row_idx = 0; row_idx < rows; ++row_idx)
		{
			RowData row = new RowData(cols);			
			row.set(data[row_idx].data);
			obj.set_row(row_idx, row);
		}
		
		return obj;
	}
	
	public RowData get_row(int rowindex) {
		return data[rowindex];
	}

	
	public void set(RowData[] data) {	
		this.data = data;
	}


}
