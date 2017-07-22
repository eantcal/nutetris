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
 *  Author: <antonino.calderone@ericsson.com>, <acaldmail@gmail.com>
 *
 */

package nuJetris;

import java.util.Vector;

public class PieceFactory {

	/** Returns the factory object instance */
	public static PieceFactory get_instance() {
		return _instance;
	}

	/** Creates a new piece object instance */
	Piece make(int piece_idx) {
		return _catalog.elementAt(piece_idx).clone();
	}

	/** Gets number of pieces within the catalog */
	public int get_piece_catalog_size() {
		return _catalog.size();
	}

	/** Adds a new piece into the catalog */
	protected void add_catalog(Piece piece) {
		_catalog.addElement(piece);
	}

	/** Creates a new Piece catalog */
	protected PieceFactory() 
	{
		int i = 0;
		
		ConcretePieceL L=new ConcretePieceL(++i);
		add_catalog(L);
		
		ConcretePieceI I=new ConcretePieceI(++i);
		add_catalog(I);
		
		ConcretePieceJ J=new ConcretePieceJ(++i);
		add_catalog(J);
		
		ConcretePieceO O=new ConcretePieceO(++i);
		add_catalog(O);
		
		ConcretePieceS S=new ConcretePieceS(++i);
		add_catalog(S);
		
		ConcretePieceZ Z=new ConcretePieceZ(++i);
		add_catalog(Z);
		
		ConcretePieceT T=new ConcretePieceT(++i);
		add_catalog(T);
	}

	private Vector<Piece> _catalog = new Vector<Piece>();
	private static PieceFactory _instance = new PieceFactory();
}
