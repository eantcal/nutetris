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

public interface Piece {
	public static final int ROWS = 4;
	public static final int COLS = 4;
	public static final int ORIENTATIONS = 4;

	/** Clones the piece returning a unique pointer to it*/
	public Piece clone();

	/** Sets column offset in order to center the piece within the row */
	public void move_center(int row_length);
	
	/** Increments game-grid related piece column offset */
	public void move_right();

	/** Decrements game-grid related piece column offset */
	public void move_left();

	/** Increments game-grid related piece row offset */
	public void move_down();

	/** Rotates the piece clockwise */
	public void rotate_cw();

	/** Rotates the piece anti-clockwise */
	public void rotate_acw();

	/** Undoes the last movement command */
	public void undo();

	/** Gets a color attribute at piece-grid coordinates col, row */
	public int get_at(int col, int row);

	/** Gets game-grid piece column offset */
	public int get_col();

	/** Gets game-grid piece row offset */
	public int get_row();

	/** Gets the count of empty piece-grid columns on the left side of piece shape */
	public int get_left_margin();

	/** Gets the count of empty piece-grid columns on the right side of piece shape */
	public int get_right_margin();

	/** Gets the count of empty piece-grid rows on the top side of piece shape */
	public int get_top_margin();

	/** Gets the count of empty piece-grid rows on the bottom side of piece shape */
	public int get_bottom_margin();

	/** Get piece orientation code */
	public int get_orientation();

	/** Gets piece shape data */
	public ShapeData get_shape();
}
