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

import java.awt.Font;
import java.awt.GridLayout;
import java.util.Random;
import java.util.Set;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import nuJetris.Grid.place_st_t;

public class GameManager {

	/** Game states */
	enum game_state_t {
		BEGIN, PLAYING, GAMEOVER
	};

	/** Game input events */
	public enum input_t {
		NONE, MOVE_RIGHT, MOVE_LEFT, MOVE_DOWN, ROTATE_CW, ROTATE_ACW, DROP_PIECE, EXIT, PAUSE_GAME
	};

	/** Default game area columns */
	private final static int DEF_COLS = 10;

	/** Default game area rows */
	private final static int DEF_ROWS = 20;

	/** Default game area width */
	private final static int DEF_XRES = 640;

	/** Default game area height */
	private final static int DEF_YRES = 480;

	/** Initial falling idle timeout (milliseconds) */
	private final static int FALLING_IDLE_INTV = 1000;

	/** 'Full-row blink' delay */
	private final static int FULL_ROW_BLNK_DL = 250;

	/** Score order of magnitude */
	private final static int FULL_ROW_SCORE_ODM = 10;

	protected GameManager(int def_cols, int def_rows,
			int full_row_blik_dalay_ms, int def_xres, int def_yres) {

		_game_grid = new Grid(def_cols, def_rows);
		_fullrow_blink_dalay_ms = full_row_blik_dalay_ms;
		_gridRenderer = new GridRenderer(_game_grid, 0, 0);
		_canvasRenderer = new GridRenderer(_preview_canvas, 0, 0);

		_frame = new JFrame("Jetris");
		_main_panel = new JPanel(new GridLayout(1, 3));
		_frame.add(_main_panel);

		_score_panel = new JPanel();

		_score_label = new JLabel("Score:");
		_score_label.setFont(new Font("Verdana", 1, 14));
		_score_panel.add(_score_label);

		_main_panel.add(_score_panel);

		_frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		_frame.setSize(def_xres, def_yres);

		_frame.addKeyListener(_input_mgr);
	}

	public GameManager() {
		this(DEF_COLS, DEF_ROWS, FULL_ROW_BLNK_DL, DEF_XRES, DEF_YRES);
	}

	/** Redraw the scene */
	public void render_scene() {

		String score = "Score:" + String.valueOf(_score);

		_score_label.setText(score);

		_gridRenderer.update(_main_panel);
		_canvasRenderer.update(_main_panel);

		if (_frame.isVisible()) {
			_frame.invalidate();
			_frame.validate();
			_frame.repaint();
		} else {
			_frame.setVisible(true);
		}

		try {
			Thread.sleep(_piece_dropped ? 10 : 100);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	/** Revert to previous piece position / orientation */
	public void undo_move_piece() {
		_game_grid.current_piece().undo();
		_game_grid.place_piece();
	}

	/** Take a new piece from catalog */
	public void select_new_piece() {
		_preview_canvas.give_piece(_game_grid);
		
		int catalog_size = _pfactory.get_piece_catalog_size();

		_preview_canvas.take_piece(_pfactory.make(_randomGenerator
				.nextInt(catalog_size)));

		_preview_canvas.clear();
		_preview_canvas.place_piece();
	}

	/** Acknowledge last input event */
	public void ack_input_event() {
		_input = input_t.NONE;
	}

	/** Remove the piece from the game area */
	void clean_piece() {
		_game_grid.remove_piece();
	}

	/** Process any new input event */
	void process_input() {
		InputManager.event_t ev = _input_mgr.poll();

		switch (ev) {
		case DOWN:
			_input = input_t.ROTATE_ACW;
			break;
		case ESCAPE:
			break;
		case LEFT:
			_input = input_t.MOVE_LEFT;
			break;
		case RIGHT:
			_input = input_t.MOVE_RIGHT;
			break;
		case SPACE:
			_piece_dropped = true;
			_input = input_t.MOVE_DOWN;
			break;
		case TIMERTICK:
			_input = input_t.MOVE_DOWN;
			break;
		case UNKNOWN:
			break;
		case UP:
			_input = input_t.ROTATE_CW;
			break;
		default:
			_input = input_t.NONE;
			break;
		}

	}

	// ! Returns and acknowledges last input event
	public input_t get_input() {
		input_t input = _input;
		_input = input_t.NONE;
		return input;
	}

	/**
	 * Set / reset _piece_dropped state which causes a series of move down event
	 * in order to speed up piece falling
	 */
	public void drop_piece(boolean st) {
		_piece_dropped = st;

		if (!st)
			ack_input_event();
	}

	/** Gets a list of completed rows */
	public Set<Integer> get_full_rows() {
		return _game_grid.get_full_rows();
	}

	/** Fills the cells of a whole row using a given color attribute */
	public void fill_row(int row_idx, int attr) {
		_game_grid.fill_row(row_idx, attr);
	}

	/** Remove the completed rows, moving down the other cells */
	public void remove_full_rows() {
		_game_grid.remove_full_rows();
	}

	/** Processes an input and handles it ! if it is related to piece movement */
	public input_t handle_piece_movements() {

		input_t input = get_input();

		// Check if no other input is present then
		// if the piece is released create MOVE_DOWN event
		if (_piece_dropped && input == input_t.NONE)
			input = input_t.MOVE_DOWN;

		switch (input) {
		case MOVE_RIGHT:
			_game_grid.current_piece().move_right();
			break;

		case MOVE_LEFT:
			_game_grid.current_piece().move_left();
			break;

		case MOVE_DOWN:
			_game_grid.current_piece().move_down();
			break;

		case ROTATE_CW:
			_game_grid.current_piece().rotate_cw();
			break;

		case ROTATE_ACW:
			_game_grid.current_piece().rotate_acw();
			break;

		case DROP_PIECE:
			drop_piece(true);
			break;
		default:
			break;
		}

		return input;
	}

	/** Called on PLAYING state */
	public void play() {
		// Input is processed using chain-of-responsibility pattern
		input_t input = handle_piece_movements();

		switch (input) {
		case NONE:
			process_input();
			return;

		case EXIT:
			break;

		case PAUSE_GAME:
			break;

		default:
			break;
		}

		place_st_t place_status = _game_grid.place_piece();
		Set<Integer> full_rows;

		switch (place_status) {
		case NO_ROOM_FOR_PIECE:
			// Game over
			_game_st = game_state_t.GAMEOVER;
			break;

		case TOUCH_DOWN:
			// Revert to last (valid) position
			undo_move_piece();

			// Get the full rows list
			full_rows = get_full_rows();

			if (!full_rows.isEmpty()) {
				int score_k = 1;

				for (int row : full_rows) {
					fill_row(row, -1);
					score_k *= 2;
				}

				_score += score_k * FULL_ROW_SCORE_ODM;
			}

			ack_input_event();

			render_scene();
			select_new_piece();

			try {
				Thread.sleep(_fullrow_blink_dalay_ms);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

			remove_full_rows();
			render_scene();

			// Turn-off release mode
			drop_piece(false);

			return;

		default:
			if (place_status != place_st_t.OK)
				undo_move_piece();

			render_scene();

			// Clean the piece from game area
			clean_piece();
			process_input();
		}
	}

	/** Called on BEING state */
	public void setup() {
		set_idle_intv(_falling_idle_intv);

		_game_grid.clear();
		_preview_canvas.clear();

		int catalog_size = _pfactory.get_piece_catalog_size();

		_game_grid.take_piece(_pfactory.make(_randomGenerator
				.nextInt(catalog_size)));

		_game_grid.current_piece().move_center(_game_grid.get_cols_count());
		
		_preview_canvas.take_piece(_pfactory.make(_randomGenerator
				.nextInt(catalog_size)));

		_preview_canvas.place_piece();

		drop_piece(false);

		_game_st = game_state_t.PLAYING;
	}

	/** Called on GAMEOVER state */
	public void game_over() {
		// Input is processed using chain-of-responsibility pattern
		input_t input = get_input();

		render_scene();

		if (input == input_t.EXIT)
			_game_st = game_state_t.BEGIN;

		process_input();

		String title = "Game Over";
		String message = "Do you want to restart ?";

		int reply = JOptionPane.showConfirmDialog(null, message, title,
				JOptionPane.YES_NO_OPTION);

		if (reply != JOptionPane.YES_OPTION)
		{
			 JOptionPane.showMessageDialog(null, "GOODBYE");
	         System.exit(0);
		}
		else
		{
			_game_st = game_state_t.BEGIN;
		}

	}

	/** Updates falling timer interval */
	public void set_idle_intv(int intv) {
		_input_mgr.changeTick(intv);
	}

	/** Runs the game */
	public void run() {
		switch (_game_st) {
		case BEGIN:
			setup();
			break;

		case PLAYING:
			play();
			break;

		case GAMEOVER:
			game_over();
			break;
		}
	}

	private int _fullrow_blink_dalay_ms = FULL_ROW_BLNK_DL;

	/** Reference to piece factory class */
	private PieceFactory _pfactory = new PieceFactory();

	/** Reference to input manager */
	private InputManager _input_mgr = new InputManager(FALLING_IDLE_INTV);

	/** Preview canvas */
	private Grid _preview_canvas = new Grid(Piece.COLS, Piece.ROWS);

	/** Game grid instance */
	private Grid _game_grid = new Grid(DEF_COLS, DEF_ROWS);

	/** Last input event */
	private input_t _input = input_t.NONE;

	/** Falling idle timeout (determines the speed of the game) */
	private int _falling_idle_intv = FALLING_IDLE_INTV;

	/** Set to speed up falling of dropped piece */
	boolean _piece_dropped = false;

	private long _score = 0;

	private Random _randomGenerator = new Random();

	GridRenderer _gridRenderer;
	GridRenderer _canvasRenderer;

	/** Holds current game status */
	private game_state_t _game_st = game_state_t.BEGIN;

	private JFrame _frame;
	private JPanel _main_panel;
	private JPanel _score_panel;
	private JLabel _score_label;
}
