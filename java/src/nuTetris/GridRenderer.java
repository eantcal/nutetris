/*
 *  This file is part of nuTetris
 *  Author: <antonino.calderone@gmail.com>
 *
 */

package nuTetris;

import java.awt.Color;
import java.awt.Graphics;

import javax.swing.JPanel;

/** Draws a game scene using grid data provided by Game Manager */
public class GridRenderer {

    private int xOffset = 0;
    private int yOffset = 0;
    private Grid grid;

    private int brickSize = 20;

    private static Color idx2color(int c) {
        if (c < 0) {
            return Color.WHITE;
        }

        switch (c) {
        case 0:
            return Color.BLACK;
        case 1:
            return Color.BLUE;
        case 2:
            return Color.CYAN;
        case 3:
            return Color.RED;
        case 4:
            return Color.PINK;
        case 5:
            return Color.GREEN;
        case 6:
            return Color.MAGENTA;
        case 7:
            return Color.ORANGE;
        }

        return Color.BLACK;
    }

    private class DrawPanel extends JPanel {
        private static final long serialVersionUID = 1L;

        public void paintComponent(Graphics g) {
            super.paintComponent(g);

            for (int y = 0; y < grid.getRowsCount(); ++y) {
                for (int x = 0; x < grid.getColsCount(); ++x) {
                    int col = grid.getAt(x, y);
                    g.setColor(idx2color(col));
                    g.fillRect(xOffset + x * brickSize, yOffset + y * brickSize, brickSize, brickSize);

                    g.setColor(col > 0 ? Color.DARK_GRAY : Color.BLACK);
                    g.drawRect(xOffset + x * brickSize, yOffset + y * brickSize, brickSize, brickSize);

                }
            }

        }
    }

    private DrawPanel drawPanel = null;

    public GridRenderer(Grid grid, int x, int y) {
        xOffset = x;
        yOffset = y;
        this.grid = grid;
    }

    public void update(JPanel panel) {
        if (drawPanel != null)
            panel.remove(drawPanel);

        drawPanel = new DrawPanel();
        panel.add(drawPanel);
    }
}
