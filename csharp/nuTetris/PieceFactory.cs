using System.Collections.Generic;
using System.Linq;

namespace nuTetris
{
    /**
     * Holds pieces catalog and provides a copy of each of them based
     * on a given index number
     */
    public class PieceFactory
    {
        /** Return the factory instance */
        public static PieceFactory GetInstance() => instance;

        /** Clone a new piece */
        public Piece Make(int pieceIdx) => catalog.ElementAt(pieceIdx).Clone();

        /** Get the count of pieces within the catalog */
        public int PieceCatalogSize => catalog.Count();

        /** Add a piece into the catalog */
        protected void AddCatalog(Piece piece) => catalog.Add(piece);

        /** Construct a catalog of pieces */
        public PieceFactory()
        {
            AddCatalog(new ConcretePieceL(1));
            AddCatalog(new ConcretePieceI(2));
            AddCatalog(new ConcretePieceJ(3));
            AddCatalog(new ConcretePieceO(4));
            AddCatalog(new ConcretePieceS(5));
            AddCatalog(new ConcretePieceZ(6));
            AddCatalog(new ConcretePieceT(7));
        }

        private List<Piece> catalog = new List<Piece>();
        private static PieceFactory instance = new PieceFactory();
    }
}
