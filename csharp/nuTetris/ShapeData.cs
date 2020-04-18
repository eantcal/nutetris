/*
 *  This file is part of nuTetris
 *  Author: <antonino.calderone@gmail.com>
 *
 */


using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace nuTetris
{
    /**
     * Represents the data used to draw a piece 
     */
    public class ShapeData : GridData
    {
        public ShapeData() : base(Piece.COLS, Piece.ROWS)
        {}
    }
}
