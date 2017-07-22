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

import java.util.HashSet;
import java.util.Set;

public class Grid {

	protected GridData _grid_map;

	/** Current piece object handle */
	private Piece _current_piece = null;

	/** Merge operation type */
	enum merge_t {
		MERGE_PUT, MERGE_REMOVE
	}

	/** Place-piece operation result type */
	enum place_st_t {
		OK, CROSS_RIGHT_BOUNDARY, CROSS_LEFT_BOUNDARY, CROSS_TOP_BOUNDARY, NO_ROOM_FOR_PIECE, TOUCH_DOWN
	};

	/** Grid rows count */
	private int _rows = 0;

	/** Grid columns count */
	private int _cols = 0;

	Grid(int cols, int rows) {
		_cols = cols;
		_rows = rows;
		_grid_map = new GridData(cols, rows);
	}

	/** Gets columns count */
	public final int get_cols_count() {
		return _cols;
	}

	/** Gets rows count */
	public final int get_rows_count() {
		return _rows;
	}

	/** Gets a reference to the cell at coordinates x,y */
	int get_at(int x, int y) {
		RowData[] row = (RowData[]) _grid_map.get();
		return row[y].get()[x];
	}

	/** Clear the grid content */
	public void clear() {
		_grid_map = new GridData(_cols, _rows);
	}

	/** Select new piece */
	public void take_piece(Piece piece) {
		_current_piece = piece;
	}

	/** Gives the selected piece to other grid */
	public void give_piece(Grid grid) {
		_current_piece.move_center(_cols);
		grid._current_piece = _current_piece;
		_current_piece = null;
	}

	/** Gets a list of completed rows */
	public Set<Integer> get_full_rows() {
		Set<Integer> s = new HashSet<Integer>();

		for (int i = 0; i < _rows; ++i) {
			if (_is_full_row(i))
				s.add(i);
		}

		return s;
	}

	/** Fills the cells of a whole row using a given color attribute */
	void fill_row(int row_idx, int attr) {

		RowData rowdata = new RowData(_cols);

		int[] val = new int[_cols];

		for (int i = 0; i < _cols; ++i) {
			val[i] = attr;
		}

		rowdata.set(val);

		_grid_map.set_row(row_idx, rowdata);
	}

	/** Remove the completed rows, moving down the other cells */
	public void remove_full_rows() {
		HashSet<Integer> full_rows = (HashSet<Integer>) get_full_rows();

		GridData grid_data = new GridData(_cols, _rows);

		int j = _rows - 1;
		for (int i = _rows - 1; i >= 0; --i) {
			if (!full_rows.contains(i)) {
				grid_data.set_row(j, _grid_map.get_row(i));
				--j;
			}
		}

		_grid_map = grid_data;
	}

	/** Places current piece onto the grid. */
	public place_st_t place_piece() {
		return merge_piece(merge_t.MERGE_PUT);
	}

	/** Remove piece from the grid */
	public void remove_piece() {
		merge_piece(merge_t.MERGE_REMOVE);
	}

	/** Gets a reference to the current piece */
	Piece current_piece() {
		return _current_piece;
	}

	/** Checks if piece crosses the grid boundaries */
	protected place_st_t check_boundaries() {
		if (_current_piece == null)
			return place_st_t.OK;

		Piece piece = _current_piece;

		int piece_x = piece.get_col();
		int piece_y = piece.get_row();

		// Check if piece crosses the grid borders
		if (piece_x + piece.get_left_margin() < 0)
			return place_st_t.CROSS_LEFT_BOUNDARY;

		if (piece_y + piece.get_top_margin() < 0)
			return place_st_t.CROSS_TOP_BOUNDARY;

		if ((piece_x + Piece.COLS - piece.get_right_margin()) > get_cols_count())
			return place_st_t.CROSS_RIGHT_BOUNDARY;

		if ((piece_y + Piece.ROWS - piece.get_bottom_margin()) > get_rows_count())
			return place_st_t.TOUCH_DOWN;

		return place_st_t.OK;
	}

	/** Merges the piece cells in the grid */
	protected place_st_t merge_piece(merge_t mode) {
		place_st_t st = check_boundaries();

		if (st != place_st_t.OK)
			return st;

		Piece piece = _current_piece;

		int piece_x = piece.get_col();
		int piece_y = piece.get_row();

		// Copy cells data onto map_data in order to preserve it before merging
		GridData draft_map = _grid_map.clone();

		for (int y = 0; y < Piece.ROWS; ++y) {
			for (int x = 0; x < Piece.COLS; ++x) {
				int grid_col = piece_x + x;
				int grid_row = piece_y + y;

				if (grid_col < 0 || grid_col >= get_cols_count()
						|| grid_row < 0 || grid_row >= get_rows_count()) {
					continue;
				}

				int grid_cell = draft_map.get_row(grid_row).get()[grid_col];
				int piece_cell = piece.get_at(x, y);

				if (mode == merge_t.MERGE_PUT) {
					// In case of cell conflict, return TOUCH_DOWN or
					// NO_ROOM_FOR_PIECE
					// depending on top margin value
					// (cells data modification will be not committed)
					if (grid_cell != 0 && piece_cell != 0) {
						return (piece_y - piece.get_top_margin()) < 1 ? place_st_t.NO_ROOM_FOR_PIECE
								: place_st_t.TOUCH_DOWN;
					}

					// Copy piece (or delete) cell content into the draft data map
					if (piece_cell != 0) {
						draft_map.get_row(grid_row).get()[grid_col] = piece_cell;
					}
				} else {
					// Copy piece (or delete) cell content into the draft data
					// map
					if (piece_cell != 0) {
						draft_map.get_row(grid_row).get()[grid_col] = 0;
					}
				}
			}
		}

		// commit changes to the map data
		_grid_map = draft_map;

		return place_st_t.OK;
	}

	/** Returns true if a row is full
	    If empty flag is true, then it returns true if the row is empty
	    (any cell in the row has a null color attribute) **/
	private boolean _is_completed_row(int row_idx, boolean empty) {
		boolean ret = true;
		int[] v = _grid_map.get()[row_idx].get();

		for (int i = 0; i < v.length; ++i) {
			boolean test = v[i] == 0;

			if (!empty)
				test = !test;

			if (!test) {
				ret = false;
				break;
			}
		}

		return ret;
	}

	/** Returns true if the row is empty. @see _is_full_row() */
	private boolean _is_full_row(int row_idx) {
		return _is_completed_row(row_idx, false);
	}

}
