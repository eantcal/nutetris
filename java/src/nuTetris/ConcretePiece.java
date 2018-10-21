/*
 *  This file is part of nuTetris
 *  Author: <antonino.calderone@gmail.com>
 *
 */

package nuTetris;

import nuTetris.Piece;

public class ConcretePiece implements Piece {

   protected class Data {
       int posX = 0;
       int posY = 0;
       int orientation = 0;
       int leftMargin = 0;
       int rightMargin = 0;
       int topMargin = 0;
       int bottomMargin = 0;

       void copy_from(Data data) {
           posX = data.posX;
           posY = data.posY;
           orientation = data.orientation;
           leftMargin = data.leftMargin;
           rightMargin = data.rightMargin;
           topMargin = data.topMargin;
           bottomMargin = data.bottomMargin;
       }
   }

   protected Data data;
   protected Data undoData;
   protected ShapeData[] shape;

   ConcretePiece() {
       data = new Data();
       undoData = new Data();
       shape = new ShapeData[Piece.ORIENTATIONS];

       for (int i = 0; i < shape.length; ++i) {
           shape[i] = new ShapeData();
       }
   }

   @Override
   public Piece clone() {
       return new ConcretePiece();
   }

   @Override
   public void moveRight() {
       undoData.copy_from(data);
       ++data.posX;
   }

   @Override
   public void moveLeft() {
       undoData.copy_from(data);
       --data.posX;
   }

   @Override
   public void moveDown() {
       undoData.copy_from(data);
       ++data.posY;
   }

   @Override
   public void rotateCw() {
       undoData.copy_from(data);
       ++data.orientation;

       if (data.orientation >= ORIENTATIONS)
           data.orientation = 0;

       computeMinBoundingBox();
   }

   protected void computeMinBoundingBox() {
       if (shape.length == 0)
           return;

       ShapeData block = shape[getOrientation()];

       int minX = -1;
       int maxX = -1;
       int minY = -1;
       int maxY = -1;

       int x = 0;
       int y = 0;

       for (RowData row : block.getData()) {
           x = 0;

           for (int cell : row.get()) {
               if (cell != 0) {
                   if (minX == -1 || x < minX)
                       minX = x;

                   if (minY == -1 || y < minY)
                       minY = y;

                   if (maxX == -1 || x > maxX)
                       maxX = x;

                   if (maxY == -1 || y > maxY)
                       maxY = y;
               }

               ++x;
           }

           ++y;
       }

       data.leftMargin = minX;
       data.rightMargin = Piece.COLS - maxX - 1;
       data.topMargin = minY;
       data.bottomMargin = Piece.ROWS - maxY - 1;

   }

   @Override
   public void rotateAcw() {
       undoData.copy_from(data);

       --data.orientation;

       if (data.orientation < 0)
           data.orientation = ORIENTATIONS - 1;

       computeMinBoundingBox();
   }

   @Override
   public void undo() {
       data.copy_from(undoData);
   }

   @Override
   public int getAt(int col, int row) {
       ShapeData block = shape[getOrientation()];
       RowData row_data = block.getRow(row);
       return row_data.get()[col];
   }

   @Override
   public int getCol() {
       return data.posX;
   }

   @Override
   public int getRow() {
       return data.posY;
   }

   @Override
   public int getLeftMargin() {
       return data.leftMargin;
   }

   @Override
   public int getRightMargin() {
       return data.rightMargin;
   }

   @Override
   public int getTopMargin() {
       return data.topMargin;
   }

   @Override
   public int getBottomMargin() {
       return data.bottomMargin;
   }

   @Override
   public int getOrientation() {
       return data.orientation;
   }

   @Override
   public ShapeData getShape() {
       return shape[data.orientation];
   }

   @Override
   public void moveCenter(int rowLength) {
       data.posX = (rowLength + (Piece.COLS - data.leftMargin
               - data.rightMargin))/2;
   }
}
