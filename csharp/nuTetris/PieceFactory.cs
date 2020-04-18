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
            int i = 0;

            AddCatalog(new ConcretePieceL(++i));
            AddCatalog(new ConcretePieceI(++i));
            AddCatalog(new ConcretePieceJ(++i));
            AddCatalog(new ConcretePieceO(++i));
            AddCatalog(new ConcretePieceS(++i));
            AddCatalog(new ConcretePieceZ(++i));
            AddCatalog(new ConcretePieceT(++i));
        }

        private List<Piece> catalog = new List<Piece>();
        private static PieceFactory instance = new PieceFactory();
    }
}
