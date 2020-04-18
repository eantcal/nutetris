using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace nuTetris
{
    public class ConcretePiece : Piece
    {

        public class Data
        {
            public int posX = 0;
            public int posY = 0;
            public int orientation = 0;
            public int leftMargin = 0;
            public int rightMargin = 0;
            public int topMargin = 0;
            public int bottomMargin = 0;

            public void copyFrom(Data data)
            {
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
        private ShapeData[] shape;

        protected ShapeData[] Shape { get => shape; set => shape = value; }

        public ConcretePiece()
        {
            data = new Data();
            undoData = new Data();
            Shape = new ShapeData[Piece.ORIENTATIONS];

            for (int i = 0; i < Shape.Length; ++i)
            {
                Shape[i] = new ShapeData();
            }
        }

       public override Piece clone()
        {
            return new ConcretePiece();
        }

       public override void moveRight()
        {
            undoData.copyFrom(data);
            ++data.posX;
        }

       public override void moveLeft()
        {
            undoData.copyFrom(data);
            --data.posX;
        }

       public override void moveDown()
        {
            undoData.copyFrom(data);
            ++data.posY;
        }

       public override void rotateCw()
        {
            undoData.copyFrom(data);
            ++data.orientation;

            if (data.orientation >= ORIENTATIONS)
                data.orientation = 0;

            computeMinBoundingBox();
        }

        protected void computeMinBoundingBox()
        {
            if (Shape.Length == 0)
                return;

            ShapeData block = Shape[getOrientation()];

            int minX = -1;
            int maxX = -1;
            int minY = -1;
            int maxY = -1;
            int y = 0;

            foreach (RowData row in block.getData())
            {
                int x = 0;

                foreach (int cell in row.get())
                {
                    if (cell != 0)
                    {
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

    
        public override void rotateAcw()
        {
            undoData.copyFrom(data);

            --data.orientation;

            if (data.orientation < 0)
                data.orientation = ORIENTATIONS - 1;

            computeMinBoundingBox();
        }

        public override void undo()
        {
            data.copyFrom(undoData);
        }

        public override int getAt(int col, int row)
        {
            ShapeData block = Shape[getOrientation()];
            RowData row_data = block.getRow(row);
            return row_data.get()[col];
        }

        public override int getCol()
        {
            return data.posX;
        }

        public override int getRow()
        {
            return data.posY;
        }

        public override int getLeftMargin()
        {
            return data.leftMargin;
        }

        public override int getRightMargin()
        {
            return data.rightMargin;
        }

        public override int getTopMargin()
        {
            return data.topMargin;
        }

        public override int getBottomMargin()
        {
            return data.bottomMargin;
        }

        public override int getOrientation()
        {
            return data.orientation;
        }

        public override ShapeData getShape()
        {
            return Shape[data.orientation];
        }

        public override void moveCenter(int rowLength)
        {
            data.posX = (rowLength + (Piece.COLS - data.leftMargin
                    - data.rightMargin)) / 2;
        }
    }
}
