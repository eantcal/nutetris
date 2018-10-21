/*
 *  This file is part of nuTetris
 *  Author: <antonino.calderone@gmail.com>
 *
 */

package nuTetris;

import java.util.Vector;

/**
 * Holds pieces catalog and provides a copy of each of them based
 * on a given index number
 */
public class PieceFactory {

    /** Return the factory instance */
    public static PieceFactory getInstance() {
        return instance;
    }

    /** Clone a new piece */
    Piece make(int pieceIdx) {
        return catalog.elementAt(pieceIdx).clone();
    }

    /** Get the count of pieces within the catalog */
    public int getPieceCatalogSize() {
        return catalog.size();
    }

    /** Add a piece into the catalog */
    protected void addCatalog(Piece piece) {
        catalog.addElement(piece);
    }

    /** Construct a catalog of pieces */
    protected PieceFactory() {
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

    private Vector<Piece> catalog = new Vector<Piece>();
    private static PieceFactory instance = new PieceFactory();
}
