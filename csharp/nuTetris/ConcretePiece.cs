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

        public int Color { get; } = 0;

        protected Data data;
        protected Data undoData;
        private ShapeData[] shape;

        protected ShapeData[] Shape { get => shape; set => shape = value; }

        public ConcretePiece(int c)
        {
            data = new Data();
            undoData = new Data();
            Shape = new ShapeData[Piece.ORIENTATIONS];

            for (int i = 0; i < Shape.Length; ++i)
                Shape[i] = new ShapeData();

            Color = c;
        }

        public override Piece Clone() => new ConcretePiece(Color);

        public override void MoveRight()
        {
            undoData.copyFrom(data);
            ++data.posX;
        }

        public override void MoveLeft()
        {
            undoData.copyFrom(data);
            --data.posX;
        }

        public override void MoveDown()
        {
            undoData.copyFrom(data);
            ++data.posY;
        }

        public override void RotateCw()
        {
            undoData.copyFrom(data);
            ++data.orientation;

            if (data.orientation >= ORIENTATIONS)
                data.orientation = 0;

            ComputeMinBoundingBox();
        }

        protected void ComputeMinBoundingBox()
        {
            if (Shape.Length == 0)
                return;

            ShapeData block = Shape[GetOrientation()];

            int minX = -1;
            int maxX = -1;
            int minY = -1;
            int maxY = -1;
            int y = 0;

            foreach (RowData row in block.GetData())
            {
                int x = 0;

                foreach (int cell in row.Get)
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


        public override void RotateAcw()
        {
            undoData.copyFrom(data);

            --data.orientation;

            if (data.orientation < 0)
                data.orientation = ORIENTATIONS - 1;

            ComputeMinBoundingBox();
        }

        public override void Undo() => data.copyFrom(undoData);

        public override int GetAt(int col, int row)
        {
            ShapeData block = Shape[GetOrientation()];
            RowData row_data = block.GetRow(row);
            return row_data.Get[col];
        }

        public override int GetCol() => data.posX;

        public override int GetRow() => data.posY;

        public override int GetLeftMargin() => data.leftMargin;

        public override int GetRightMargin() => data.rightMargin;

        public override int GetTopMargin() => data.topMargin;

        public override int GetBottomMargin() => data.bottomMargin;

        public override int GetOrientation() => data.orientation;

        public override ShapeData GetShape() => Shape[data.orientation];

        public override void MoveCenter(int rowLength) =>
            data.posX = (rowLength + (Piece.COLS - data.leftMargin
                    - data.rightMargin)) / 2;
    }
}
