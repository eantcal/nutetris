using System;
using System.Windows.Forms;

namespace nuTetris
{
    public partial class MainForm : Form
    {
        static System.Windows.Forms.Timer myTimer = new System.Windows.Forms.Timer();
        const int TICK_COUNTER_RESET = 8;
        static int tickCounter = TICK_COUNTER_RESET;

        const int TICK_INTV = 20;

        private GameManager gm = null;

        public MainForm()
        {
            InitializeComponent();

            myTimer.Tick += new EventHandler(TimerEventProcessor);

            myTimer.Interval = TICK_INTV; // ms
            myTimer.Start();

            gm = new GameManager(this);
        }

        private void TimerEventProcessor(Object myObject, EventArgs myEventArgs)
        {
            myTimer.Stop();

            System.Drawing.Graphics formGraphics;
            formGraphics = this.CreateGraphics();

            if (tickCounter-- < 1)
            {
                gm.TimerTick();
                tickCounter = TICK_COUNTER_RESET;
            }

            gm.run(formGraphics);
            formGraphics.Dispose();

            myTimer.Enabled = true;
        }


        protected override void OnPaint(System.Windows.Forms.PaintEventArgs e)
        {
            System.Drawing.Graphics formGraphics;
            formGraphics = this.CreateGraphics();
            gm.RenderScene(formGraphics);
            formGraphics.Dispose();
        }

        private void MainForm_KeyDown(object sender, KeyEventArgs e)
        {
            gm.inputMgr.processInput(e);
        }
    }
}
