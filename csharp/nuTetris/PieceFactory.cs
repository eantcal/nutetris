using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace nuTetris
{
    /**
     * Holds pieces catalog and provides a copy of each of them based
     * on a given index number
     */
    public class PieceFactory
    {

        /** Return the factory instance */
        public static PieceFactory getInstance()
        {
            return instance;
        }

        /** Clone a new piece */
        public Piece make(int pieceIdx)
        {
            return catalog.ElementAt(pieceIdx).clone();
        }

        /** Get the count of pieces within the catalog */
        public int getPieceCatalogSize()
        {
            return catalog.Count();
        }

        /** Add a piece into the catalog */
        protected void addCatalog(Piece piece)
        {
            catalog.Add(piece);
        }

        /** Construct a catalog of pieces */
        public PieceFactory()
        {
            int i = 0;
                        
            ConcretePieceL L = new ConcretePieceL(++i);
            addCatalog(L);

            ConcretePieceI I = new ConcretePieceI(++i);
            addCatalog(I);

            ConcretePieceJ J = new ConcretePieceJ(++i);
            addCatalog(J);

            ConcretePieceO O = new ConcretePieceO(++i);
            addCatalog(O);

            ConcretePieceS S = new ConcretePieceS(++i);
            addCatalog(S);

            ConcretePieceZ Z = new ConcretePieceZ(++i);
            addCatalog(Z);

            ConcretePieceT T = new ConcretePieceT(++i);
            addCatalog(T);
        }

        private List<Piece> catalog = new List<Piece>();
        private static PieceFactory instance = new PieceFactory();
    }
}
