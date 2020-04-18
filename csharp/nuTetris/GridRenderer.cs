/*
 *  This file is part of nuTetris
 *  Author: <antonino.calderone@gmail.com>
 *
 */

using System.Drawing;

namespace nuTetris
{
    /** Draws a game scene using grid data provided by Game Manager */
    public class GridRenderer
    {
        private readonly int xOffset = 0;
        private readonly int yOffset = 0;
        private readonly Grid grid;
        private readonly bool drawBorder = false;
        private readonly int brickSize = 20;


        private static System.Drawing.Color idx2color(int c)
        {
            if (c < 0)
                return System.Drawing.Color.White;

            switch (c)
            {
                case 0:
                    return System.Drawing.Color.Black;
                case 1:
                    return System.Drawing.Color.Blue;
                case 2:
                    return System.Drawing.Color.Cyan;
                case 3:
                    return System.Drawing.Color.Red;
                case 4:
                    return System.Drawing.Color.Pink;
                case 5:
                    return System.Drawing.Color.Green;
                case 6:
                    return System.Drawing.Color.Magenta;
                case 7:
                    return System.Drawing.Color.Orange;
            }

            return System.Drawing.Color.Black;
        }

        public void update(System.Drawing.Graphics g)
        {
            // super.paintComponent(g);

            for (int y = 0; y < grid.RowsCount; ++y)
            {
                for (int x = 0; x < grid.ColsCount; ++x)
                {
                    int col = grid.GetAt(x, y);

                    System.Drawing.SolidBrush myBrush =
                        new System.Drawing.SolidBrush(idx2color(col));

                    g.FillRectangle(myBrush,
                        new Rectangle(xOffset + x * brickSize,
                                      yOffset + y * brickSize,
                                      brickSize, brickSize));

                    System.Drawing.Pen myPen = new System.Drawing.Pen(
                        col > 0 ? System.Drawing.Color.DarkGray : System.Drawing.Color.Black);

                    g.DrawRectangle(myPen,
                        new Rectangle(xOffset + x * brickSize,
                                      yOffset + y * brickSize,
                                      brickSize, brickSize));

                    myBrush.Dispose();
                    myPen.Dispose();
                }
            }

            if (drawBorder)
            {
                System.Drawing.Pen newPen = new System.Drawing.Pen(
                            System.Drawing.Color.DarkGray);

                g.DrawRectangle(newPen,
                    new Rectangle(xOffset - 1,
                                  yOffset - 1,
                                  brickSize * grid.ColsCount + 2,
                                  brickSize * grid.RowsCount + 2));

                newPen.Dispose();
            }
        }


        public GridRenderer(Grid grid, int x, int y, bool drawBoarder, int brickSize)
        {
            xOffset = x;
            yOffset = y;
            this.grid = grid;
            this.drawBorder = drawBoarder;
            this.brickSize = brickSize;
        }

    }
}
