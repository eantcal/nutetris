/*
 *  This file is part of nuTetris
 *  Author: <antonino.calderone@gmail.com>
 *
 */

using System.Collections.Generic;

namespace nuTetris
{
    /** Implements Canvas and Game Board 
  * The Canvas shows a preview of next falling piece.
  * The Board is the game area where the pieces fall.
  */
    public class Grid
    {
        protected GridData gridMap;

        /** Current piece object handle */
        private Piece currentPiece = null;

        /** Merge operation type */
        public enum MergeType
        {
            MERGE_PUT, MERGE_REMOVE
        }

        /** Place-piece operation result type */
        public enum PlaceSt
        {
            OK,
            CROSS_RIGHT_BOUNDARY,
            CROSS_LEFT_BOUNDARY,
            CROSS_TOP_BOUNDARY,
            NO_ROOM_FOR_PIECE,
            TOUCH_DOWN
        }

        public Grid(int cols, int rows)
        {
            this.ColsCount = cols;
            this.RowsCount = rows;
            gridMap = new GridData(cols, rows);
        }

        /** Get columns count */
        public int ColsCount { get; } = 0;

        /** Get rows count */
        public int RowsCount { get; } = 0;

        /** Get value of to a cell at coordinates x,y */
        public int GetAt(int x, int y)
        {
            RowData[] row = (RowData[])gridMap.GetData();
            return row[y].Get[x];
        }

        /** Clear the grid content */
        public void Clear() => gridMap = new GridData(ColsCount, RowsCount);

        /** Select new piece */
        public void SetCurrentPiece(Piece piece) => currentPiece = piece;

        /** Move selected piece to another grid */
        public void MovePieceToGrid(Grid grid)
        {
            currentPiece.MoveCenter(ColsCount);
            grid.currentPiece = currentPiece;
            currentPiece = null;
        }

        /** Get a list of completed rows */
        public HashSet<int> GetFullRows()
        {
            HashSet<int> s = new HashSet<int>();

            for (int i = 0; i < RowsCount; ++i)
            {
                if (IsFullRow(i))
                    s.Add(i);
            }

            return s;
        }

        /** Fill the cells of a row using a given color attribute */
        public void FillRow(int rowIdx, int attr)
        {

            RowData rowdata = new RowData(ColsCount);

            int[] val = new int[ColsCount];

            for (int i = 0; i < ColsCount; ++i)
                val[i] = attr;

            rowdata.Set(val);

            gridMap.SetRow(rowIdx, rowdata);
        }

        /** Remove full rows and compact the other cells */
        public void RemoveFullRows()
        {
            HashSet<int> full_rows = (HashSet<int>)GetFullRows();

            GridData gridData = new GridData(ColsCount, RowsCount);

            int j = RowsCount - 1;
            for (int i = RowsCount - 1; i >= 0; --i)
            {
                if (!full_rows.Contains(i))
                {
                    gridData.SetRow(j, gridMap.GetRow(i));
                    --j;
                }
            }

            gridMap = gridData;
        }

        /** Place current piece onto the grid. */
        public PlaceSt GetPlacePiece() => MergePiece(MergeType.MERGE_PUT);

        /** Remove piece from the grid */
        public void RemovePiece() => MergePiece(MergeType.MERGE_REMOVE);

        /** Get a reference to the current piece */
        public Piece CurrentPiece => currentPiece;

        /** Check if piece crosses the grid boundaries */
        protected PlaceSt CheckBoundaries()
        {
            if (currentPiece == null)
                return PlaceSt.OK;

            Piece piece = currentPiece;

            int pieceX = piece.GetCol();
            int pieceY = piece.GetRow();

            // Check if piece crosses the grid borders
            if (pieceX + piece.GetLeftMargin() < 0)
                return PlaceSt.CROSS_LEFT_BOUNDARY;

            if (pieceY + piece.GetTopMargin() < 0)
                return PlaceSt.CROSS_TOP_BOUNDARY;

            if ((pieceX + Piece.COLS - piece.GetRightMargin()) > ColsCount)
                return PlaceSt.CROSS_RIGHT_BOUNDARY;

            if ((pieceY + Piece.ROWS - piece.GetBottomMargin()) > RowsCount)
                return PlaceSt.TOUCH_DOWN;

            return PlaceSt.OK;
        }

        /** Merge the piece content (cells) in the grid */
        protected PlaceSt MergePiece(MergeType mode)
        {
            PlaceSt st = CheckBoundaries();

            if (st != PlaceSt.OK)
                return st;

            Piece piece = currentPiece;

            int pieceX = piece.GetCol();
            int pieceY = piece.GetRow();

            // Copy cells data onto map_data in order to preserve it before merging
            GridData draftMap = gridMap.Clone();

            for (int y = 0; y < Piece.ROWS; ++y)
            {
                for (int x = 0; x < Piece.COLS; ++x)
                {
                    int gridCol = pieceX + x;
                    int gridRow = pieceY + y;

                    if (gridCol < 0 ||
                        gridCol >= ColsCount ||
                        gridRow < 0 ||
                        gridRow >= RowsCount)
                    {
                        continue;
                    }

                    int gridCell = draftMap.GetRow(gridRow).Get[gridCol];
                    int pieceCell = piece.GetAt(x, y);

                    if (mode == MergeType.MERGE_PUT)
                    {
                        // In case of cell conflict, return TOUCH_DOWN or
                        // NO_ROOM_FOR_PIECE
                        // depending on top margin value
                        // (cells data modification will be not committed)
                        if (gridCell != 0 && pieceCell != 0)
                        {
                            return (pieceY - piece.GetTopMargin()) < 1 ?
                                PlaceSt.NO_ROOM_FOR_PIECE : PlaceSt.TOUCH_DOWN;
                        }

                        // Copy piece (or delete) cell content into the draft data map
                        if (pieceCell != 0)
                            draftMap.GetRow(gridRow).Get[gridCol] = pieceCell;
                    }
                    else
                    {
                        // Copy piece (or delete) cell content into the draft data
                        // map
                        if (pieceCell != 0)
                            draftMap.GetRow(gridRow).Get[gridCol] = 0;
                    }
                }
            }

            // commit changes to the map data
            gridMap = draftMap;

            return PlaceSt.OK;
        }

        /** Return true if the row is full, false otherwise */
        private bool IsFullRow(int rowIdx)
        {
            bool ret = true;
            int[] v = gridMap.GetData()[rowIdx].Get;

            for (int i = 0; i < v.Length; ++i)
            {
                if (v[i] == 0)
                {
                    ret = false;
                    break;
                }
            }

            return ret;
        }

    }
}
