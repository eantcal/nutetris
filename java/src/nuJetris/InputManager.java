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

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.Timer;
import java.util.TimerTask;

public class InputManager implements KeyListener {

	private final Object lock = new Object();

	InputManager(int timerTick) {
		changeTick(timerTick);
	}

	public void changeTick(int timerTick) {
		
		timer.purge();
		
		timer.scheduleAtFixedRate(new TimerTask() {
			@Override
			public void run() {
				synchronized (lock) {
					_event = event_t.TIMERTICK;
				}
			}
		}, timerTick, timerTick);
	}

	@Override
	public void keyTyped(KeyEvent e) {
	}

	@Override
	public void keyPressed(KeyEvent e) {
		String event = KeyEvent.getKeyText(e.getKeyCode());
		
		synchronized (lock) {

			switch (event) {
			case "Right":
				_event = event_t.RIGHT;
				break;

			case "Left":
				_event = event_t.LEFT;
				break;

			case "Space":
				_event = event_t.SPACE;
				break;

			case "Up":
				_event = event_t.UP;
				break;

			case "Down":
				_event = event_t.DOWN;
				break;

			case "Escape":
				_event = event_t.ESCAPE;
				break;

			case "Pause":
				_event = event_t.PAUSE;
				break;

			default:
				_event = event_t.UNKNOWN;
				break;
			}
		}
	}

	@Override
	public void keyReleased(KeyEvent e) {
		_event = event_t.NONE;
	}

	public enum event_t {
		NONE, LEFT, RIGHT, DOWN, UP, SPACE, PAUSE, ESCAPE, TIMERTICK, UNKNOWN
	}

	private event_t _event = event_t.NONE;
	private Timer timer = new Timer();
	

	/** Returns last event detected */
	public event_t poll() {
		event_t ev = event_t.NONE;
		
		synchronized (lock) {
			ev = _event;
			_event = event_t.NONE;
		}
		
		return ev;
	}
}
