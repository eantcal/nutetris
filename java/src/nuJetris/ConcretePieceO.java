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

public class ConcretePieceO extends ConcretePiece {
	private int _color = 0;
	
	ConcretePieceO(int c) {
		_color = c;
		
		RowData[] data;

		int[] rowdata1 = { 0, 0, 0, 0 };
		int[] rowdata2 = { 0, c, c, 0 };
		int[] rowdata3 = { 0, c, c, 0 };
		int[] rowdata4 = { 0, 0, 0, 0 };

		for (int rowidx = 0; rowidx < Piece.ROWS; ++rowidx) {

			data = _shape[rowidx].get();

			data[0].set(rowdata1);
			data[1].set(rowdata2);
			data[2].set(rowdata3);
			data[3].set(rowdata4);
		}

		compute_min_bounding_box();
	}
	
	@Override
	public Piece clone() {
		return new ConcretePieceO(_color);
	}

}
