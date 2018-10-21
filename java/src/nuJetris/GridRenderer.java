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
 *  Author: <antonino.calderone@gmail.com>
 *
 */

package nuJetris;

import java.awt.Color;
import java.awt.Graphics;

import javax.swing.JPanel;

public class GridRenderer {

   private int _x_offset = 0;
   private int _y_offset = 0;
   private Grid _grid;

   private int _brick_size = 20;

   private static Color _idx2color(int c) {
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

         for (int y = 0; y < _grid.get_rows_count(); ++y) {
             for (int x = 0; x < _grid.get_cols_count(); ++x) {
                 int col = _grid.get_at(x, y);
                 g.setColor(_idx2color(col));
                 g.fillRect(_x_offset + x * _brick_size, _y_offset + y
                         * _brick_size, _brick_size, _brick_size);

                 
                 g.setColor(col > 0 ? Color.DARK_GRAY : Color.BLACK);
                 g.drawRect(_x_offset + x * _brick_size, _y_offset + y
                             * _brick_size, _brick_size, _brick_size);
                 
             }
         }

      }
   }

   private DrawPanel _drawpanel = null;

   public GridRenderer(Grid grid, int x, int y) {
      _x_offset = x;
      _y_offset = y;
      _grid = grid;
   }

   public void update(JPanel panel) {
      if (_drawpanel != null)
         panel.remove(_drawpanel);

      _drawpanel = new DrawPanel();
      panel.add(_drawpanel);
   }
}
