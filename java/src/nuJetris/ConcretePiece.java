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

import nuJetris.Piece;

public class ConcretePiece implements Piece {

	protected class Data {
		int _pos_x = 0;
		int _pos_y = 0;
		int _orientation = 0;
		int _left_margin = 0;
		int _right_margin = 0;
		int _top_margin = 0;
		int _bottom_margin = 0;

		void copy_from(Data data) {
			_pos_x = data._pos_x;
			_pos_y = data._pos_y;
			_orientation = data._orientation;
			_left_margin = data._left_margin;
			_right_margin = data._right_margin;
			_top_margin = data._top_margin;
			_bottom_margin = data._bottom_margin;
		}
	}

	protected Data _data;
	protected Data _undo_data;
	protected ShapeData[] _shape;

	ConcretePiece() {
		_data = new Data();
		_undo_data = new Data();
		_shape = new ShapeData[Piece.ORIENTATIONS];

		for (int i = 0; i < _shape.length; ++i) {
			_shape[i] = new ShapeData();
		}
	}

	@Override
	public Piece clone() {
		return new ConcretePiece();
	}

	@Override
	public void move_right() {
		_undo_data.copy_from(_data);
		++_data._pos_x;
	}

	@Override
	public void move_left() {
		_undo_data.copy_from(_data);
		--_data._pos_x;
	}

	@Override
	public void move_down() {
		_undo_data.copy_from(_data);
		++_data._pos_y;
	}

	@Override
	public void rotate_cw() {
		_undo_data.copy_from(_data);
		++_data._orientation;

		if (_data._orientation >= ORIENTATIONS)
			_data._orientation = 0;

		compute_min_bounding_box();
	}

	protected void compute_min_bounding_box() {
		if (_shape.length == 0)
			return;

		ShapeData block = _shape[get_orientation()];

		int min_x = -1;
		int max_x = -1;
		int min_y = -1;
		int max_y = -1;

		int x = 0;
		int y = 0;

		for (RowData row : block.get()) {
			x = 0;

			for (int cell : row.get()) {
				if (cell != 0) {
					if (min_x == -1 || x < min_x)
						min_x = x;

					if (min_y == -1 || y < min_y)
						min_y = y;

					if (max_x == -1 || x > max_x)
						max_x = x;

					if (max_y == -1 || y > max_y)
						max_y = y;
				}

				++x;
			}

			++y;
		}

		_data._left_margin = min_x;
		_data._right_margin = Piece.COLS - max_x - 1;
		_data._top_margin = min_y;
		_data._bottom_margin = Piece.ROWS - max_y - 1;

	}

	@Override
	public void rotate_acw() {
		_undo_data.copy_from(_data);

		--_data._orientation;

		if (_data._orientation < 0)
			_data._orientation = ORIENTATIONS - 1;

		compute_min_bounding_box();
	}

	@Override
	public void undo() {
		_data.copy_from(_undo_data);
	}

	@Override
	public int get_at(int col, int row) {
		ShapeData block = _shape[get_orientation()];
		RowData row_data = block.get_row(row);
		return row_data.get()[col];
	}

	@Override
	public int get_col() {
		return _data._pos_x;
	}

	@Override
	public int get_row() {
		return _data._pos_y;
	}

	@Override
	public int get_left_margin() {
		return _data._left_margin;
	}

	@Override
	public int get_right_margin() {
		return _data._right_margin;
	}

	@Override
	public int get_top_margin() {
		return _data._top_margin;
	}

	@Override
	public int get_bottom_margin() {
		return _data._bottom_margin;
	}

	@Override
	public int get_orientation() {
		return _data._orientation;
	}

	@Override
	public ShapeData get_shape() {
		return _shape[_data._orientation];
	}

	@Override
	public void move_center(int row_length) {
		_data._pos_x = (row_length + (Piece.COLS - _data._left_margin
				- _data._right_margin))/2;
	}
}
