using System.Windows.Forms;

namespace nuTetris
{
    /** Collects and dispatches input events */
    public class InputManager
    {
        public enum EventType
        {
            NONE, LEFT, RIGHT, DOWN, UP, SPACE, PAUSE, ESCAPE, TIMERTICK, UNKNOWN
        }

        private EventType _event;

        public InputManager()
        {
        }

        // private Timer timer = new Timer();
        public void processInput(KeyEventArgs e)
        {
            _event = EventType.UNKNOWN;

            switch (e.KeyCode)
            {
                case Keys.Right:
                    _event = EventType.RIGHT;
                    e.SuppressKeyPress = true;
                    break;

                case Keys.Left:
                    _event = EventType.LEFT;
                    e.SuppressKeyPress = true;
                    break;

                case Keys.Space:
                    _event = EventType.SPACE;
                    e.SuppressKeyPress = true;
                    break;

                case Keys.Up:
                    _event = EventType.UP;
                    e.SuppressKeyPress = true;
                    break;

                case Keys.Down:
                    _event = EventType.DOWN;
                    e.SuppressKeyPress = true;
                    break;

                case Keys.Escape:
                    _event = EventType.ESCAPE;
                    e.SuppressKeyPress = true;
                    break;

                case Keys.Pause:
                    _event = EventType.PAUSE;
                    e.SuppressKeyPress = true;
                    break;

                default:
                    _event = EventType.UNKNOWN;
                    break;
            }
        }

        private readonly object syncLock = new object();

        /** Returns last event detected */
        public EventType poll()
        {
            EventType ev = EventType.NONE;

            // clear the pending event once read
            lock (syncLock)
            {
                ev = _event;
                _event = EventType.NONE;
            }

            return ev;
        }


        public void tick()
        {
            lock (syncLock)
            {
                _event = EventType.TIMERTICK;
            }
        }
    }

}

