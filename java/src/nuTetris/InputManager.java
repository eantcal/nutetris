/*
 *  This file is part of nuTetris
 *  Author: <antonino.calderone@gmail.com>
 *
 */

package nuTetris;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.Timer;
import java.util.TimerTask;

/** Collects and dispatches input events */
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
                    event = EventType.TIMERTICK;
                }
            }
        }, timerTick, timerTick);
    }

    @Override
    public void keyTyped(KeyEvent e) {
    }

    @Override
    public void keyPressed(KeyEvent e) {

        synchronized (lock) {

            switch (e.getKeyCode()) {
            case KeyEvent.VK_RIGHT:
                event = EventType.RIGHT;
                break;

            case KeyEvent.VK_LEFT:
                event = EventType.LEFT;
                break;

            case KeyEvent.VK_SPACE:
                event = EventType.SPACE;
                break;

            case KeyEvent.VK_UP:
                event = EventType.UP;
                break;

            case KeyEvent.VK_DOWN:
                event = EventType.DOWN;
                break;

            case KeyEvent.VK_ESCAPE:
                event = EventType.ESCAPE;
                break;

            case KeyEvent.VK_PAUSE:
                event = EventType.PAUSE;
                break;

            default:
                event = EventType.UNKNOWN;
                break;
            }
        }
    }

    @Override
    public void keyReleased(KeyEvent e) {
        // do nothing
    }

    public enum EventType {
        NONE, LEFT, RIGHT, DOWN, UP, SPACE, PAUSE, ESCAPE, TIMERTICK, UNKNOWN
    }

    private EventType event = EventType.NONE;
    private Timer timer = new Timer();

    /** Returns last event detected */
    public EventType poll() {
        EventType ev = EventType.NONE;

        // clear the pending event once read
        synchronized (lock) {
            ev = event;
            event = EventType.NONE;
        }

        return ev;
    }
}
